# Relatório do Projeto 1 de Compuação Móvel

## Introdução

O projeto tem como objetivo criar um jogo com 3 fases que será implementado utilizando o Arduino UNO. A proposta envolve a utilização dos conceitos de computação embarcada que foram aprendidos em aula.

## Metodologia
### Materiais utilizados:
 - 1 breadboard;
 - 3 botões;
 - 2 LEDs (vermelho/verde);
 - 3 resistores (1kΩ);
 - 1 buzzer;
 - 1 display LCD 16x2;
 - 1 potênciometro;
 - 1 Arduino UNO;
 - Tinkercad;
 - Arduino IDE.

### Métodos
O projeto foi desenvolvido em três etapas (correspondente às fases do jogo):

#### Fase 1 - Jogo da Memória:

Após pressionar o botão start, é apresentado ao jogador uma sequência em que são acendidos os LEDs verde e vermelho um total de 10 vezes, em uma ordem aleatória. Após ser apresentado com a sequência, o jogador deve repetir a mesma ordem pressionando o botão correspondente ao acendimento de cada LED.
Caso o jogador reproduza corretamente a sequência anteriormente apresentada, será movido para a próxima fase.
Caso cometa algum erro, o jogador é retornado ao início do jogo.

```cpp
void memoria(){
  int cont = 0;
  int index_memoria = random(0, 10); // define o "ponto inicial" na sequência que foi gerada aleatoriamente antes da chamada da função.
  int acerto = 0;  // variável que servirá como contador de acertos
    for (int k = index_memoria; k <= 20; k++){ // este laço será usado apenas para mostrar a sequência ao usuário
      if(sequencia[k] == 0){         // quando o elemento da sequência é 0, aciona-se o LED verde
      	digitalWrite(ledVerde, HIGH);
       delay(1000);
       digitalWrite(ledVerde, LOW);
     		delay(500);
       }
       else if(sequencia[k] == 1){    // quando o elemento da sequência é 1, aciona-se o LED vermelho.
        digitalWrite(ledVermelho, LOW); // é preciso apagar o LED vermelho antes, pois caso o usuário tenha errado anteriormente, ele estaria aceso
        digitalWrite(ledVermelho, HIGH);
        delay(1000);
        digitalWrite(ledVermelho, LOW);
        delay(500);
        }
      cont++;
      if(cont == 10){ // encerra a execução da função quando o jogador chega ao final da sequência
        break;
      }
    }

  	for (int i = index_memoria; i <= 15; i++){ // este laço será usado para receber o input (sequência) do jogador
      int cont2 = 0;
      while(true){
        input = retornaBotao(); // a função retornaBotao() serve para dizer qual botão está sendo pressionado pelo usuário
        if (input == 0){  // quando retornaBotao() retorna 0, foi pressionado o botão referente ao LED verde
          digitalWrite(ledVerde, HIGH);
        }
        else if(input == 1){  quando retornaBotao() retorna 1, foi pressionado o botão referente ao LED vermelho
          digitalWrite(ledVermelho, HIGH);
        }
          if (input == sequencia[i]){  // verifica se o usuário apertou o botão correto de acordo com a sequência
            // quando o usuário acerta, o buzzer dá um feedback sonoro    
            i++;
            acerto++;
            tone(bzz, acerto);
            delay(250);
            digitalWrite(ledVerde, LOW);
            digitalWrite(ledVermelho, LOW);
            noTone(bzz);
            if (acerto == 10){ // se usuário acertou toda a sequência (10 acertos) encerra o loop
              cont2++;
              break;
            }
            
          } else if(input != sequencia[i] && input != 3 && input != 2) { // entra nessa condicinal quando o usuário aperta o botão errado de acordo com a sequência.
            // vale ressaltar que quando a função retornaBotao() retorna 3, nenhum botão está sendo pressionado pelo usuário.
            tone(bzz, erro);
            delay(250);
            noTone(bzz);
            digitalWrite(ledVerde, LOW);
            digitalWrite(ledVermelho, LOW);
            derrota(); 
            break;
          }
        else if(input == 2){  // quando retornaBotao() retorna 2, foi pressionado o botão referente ao START/RESET
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledVermelho, LOW);
          quit();
        }
      }
      if(cont2 == 1){
        break;
      }
  }
  lcd.clear();
  lcd.print("Voce ganhou");
  delay(1500);
  lcd.clear();
}
``` 

