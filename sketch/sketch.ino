#include <LiquidCrystal.h>

int seconds = 0;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int btVerde = 3;
int btVermelho = 2;
int btStart = 1;
int bzz = 10;
int rodadas = 5;
int contRodadas = 0;
int sequencia[5];
int jogoIniciado = 0;
int ledVerde = 9;
int ledVermelho = 8;
int arrLed[] = {9, 8};

void setup()
{
  lcd.begin(16, 2);
  pinMode(btVerde, INPUT_PULLUP);
  pinMode(btVermelho, INPUT_PULLUP);
  pinMode(btStart, INPUT_PULLUP);
  
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(bzz, OUTPUT);
  // Print a message to the LCD.
  lcd.print("Aperte o botao para iniciar!");
}



void loop()
{
  if(digitalRead(btStart) == LOW && !jogoIniciado){
    jogoIniciado = 1;
    contRodadas = 0;
    iniSeq();    
  }
  for (int i = 0; i <= rodadas; i++){
    while(true){
      input = retornaBotao();
      if (input < 2){
        digitalWrite(arrLed[input], HIGH);
        tone(bzz, 262);
      } else {quit(); break;}
    }
  }
  contRodadas++
  if (contRodadas >= rodadas)
	vitoria();
}

int retornaBotao(){
  if (digitalRead(btVerde) == LOW)
    return 0;
  else if (digitalRead(btVermelho) == LOW)
    return 1;
  else if (digitalRead(btStart) == LOW)
    return 2;
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
}

void iniSeq(){
	randomSeed(analogRead(A0);
    for (int j = 0; j <= rodadas; j++)
      sequencia[j] = round(random(0, 2));                           
}
                           

                           