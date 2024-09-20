#include <LiquidCrystal.h>

int seconds = 0;

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

void setup()
{
  lcd.begin(16, 2);
  pinMode(btVerde, INPUT_PULLUP);
  pinMode(btVermelho, INPUT_PULLUP);
  pinMode(btStart, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(bzz, OUTPUT);
   //Print a message to the LCD.
  lcd.print("Aperte o botao para iniciar!");
}



void loop()
{
  
  do{
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
  }
	lcd.print("Albertini trabalha?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
 	
  while(true){
  	input = retornaBotao();
  	
  if(input == 0){
    lcd.print("Erro");
    delay(2000);
    lcd.clear();
    quit();
  }
  else if(input == 1){
    lcd.print("Acerto");
    delay(2000);
    lcd.clear();
    break;
  }    
 }
  	lcd.print("Robertinho eh autista?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
    else if(input == 1){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
  }
  	
  	lcd.print("Finatti eh escravo?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
  	input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
    else if(input == 1){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
  }
  	
  	lcd.print("Kawan eh pobre?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
    else if(input == 1){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
  }
  
  	lcd.print("Givas eh gado?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
    else if(input == 1){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
  }
  	lcd.print("Tiago sabe dar commit?");
    delay(2000);
  	lcd.clear();
  	delay(500);
  	
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
    else if(input == 1){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
  }
  	lcd.print("Pedro eh corno?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
    }
    else if(input == 1){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      break;
    }
  }
  	lcd.print("PERGUNTA FINAL");
  	delay(3000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Albertini eh gay?");
  	delay(2000);
  	lcd.clear();
  	delay(500);
  
  while(true){
    input = retornaBotao();
    
    if(input == 0){
      lcd.print("Acerto");
      delay(2000);
      lcd.clear();
      vitoria();
    }
    else if(input == 1){
      lcd.print("Erro");
      delay(2000);
      lcd.clear();
      quit();
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
