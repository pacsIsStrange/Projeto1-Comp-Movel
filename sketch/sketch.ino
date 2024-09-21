#include <LiquidCrystal.h>
#define RESET asm ("jmp (0x0000)")

int seconds = 0;

//pronto, agr so precisa fzr um array do tipo "Perguntas"
  //ai cada indice vai ter uma pergunta
typedef struct{
  char* pergunta;
}Perguntas;



LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int btVerde = 3;
int btVermelho = 2;
int btStart = 13;
int bzz = 10;
int rodadas = 5;
int contRodadas = 0;
int sequencia[5];
int jogoIniciado = 0;
int ledVerde = 9;
int ledVermelho = 8;
int arrLed[] = {9, 8};
int input = 0;
int tamanho_array = 14;
int caracter = 50;
Perguntas listaPerguntas[15];
int respostas[14] = {1,0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1};
void setup()
{
  //int respostas[14] = {1,0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1};
  listaPerguntas[0].pergunta = "33 + 77 = 100?";
  listaPerguntas[1].pergunta = "16 x 5 = 80?";
  listaPerguntas[2].pergunta = "2^9 = 512?";
  listaPerguntas[3].pergunta = "25 x 7 = 175?";
  listaPerguntas[4].pergunta = "66 + 44 = 100?";
  listaPerguntas[5].pergunta = "11 x 12 = 132?";
  listaPerguntas[6].pergunta = "1 - 1/2 = 1/2?";
  listaPerguntas[7].pergunta = "2^11 = 4096?";
  listaPerguntas[8].pergunta = "13 x 7 = 91?";
  listaPerguntas[9].pergunta = "567 eh primo?";
  listaPerguntas[10].pergunta = "88 + 22 = 110?";
  listaPerguntas[11].pergunta =	"435 eh primo?";
  listaPerguntas[12].pergunta = "553 eh primo?";
  listaPerguntas[13].pergunta = "28 x 5 = 160?";
  listaPerguntas[14].pergunta = "28 x 5 = 160?";
  

  lcd.begin(16, 2);
  pinMode(btVerde, INPUT_PULLUP);
  pinMode(btVermelho, INPUT_PULLUP);
  pinMode(btStart, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(bzz, OUTPUT);
  randomSeed(analogRead(0));
   //Print a message to the LCD.
  //lcd.print("Aperte o botao para iniciar!");
}



void loop()
{
  
  /*do{
    input = retornaBotao();
    Serial.println(input);
  } while (input != 2);
  lcd.clear();
  delay(100);
  while(1){
    if(!jogoIniciado){
      jogoIniciado = 1;
      contRodadas = 0;
      iniSeq();    
    }
    for (int i = 0; i <= rodadas; i++){
      for (int k = 0; k <= i; k++){
      	digitalWrite(arrLed[sequencia[k]], HIGH);
        delay(100);
        digitalWrite(arrLed[sequencia[k]], LOW);
        delay(30);
      }
      while(true){
        input = retornaBotao();
        if (input < 3 and input != 2){
          digitalWrite(arrLed[input], HIGH);

          if(input == sequencia[i]){
            tone(bzz, 262);
            lcd.setCursor(0, 0);
            lcd.print("Acerto");
            break;
          } else{
            tone(bzz, 136);
            lcd.setCursor(0, 0);
            lcd.print("Erro!");
            
          }
          
        } else if(input == 2){quit(); break;}
      }
    }
    contRodadas++;
    if (contRodadas >= rodadas)
      vitoria();
  }*/
  	lcd.print("Fase 2");
  	delay(2000);
  	lcd.clear();
  	int index = random(0, 8);
  	lcd.print(listaPerguntas[index].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime = millis();
  	
  while(true){
    
  unsigned long currentTime = millis(); 
    
  if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }

  input = retornaBotao();

  if(input != respostas[index] && input != 3){
    lcd.clear();
    lcd.print("Erro");
    delay(2000);
    tone(bzz, 136);
    delay(2000);
    noTone(bzz);
    lcd.clear();
    derrota();
  }
  else if(input == respostas[index]){
    lcd.clear();
    lcd.print("Acerto");
    tone(bzz, 262);
    delay(2000);
    noTone(bzz);
    lcd.clear();
    break;
  }
 }
  	lcd.print(listaPerguntas[index+1].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
     
    input = retornaBotao();

    if(input == respostas[index+1]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, 262);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      break;
    }
    else if(input != respostas[index+1] && input != 3){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, 136);
      noTone(bzz);
      delay(2000);
      lcd.clear();
      derrota();
    }
  }
  	
  	lcd.print(listaPerguntas[index+2].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
    
  	input = retornaBotao();

    if(input == respostas[index+2]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, 262);
      noTone(bzz);
      delay(2000);
      lcd.clear();
      break;
    }
    else if(input != respostas[index+2] && input != 3){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, 136);
      noTone(bzz);
      delay(2000);
      lcd.clear();
      derrota();
    }
  }
  	
  	lcd.print(listaPerguntas[index+3].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
   
    input = retornaBotao();

    if(input == respostas[index+3]){
      lcd.print("Acerto");
      tone(bzz, 262);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      break;
    }
    else if(input != respostas[index+3] && input != 3){
      lcd.print("Erro");
      tone(bzz, 136);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
  }
  
  	lcd.print(listaPerguntas[index+4].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    unsigned long currentTime = millis();
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
   
    
    input = retornaBotao();

    if(input == respostas[index+4]){
      lcd.print("Acerto");
      tone(bzz, 262);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      break;
    }
    else if (input!= respostas[index+4] && input != 3){
      lcd.print("Erro");
      tone(bzz, 136);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
  }
  	lcd.print(listaPerguntas[index+5].pergunta);
    delay(4000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
   
    input = retornaBotao();

    if(input != respostas[index+5] && input != 3){
      lcd.print("Erro");
      tone(bzz, 136);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == respostas[index+5]){
      lcd.print("Acerto");
      tone(bzz, 262);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      break;
    }
  }
  	lcd.print(listaPerguntas[index+6].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
   
    input = retornaBotao();
    
    if(input != respostas[index+6] && input != 3){
      lcd.print("Erro");
      tone(bzz, 136);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == respostas[index+6]){
      lcd.print("Acerto");
      tone(bzz, 262);
	  delay(2000);
      noTone(bzz);
      lcd.clear();
      break;
    }
  }
  	lcd.print("PERGUNTA FINAL");
  	delay(3000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Albertini eh gay?");
  	delay(4000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    unsigned long currentTime = millis(); 
    if (currentTime - startTime >= 7500){
      tone(bzz, 136);
  }
  
  if (currentTime - startTime >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        delay(2000);
        lcd.clear();
        derrota();
    	break;
  }
   
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      tone(bzz, 262);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      vitoria();
    }
    else if(input == 1){
      lcd.print("Erro");
      tone(bzz, 136);
      delay(2000);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
  }
}
  
int retornaBotao(){
  if (digitalRead(btVerde) == LOW)
    return 0;
  else if (digitalRead(btVermelho) == LOW)
    return 1;
  else if (digitalRead(btStart) == LOW)
    return 2;
  else return 3;
}

void vitoria(){
  jogoIniciado = false;
  lcd.setCursor(0, 0);
  lcd.print("Voce venceu!");
}


void derrota(){
  lcd.clear();
  lcd.print("Voce perdeu");
  delay(2000);
  RESET;
}

void quit(){
  jogoIniciado = 0;
  lcd.setCursor(0,0);
  lcd.print("Voce desistiu do jogo!");
  delay(2000);
  lcd.clear();
}

void iniSeq(){
	randomSeed(analogRead(A0));
    for (int j = 0; j <= rodadas; j++)
      sequencia[j] = round(random(0, 2));                           
}
