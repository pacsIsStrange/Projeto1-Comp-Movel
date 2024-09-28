#include <LiquidCrystal.h>
#define RESET asm ("jmp (0x0000)")

int seconds = 0;


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
int jogoIniciado = 0;
int ledVerde = 9;
int ledVermelho = 8;
int arrLed[] = {9, 8};
int input = 0;
int tamanho_array = 14;
int caracter = 50;
Perguntas listaPerguntas[15];
int respostas[14] = {1,0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1};
int sequencia[19] = {0,1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0};
int erro = 136;
int acerto = 262;
int tempo_quase_esgotado = 235;
int tempo_esgotado = 200;
int quit_buzzer = 215;
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
  

  lcd.begin(16, 2);
  pinMode(btVerde, INPUT_PULLUP);
  pinMode(btVermelho, INPUT_PULLUP);
  pinMode(btStart, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(bzz, OUTPUT);
  randomSeed(analogRead(0));
   
}



void loop()
{
  lcd.print("APERTE START");
  lcd.setCursor(0, 1);
  lcd.print("PARA INICIAR");
  do{
    input = retornaBotao();
    //Serial.println(input);
  } while (input != 2);
  
  lcd.clear();
  lcd.print("JOGO INICIADO!!");
  delay(400);

  memoria();
  

  
  	lcd.print("Fase 2");
  	delay(2000);
  	lcd.clear();
  	int index = random(0, 8);
  	int vidas = 1;
  	char tempo_string[200];
  	int tempo;
  	lcd.print(listaPerguntas[index].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	
  	unsigned long startTime1 = millis();
  while(true){
  
  
  unsigned long currentTime = millis();
  lcd.setCursor(0,1);
  int tempo = ((currentTime - startTime1)/1000);
  sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
  lcd.print(tempo_string);
  
  delay(100);
  
    
  if (currentTime - startTime1 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime1 >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }

  input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

  if(input != respostas[index] && input != 3 && input != 2){
    lcd.clear();
    lcd.print("Erro");
    tone(bzz, erro);
    delay(2000);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    noTone(bzz);
    lcd.clear();
    derrota();
  }
  else if(input == respostas[index]){
    lcd.clear();
    lcd.print("Acerto!");
    tone(bzz, acerto);
    delay(2000);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    noTone(bzz);
    lcd.clear();
    lcd.print("Restam 6");
    delay(2000);
    lcd.clear();
    delay(1000);
    break;
  }
    else if(input == 2){
      quit();
      RESET;
    }
 }
  	lcd.print(listaPerguntas[index+1].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime2 = millis();
  	

  while(true){
    
    unsigned long currentTime = millis(); 
    lcd.setCursor(0,1);
    int tempo = ((currentTime - startTime2)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);

    if (currentTime - startTime2 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime2 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime2 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
     
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

    if(input == respostas[index+1]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      lcd.print("Restam 5");
      delay(2000);
      lcd.clear();
      delay(1000);
      break;
    }
    else if(input != respostas[index+1] && input != 3 && input != 2){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  	
  	lcd.print(listaPerguntas[index+2].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime3 = millis();
  
  while(true){
    unsigned long currentTime = millis();
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime3)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);


    if (currentTime - startTime3 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime3 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime3 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
    
  	input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

    if(input == respostas[index+2]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      lcd.print("Restam 4");
      delay(2000);
      lcd.clear();
      delay(1000);
      break;
    }
    else if(input != respostas[index+2] && input != 3 && input != 2){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  	
  	lcd.print(listaPerguntas[index+3].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime4 = millis();
  
  while(true){
    unsigned long currentTime = millis();
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime4)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);

    if (currentTime - startTime4 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime4 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime4 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
   
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

    if(input == respostas[index+3]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      lcd.print("Restam 3");
      delay(2000);
      lcd.clear();
      delay(1000);
      break;
    }
    else if(input != respostas[index+3] && input != 3 && input != 2){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  
  	lcd.print(listaPerguntas[index+4].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime5 = millis();
  
  while(true){
  unsigned long currentTime = millis(); 
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime5)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);
    if (currentTime - startTime5 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime5 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime5 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
   
    
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

    if(input == respostas[index+4]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      lcd.print("Restam 2");
      delay(2000);
      lcd.clear();
      delay(1000);
      break;
    }
    else if (input!= respostas[index+4] && input != 3 && input != 2){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  	lcd.print(listaPerguntas[index+5].pergunta);
    delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime6 = millis();
  	
  while(true){
   unsigned long currentTime = millis(); 
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime6)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);
    if (currentTime - startTime6 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime6 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime6 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
   
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }

    if(input != respostas[index+5] && input != 3 && input != 2){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == respostas[index+5]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      lcd.print("Resta 1");
      delay(2000);
      lcd.clear();
      delay(1000);
      break;
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  	lcd.print(listaPerguntas[index+6].pergunta);
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime7 = millis();
  
  while(true){
    unsigned long currentTime = millis(); 
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime7)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);
    if (currentTime - startTime7 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime7 >= 10000 && vidas == 0){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
  
  if (currentTime - startTime7 >= 10000 && vidas == 1){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        vidas--;
    	break;
  }
   
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }
    
    if(input != respostas[index+6] && input != 3){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == respostas[index+6]){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
	  delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      break;
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
  	lcd.print("PERGUNTA FINAL");
  	delay(3000);
  	lcd.clear();
  	delay(500);
  	lcd.print("9^4 = 6561?");
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime8 = millis();
  
  while(true){
    unsigned long currentTime = millis(); 
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime8)/1000);
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo);
    lcd.print(tempo_string);
    delay(100);
    if (currentTime - startTime8 >= 7500){
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime8 >= 10000){
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota();
    	break;
  }
   
    input = retornaBotao();
    
    if(input == 0){
      digitalWrite(9, HIGH);
    }
    else if(input == 1){
      digitalWrite(8, HIGH);
    }
    
    if(input == 0){
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      vitoria();
    }
    else if(input == 1){
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota();
    }
    else if(input == 2){
      quit();
      RESET;
    }
  }
}

void memoria(){
  int cont = 0;
  int index_memoria = random(0, 10);
  int acerto = 0;
    for (int k = index_memoria; k < 15; k++){
      if(sequencia[k] == 0){
      	digitalWrite(9, HIGH);
        delay(1000);
        digitalWrite(9, LOW);
		delay(500);
        }
        else if(sequencia[k] == 1){
        digitalWrite(8, LOW);
        digitalWrite(8, HIGH);
        delay(1000);
        digitalWrite(8, LOW);
        delay(500);
        }
      cont++;
      //Serial.println(cont);
      if(cont == 10){
        break;
      }
    }

   
      //Serial.println(i);
  	for (int i = index_memoria; i <= 15; i++){
      int cont2 = 0;
      while(true){
        input = retornaBotao();
        if (input == 0){
          digitalWrite(9, HIGH);
        }
        else if(input == 1){
          digitalWrite(8, HIGH);
        }
       
			
          if (input == sequencia[i]){
         
            i++;
            acerto++;
            Serial.println(i);
            //Serial.println(acerto);
            tone(bzz, acerto);
            delay(250);
            digitalWrite(9, LOW);
            digitalWrite(8, LOW);
            noTone(bzz);
            if (acerto == 10){
              cont2++;
              break;
            }
            
          } else if(input != sequencia[i] && input != 3) {
            tone(bzz, erro);
            delay(250);
            noTone(bzz);
            derrota(); 
            break;
          }
      }
      if(cont2 == 1){
        break;
      }
  }
  lcd.clear();
  lcd.print("Voce ganhou");
  delay(3000);
  lcd.clear();
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
  delay(10000);
  RESET;
}


void derrota(){
  lcd.clear();
  lcd.print("Voce perdeu");
  delay(1000);
  RESET;
}

void quit(){
  jogoIniciado = 0;
  lcd.setCursor(0,0);
  lcd.print("Voce desistiu!");
  tone(bzz, quit_buzzer);
  delay(2000);
  noTone(bzz);
  lcd.clear();
}

void iniSeq(){
	randomSeed(analogRead(A0));
    for (int j = 0; j <= rodadas; j++)
      sequencia[j] = round(random(0, 2));                           
}
