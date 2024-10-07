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
    for (int k = index_memoria; k <= 20; k++){
    // este laço será usado apenas para mostrar a sequência ao usuário
      if(sequencia[k] == 0){
      // quando o elemento da sequência é 0, aciona-se o LED verde
      	digitalWrite(ledVerde, HIGH);
       delay(1000);
       digitalWrite(ledVerde, LOW);
     		delay(500);
       }
       else if(sequencia[k] == 1){
       // quando o elemento da sequência é 1, aciona-se o LED vermelho.
        digitalWrite(ledVermelho, LOW); // é preciso apagar o LED vermelho antes, pois caso o usuário tenha errado anteriormente, ele estaria aceso
        digitalWrite(ledVermelho, HIGH);
        delay(1000);
        digitalWrite(ledVermelho, LOW);
        delay(500);
        }
      cont++;
      if(cont == 10){
      // encerra a execução da função quando o jogador chega ao final da sequência
        break;
      }
    }

  	for (int i = index_memoria; i <= 15; i++){
   // este laço será usado para receber o input (sequência) do jogador
      int cont2 = 0;
      while(true){
        input = retornaBotao(); // a função retornaBotao() serve para dizer qual botão está sendo pressionado pelo usuário
        if (input == 0){
        // quando retornaBotao() retorna 0, foi pressionado o botão referente ao LED verde
          digitalWrite(ledVerde, HIGH);
        }
        else if(input == 1){
        // quando retornaBotao() retorna 1, foi pressionado o botão referente ao LED vermelho
          digitalWrite(ledVermelho, HIGH);
        }
          if (input == sequencia[i]){
          // verifica se o usuário apertou o botão correto de acordo com a sequência
          // quando o usuário acerta, o buzzer dá um feedback sonoro    
            i++;
            acerto++;
            tone(bzz, acerto);
            delay(250);
            digitalWrite(ledVerde, LOW);
            digitalWrite(ledVermelho, LOW);
            noTone(bzz);
            if (acerto == 10){
            // se usuário acertou toda a sequência (10 acertos) encerra o loop
              cont2++;
              break;
            }
            
          } else if(input != sequencia[i] && input != 3 && input != 2) {
            // entra nessa condicinal quando o usuário aperta o botão errado de acordo com a sequência.
            // vale ressaltar que quando a função retornaBotao() retorna 3, nenhum botão está sendo pressionado pelo usuário.
            tone(bzz, erro);
            delay(250);
            noTone(bzz);
            digitalWrite(ledVerde, LOW);
            digitalWrite(ledVermelho, LOW);
            derrota(); 
            break;
          }
        else if(input == 2){
        // quando retornaBotao() retorna 2, foi pressionado o botão referente ao START/RESET
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

#### Fase 2 - Fase de Perguntas:
Após completar a primeira fase, o jogador é levado à fase de perguntas. Nesta fase, são apresentadas ao jogador 7 perguntas, sorteadas aleatoriamente de um banco de perguntas, no display LCD. O jogador, por sua vez, deve responder as perguntas com Sim ou Não, pressionando o botão do LED verde para sim e o botão do LED vermelho para não. Para cada pergunta, o jogador possui 10 segundos para responder, com o tempo restante sendo mostrado no display. Caso o jogador acerte a resposta, será apresentada outra pergunta no Display, até que se tenham totalizado 7 acertos, o que leva o jogador à fase 3. Caso não responda dentro dos 10 segundos, a questão será considerada como pulada e o jogo apresentará a próxima questão. Caso o jogador volte a não responder qualquer outra questão dentro do tempo, ele perderá a fase de perguntas e será retornado ao início do jogo. Caso o jogador erre alguma pergunta, também perderá a fase de perguntas e será retornado ao início do jogo. 

``` cpp
  lcd.print("Fase 2"); //Print que indica o início da fase 2
  delay(2000);
  lcd.clear();
  int index = random(0, 8); //Sorteia randomicamente um número entre 0 e 7
  int vidas = 1; //Numero de vidas do jogador
  char tempo_string[200]; //Preparação da string para utilizar no sprintf de maneira formatada
  int tempo;
  lcd.print(listaPerguntas[index].pergunta); //Print da pergunta no Display LCD
  delay(4000);
  lcd.clear();
  delay(500);
  lcd.print("Sim ou Nao?"); //Print que indica como o jogador deve responder

  unsigned long startTime1 = millis(); //Função que guarda o tempo inicial antes de entrar no loop
  while(true){
  
  
  unsigned long currentTime = millis(); //Função que guarda o tempo atual de execução do loop
  lcd.setCursor(0,1); //Posicionamento do print no LCD
  int tempo = ((currentTime - startTime1)/1000); //Calculo do tempo atual em segundos
  sprintf(tempo_string, "Tempo: %02d", 10 - tempo); //Print do tempo restante no LCD
  lcd.print(tempo_string);
  
  delay(100);
  
    
  if (currentTime - startTime1 >= 7500){
      tone(bzz, tempo_quase_esgotado); //Laço que calcula se o tempo está quase se esgotando e emite um buzzer
  }
  
  if (currentTime - startTime1 >= 10000){ //Laço que calcula se o tempo se encerrou e emite um buzzer
    	lcd.clear();
    	noTone(bzz); //Função que cancela o buzzer anterior
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
    	lcd.print("Restam 6"); //Print que informa o usuário quantas questões restam
    	delay(2000);
    	lcd.clear();
    	delay(1000);
        vidas--; //Descréscimo de vidas caso o jogador deixe o tempo esgotar
    	break;
  }

  input = retornaBotao(); //Função que obtem o input do usuário por meio de qual botão aperta
    
    if(input == 0){ //Laço que acende a luz verde, caso o botão tenha sido pressionado pelo jogador
      digitalWrite(9, HIGH);
    }
    else if(input == 1){ //Laço que acende a luz vermelha, caso o botão tenha sido pressionado pelo jogador
      digitalWrite(8, HIGH);
    }
  // O bloco a seguir se repete para cada uma das perguntas
  // INÍCIO DO BLOCO
  if(input != respostas[index] && input != 3 && input != 2){ //Laço que verifica se o usuário errou a resposta e emite um buzzer
    lcd.clear();
    lcd.print("Erro");
    tone(bzz, erro);
    delay(2000);
    digitalWrite(9, LOW); //Apaga as luzes caso estejam acesas
    digitalWrite(8, LOW); //Apaga as luzes caso estejam acesas
    noTone(bzz);
    lcd.clear();
    derrota(); //Encerra o jogo após o jogador ter errado a resposta
  }
  else if(input == respostas[index]){ //Laço que verifica se o jogador acertou a questão
    lcd.clear();
    lcd.print("Acerto!");
    tone(bzz, acerto);
    delay(2000);
    digitalWrite(9, LOW); //Apaga as luzes caso estejam acesas
    digitalWrite(8, LOW); //Apaga as luzes caso estejam acesas
    noTone(bzz);
    lcd.clear();
    lcd.print("Restam 6"); //Print que indica ao jogador quantas questões restam
    delay(2000);
    lcd.clear();
    delay(1000);
    break;
  }
    else if(input == 2){ //Laço que verifica se o jogador pressionou o botão de desistir
      quit(); //Função que reinicia o jogo após o usuário desistir
      //RESET;
    }
    // FINAL DO BLOCO
 }
  
  	
```

#### Fase 3 - Pergunta Final
A fase 3 funciona da mesma maneira que a fase 2, o jogador é apresentado com uma pergunta final no Display LCD e deve responder com Sim ou Não dentro de 10 segundos. Caso o jogador não responda a pergunta final dentro dos 10 segundos, perderá a fase 3 e será retornado ao início do jogo, o mesmo valendo para caso o jogador erre a resposta. Por fim, caso o jogador acerte a resposta, terá vencido o jogo e uma mensagem de vitória será apresentada no Display LCD, juntamente com uma música de vitória tocada pelo Buzzer.

``` cpp
lcd.print("PERGUNTA FINAL"); //Print que indica a passagem para a fase final
  	delay(3000);
  	lcd.clear();
  	delay(500);
  	lcd.print("9^4 = 6561?"); //Pergunta final
  	delay(4000);
  	lcd.clear();
  	delay(500);
  	lcd.print("Sim ou Nao?");
  	unsigned long startTime8 = millis(); //Função que guarda o tempo inicial antes de entrar no loop
  
  while(true){
    unsigned long currentTime = millis(); //Função que guarda o tempo atual de execução do loop
    lcd.setCursor(0,1);
    tempo = ((currentTime - startTime8)/1000); //Calcula o tempo atual em segundos
    sprintf(tempo_string, "Tempo: %02d", 10 - tempo); //Print que mostra o tempo restante para o jogador responder a pergunta
    lcd.print(tempo_string);
    delay(100);
    if (currentTime - startTime8 >= 7500){ //Laço que calcula se o tempo está quase se esgotando e emite um buzzer
      tone(bzz, tempo_quase_esgotado);
  }
  
  if (currentTime - startTime8 >= 10000){ //Laço que calcula se o tempo se esgotou e emite um buzzer
    	lcd.clear();
    	noTone(bzz);
        lcd.print("Tempo Esgotado");
        tone(bzz, tempo_esgotado);
        delay(2000);
    	noTone(bzz);
        lcd.clear();
        derrota(); //Função que encerra o jogo caso o usuário não tenha respondido dentro do tempo
    	break;
  }
   
    input = retornaBotao(); //Função que obtem o input do usuário por meio de qual botão aperta
    
    if(input == 0){ //Laço que acende a luz verde caso o usuário pressione o botão correspondente
      digitalWrite(9, HIGH);
     }
    else if(input == 1){ //Laço que acende a luz vermelha caso o usuário pressione o botão correspondente
      digitalWrite(8, HIGH);
    }
    
    if(input == 0){ //Laço que verifica se o usuário acertou a pergunta e emite um buzzer
      lcd.clear();
      lcd.print("Acerto");
      tone(bzz, acerto);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      vitoria(); //Função que encerra o jogo com vitória do usuário caso responda a pergunta corretamente
    }
    else if(input == 1){ //Laço que verifica se o usuário errou a resposta e emite um buzzer
      lcd.clear();
      lcd.print("Erro");
      tone(bzz, erro);
      delay(2000);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      noTone(bzz);
      lcd.clear();
      derrota(); //Função que encerra o jogo caso o usuário tenha errado a resposta 
    }
    else if(input == 2){ //Laço que verifica se o jogador apertou o botão de desistir
      quit(); //Função que reinicia o jogo caso o usuário tenha desistido
      //RESET;
    }
```

#### Mais detalhes:
Caso o botão de Start/Reset seja apertado com o jogo já em andamento, será considerado como desistência por parte do jogador e ele será retornado ao início do jogo.
O jogo possui sons programados para serem tocados pelo buzzer para todo tipo de interação, incluindo acertos, erros, vitória, derrota, desistência e pular pergunta.
Além de poder ser implementado no Arduíno UNO, deixamos também um link com o circuito montado na plataforma Tinkercad, onde o mesmo funcionamento pode ser simulado.

[LINK DO PROJETO NO TINKERCAD](https://www.tinkercad.com/things/daBGwtuhZFQ-projeto-1/editel?sharecode=6JyAtBr4nV1n0gE9bmHrp2lm3OQVEnqkpkbPvpzJql0)

## Experimentos

As fotos abaixo ilustram o circuito montado e o jogo funcionando:

[INSERIR IMAGENS DO JOGO FUNCIONANDO]

## Conclusão

A proposta foi atendida com sucesso. O circuito foi montado de acordo com os materiais especificados, e o jogo funcionou corretamente, com toas as interações tendo sido testadas e integradas de maneira adequada.

## Dificuldades Encontradas

As principais dificuldades do projeto tiveram a ver com as particularidades da programação em arduino, quando comparado com a programação em C++.