# Fase 2 - Fase de Perguntas:
Após completar a primeira fase, o jogador é levado à fase de perguntas. Nesta fase, são apresentadas ao jogador 7 perguntas, sorteadas aleatoriamente de um banco de perguntas, no display LCD. O jogador, por sua vez, deve responder as perguntas com Sim ou Não, pressionando o botão do LED verde para sim e o botão do LED vermelho para não. Para cada pergunta, o jogador possui 10 segundos para responder, com o tempo restante sendo mostrado no display. Caso o jogador acerte a resposta, será apresentada outra pergunta no Display, até que se tenham totalizado 7 acertos, o que leva o jogador à fase 3. Caso não responda dentro dos 10 segundos, a questão será considerada como pulada e o jogo apresentará a próxima questão. Caso o jogador volte a não responder qualquer outra questão dentro do tempo, ele perderá a fase de perguntas e será retornado ao início do jogo. Caso o jogador erre alguma pergunta, também perderá a fase de perguntas e será retornado ao início do jogo. 
# Fase 3 - Pergunta Final
A fase 3 funciona da mesma maneira que a fase 2, o jogador é apresentado com uma pergunta final no Display LCD e deve responder com Sim ou Não dentro de 10 segundos. Caso o jogador não responda a pergunta final dentro dos 10 segundos, perderá a fase 3 e será retornado ao início do jogo, o mesmo valendo para caso o jogador erre a resposta. Por fim, caso o jogador acerte a resposta, terá vencido o jogo e uma mensagem de vitória será apresentada no Display LCD, juntamente com uma música de vitória tocada pelo Buzzer.
# Mais detalhes:
Caso o botão de Start/Reset seja apertado com o jogo já em andamento, será considerado como desistência por parte do jogador e ele será retornado ao início do jogo.
O jogo possui sons programados para serem tocados pelo buzzer para todo tipo de interação, incluindo acertos, erros, vitória, derrota, desistência e pular pergunta.
Além de poder ser implementado no Arduíno UNO, deixamos também um link com o circuito montado na plataforma Tinkercad, onde o mesmo funcionamento pode ser simulado.

[LINK DO PROJETO NO TINKERCAD](https://www.tinkercad.com/things/daBGwtuhZFQ-projeto-1/editel?sharecode=6JyAtBr4nV1n0gE9bmHrp2lm3OQVEnqkpkbPvpzJql0)

# English:
 
The first project of mobile computing consists in a simple game of 3 levels that can be implemented on an Arduino UNO, exploring the concepts of embedded computing we have seen during the course.
The circuit can be built with 1 breadbord, 3 buttons (1 Start/Reset button and 2 buttons that turn on the LEDs), 1 red LED, 1 green LED, 3 resistors, 1 buzzer, 1 LCD Display 16x2 and 1 potenciometer, alongside of the Arduino UNO itself.
As previously mentioned, the game works with 3 levels:
# Level 1 - Memory Game:
After pressing the start button, the player is presented with a sequence of blinking red and green LEDs, that blink a total of 10 times in a random order. After being presented with the sequence, the player must reproduce the exact same sequence of LEDs by pressing the buttons that turn on each led.
If the player reproduces the previously presented sequence correctly, they advance to the next level.
If the player makes a mistake, they are returned to the start screen.
# Level 2 - Yes or No questions:
After advancing through the first level, the player is taken to the Yes or No questions level. In this level, the player is presented in the LCD Display with 7 questions, drawn randomly from a question database.  The player must answer the questions with Yes or No, pressing the green LED button for yes, or the red LED button for no. For each question, the player has 10 seconds to answer, with the remaining time being displayed in the LCD Display. If the player gets the answer right, they are presented with the next question, until they have answered correctly all 7 questions, which takes them to the next level. If the player doesn't answer the question within the 10 seconds, the question will be considered skipped, and the next question will be presented. If the player fails to answer another question within 10 seconds, they will have lost the second level and will be taken back to the start of the game. The same applies if the player gets the answer wrong.
# Level 3 - Final Question
Level 3 works the same as level 2, the player is presented with a final question and must answer it with Yes or No within 10 seconds. If the player fails to answer within 10 seconds, they will have lost the game and will be returned to the start. The same applies if the player gets the answer wrong. Finally, if the player answers the final question correctly, they will have won the game and a victory message will be shown in the LCD Display, alongside a victory song played through the buzzer.
# More details:
If the Start/Reset button is pressed with the game already running, it will be considered as if the player gave up, and they will be taken back to the start.
The game has sounds programmed to be played through the buzzer for every interaction, including answering right, answering wrong, victory, defeat, giving up and skipping question.
Besides being projected for the Arduino UNO, we also left a link with the circuit built on the platform Tinkarcad, where it is possible to simulate it.

[PROJECT ON TINKERCAD](https://www.tinkercad.com/things/daBGwtuhZFQ-projeto-1/editel?sharecode=6JyAtBr4nV1n0gE9bmHrp2lm3OQVEnqkpkbPvpzJql0)
