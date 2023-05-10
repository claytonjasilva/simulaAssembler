/*
Matéria: Arquitetura de computadores
Turma: 3º Feira
Alunos e auto-avaliação: 
  Michel Lutegar,
  André Costa,
  Gabriel Perrota, 
  Hudson Guilherme, 
  Victor Furtado,
  Jõao Marcio
*/



#include <LiquidCrystal.h>

// DECLARANDO AS VARIAVEIS
String entrada; // variavel que recebera o input do usuario
String modo; // variavel para escolher o modo do complemento, se vai ser complemento de 1 ou de 2
int tempo; // variavel para determinar o tempo de tela de cada passo na operação
String op; // variavel que declara qual operação será realizado
String saida; // variavel do resultado da operação
String saida2; // variavel do resultado da operação complemento 2
// LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // configurando o lcd no arduino online
const int rs = 10, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // configurando o lcd no arduino faculdade

// FUNÇÕES
String complemento1(String numero){ // função que faz o complemnto de 1 de uma entrada qualquer
  // INVERTENDO A ENTRADA
  for(int i = 0; i < numero.length()+1; i++){ // um for que ler bit a bit da entrada e inverte
    if(numero[i]=='0'){
      numero[i] = '1';
    } else if(numero[i]=='1'){
      numero[i] = '0';
    }
  }
  return numero;
}

String complemento2(String numero){ // função que faz o complemnto de 2 de um bit qualquer
  numero = complemento1(numero); // faz o complemento de 1
  return somaBit(numero, "1"); // retorna o numero somado mais 1
}

String zeroAEsquerda(String numero){ // função que adiciona os bits '0' para manter o tamanho de 3 bits
  String palavra = "AAA"; // instancia o tamanho da palavra que a gente quer para o número
  
  if (numero.length() == 2){ // se o número tiver tamanho 2, adiciona um '0' a esquerda
    palavra[0] = '0';

    for(int i = 0; i<palavra.length();i++){
      palavra[i+1] = numero[i];
    }

    numero = palavra;

  } else if(numero.length() == 1){ // se o número tiver tamanho 1, adiciona dois '0' a esquerda

    String palavra = "AAA";
    palavra[0] = '0';
    palavra[1] = '0';
    palavra[2] = numero[0];
    numero = palavra;

  }

  return numero;
}

String somaBit(String num1, String num2){ // função que faz a soma binário puro
  long n1 = strtol(num1.c_str(), NULL, 2); // transformando a primeira parcela em binario
  long n2 = strtol(num2.c_str(), NULL, 2); // transformando a segunda parcela em binario

  long soma = n1+n2; 

  String resultado = String(soma, 2); // transformando a soma em String
  return zeroAEsquerda(resultado); // retorna o resultado, mantendo o tamanho determinado pela função zeroAEsquerda()
}

void setup() { 
  lcd.begin(16,2);
  Serial.begin(9600);  
}

void loop() {

  // MODO
  modo = "1"; // opção de escolha para complemento de 1 (modo = "1") ou complemento de 2 (modo = "2")

  // TEMPO
  tempo = 1500; // tempo de tela das operações dos códigos

  // PRINTANDO A ENTRADA DO USUARIO
  lcd.setCursor(0,0);
  lcd.print("Entrada:");
  // entrada = "111000"; atribuindo valor para teste
  while (Serial.available()==0){} entrada = Serial.readString(); // lendo a entrada do usuario pelo serial
  entrada = entrada.substring(0,6);
  delay(tempo);
  lcd.print(entrada);
  delay(tempo);

  // PRINTANDO A OPERAÇÃO ESCOLHIDA PELO USUARIO
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Operador:");
  delay(tempo);
  lcd.print(entrada[0]);
  delay(10);
  lcd.print(entrada[1]);
  delay(tempo);

  // ESCOLHENDO OPERAÇÃO
  if(entrada[0] == '0'){

    // OPERAÇÃO - COMPLEMENTO DE 1 E DE 2
    if(entrada[1] == '0'){

      // PRINTANDO A OPERAÇÃO ESCOLHIDA
      op = "Complemento";
      lcd.setCursor(0,1);
      lcd.print(op);
      delay(tempo);
      
      // PRINTANDO O MODO ESCOLHIDO PARA O COMPLEMENTO
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MODO ");
      lcd.print(modo);
      lcd.setCursor(0,1);
      lcd.print("Comp. "); 
      lcd.print(modo);
      delay(tempo);
      lcd.clear();


      // OPERAÇÃO - COMPLEMENTO DE 1
      if(modo == "1"){
        
        // PRINTANDO A ESCOLHA COMPLEMENTO DE 1
        lcd.setCursor(0,0);
        lcd.print("Comp1: ");

        // ATRIBUINDO O RESULTADO DO COMPLEMENTO DE 1
        saida = complemento1(entrada);

        // PRINTANDO O RESULTADO
        lcd.print(saida);
      } else if (modo == "2"){

        // PRINTANDO A ESCOLHA COMPLEMENTO DE 2
        lcd.print("Comp2: ");

        // ATRIBUINDO O RESULTADO DO COMPLEMENTO DE 2
        saida = complemento2(entrada);

        // PRINTANDO O RESULTADO
        lcd.print(saida);
      } 

      
      // OPERAÇÃO - ADIÇÃO DE BINÁRIO PURO
    } else if(entrada[1] == '1'){

      // PRINTANDO A ESCOLHA DE ADIÇÃO DE BINÁRIO PURO
      op = "Soma";
      lcd.setCursor(0,1);
      lcd.print(op);

      // ATRIBUINDO O RESULTADO DA ADIÇÃO DE BINÁRIO PURO
      saida = somaBit(entrada.substring(0,3),entrada.substring(3,6));

      // PRINTANDO O RESULTADO
      delay(tempo);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(entrada.substring(0,3));
      delay(tempo);
      lcd.print("+");
      delay(tempo);
      lcd.print(entrada.substring(3,6));
      delay(tempo);
      lcd.print("=");
      delay(tempo);
      lcd.print(saida);
    }

    
  } else if (entrada[0] == '1'){

    // OPERAÇÃO - SUBTRAÇÃO DE BINÁRIO PURO
    if(entrada[1] == '0'){

      // PRINTANDO A OPERAÇÃO ESCOLHIDA
      op = "Subtracao bin";
      lcd.setCursor(0,1);
      lcd.print(op);
      delay(tempo);

      // CRIANDO VARIAVEIS
      String minuendo = entrada.substring(0,3); // atribuindo a minuendo a primeira parcela da entrada
      String subtraendo = entrada.substring(3,6); // atribuindo a minuendo a segunda parcela da entrada
      long q1 = strtol(minuendo.c_str(), NULL, 2); // convertendo a primeira parcela para binario
      long q2 = strtol(subtraendo.c_str(), NULL, 2); // convertendo a primeira parcela para binario

      // VERIFICANDO O MAIOR TERMO (MINUENDO E SUBTRAENDO)
      if(q1>q2){ // se q1 for maior que o q2, faça q1-q2
        long subtr = q1-q2; 
        saida = String(subtr, 2); // retornando resultado para string
      } else if(q2>q1){ // se q2 for maior que o q1, faça q2-q1
        long subtr = q2-q1; 
        saida = String(subtr, 2); // retornando resultado para string
      }

      saida = zeroAEsquerda(saida); // retornando o tamanho do resultado para 3

      // PRINTANDO O RESULTADO
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(entrada.substring(0,3));
      delay(tempo);
      lcd.print("-");
      delay(tempo);
      lcd.print(entrada.substring(3,6));
      delay(tempo);
      lcd.print("=");
      delay(tempo);
      lcd.print(saida);

      // OPERAÇÃO - SUBTRAÇÃO DE BINÁRIO DE COMPLEMENTO DE 1 E DE 2
    } else if (entrada[1] == '1'){
    
      // PRINTANDO A OPERAÇÃO ESCOLHIDA
      op = "Subtracao Comp";
      lcd.setCursor(0,1);
      lcd.print(op);
      delay(tempo);
  
      // PRINTANDO O MODO ESCOLHIDO PARA O COMPLEMENTO
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MODO ");
      lcd.print(modo);
      lcd.setCursor(0,1);
      lcd.print("Comp. "); 
      lcd.print(modo);
      delay(tempo);
      lcd.clear();
      
      // VARIAVEIS
      String minuendo, subtraendo; // variaveis para o minuendo, subtraendo
      String operacao; // variavel em que as operações da subtração de complemento serão feitas
      String resultado = "SEE"; // variavel para separar o bit sinal dos bits. S = sinal; E = bits;

      // OPERAÇÃO - SUBTRAÇÃO POR COMPLEMENTO DE 1
      if(modo == "1"){

        // VARIAVEIS PARA SINAIS
        char sinalMin = entrada[0]; // sinal do minuendo
        char sinalSub = entrada[3]; // sinal do subtraendo
        char sinal; // variável que ira guardar o sinal do resultado 

        // OPERAÇÃO - PARA SINAIS DE MINUENDO E SUBTRAENDO DIFERENTES
        if(sinalMin != sinalSub){ // esse if foi posto, pois caso os sinais sejam diferentes, haverá uma soma das parcelas
          
          // VARIAVEIS
          sinal = sinalMin; // sinal do resultado final
          minuendo = complemento1(entrada.substring(1,3)); // atribuindo a parcela 1 o complemento do minuendo dele mesmo
          subtraendo = entrada.substring(4,6); // atribuindo a parcela 2 o subtraendo
          operacao = somaBit(minuendo, subtraendo); // fazendo a soma de binario puro das duas parcelas
          operacao = complemento1(operacao); // refazendo o complemento da resposta para pegar o valor final
          
          // UNINDO A RESPOSTA COM O BIT SINAL
          if(operacao.length() == 3){ // se o resultado acima tiver um tamanho maior que as parcelas iniciais, aumenta o tamanho do resultado
            resultado = "SEEE";
          } 

          resultado[0] = sinal; // atribui o bit sinal ao resultado
          for(int i = 0; i<resultado.length();i++){ // atribui os outros bits ao resultado
            resultado[i+1] = operacao[i];
          }

          operacao = resultado; // atribuindo o resultado final
          
          // OPERAÇÃO - PARA SINAIS DE MINUENDO E SUBTRAENDO IGUAIS
        } else{
          
          // VARIAVEIS
          minuendo = entrada.substring(0,3); // atribuindo o valor do minuendo
          subtraendo = entrada.substring(3,6); // atribuindo o valor do subtraendo
          subtraendo = complemento1(subtraendo); // atribuindo o subtraendo o complemento dele mesmo
          operacao = somaBit(minuendo, subtraendo); // fazendo a soma do minuendo e subtraendo

          // RESULTADO DA OPERAÇÃO MAIOR QUE 3 CASAS
          if (operacao.length() == 4) { // se a soma for maior que 3 casas, remove o bit a esquerda e soma 1
            operacao = operacao.substring(1,4); // removendo o bit a esquerda
            operacao = somaBit(operacao, "1"); // somando o resultado com 1
          }
        }
        
        // RESULTADO DA OPERAÇÃO - SUBTRAÇÃO POR COMPLEMENTO DE 1
        saida = zeroAEsquerda(operacao);

        // OPERAÇÃO - SUBTRAÇÃO POR COMPLEMENTO DE 2
      } else if (modo == "2"){

        // VARIAVEIS
        minuendo = entrada.substring(0,3); // atribuindo o valor do minuendo
        subtraendo = entrada.substring(3,6); // atribuindo o valor do subtraendo 
        subtraendo = complemento2(subtraendo); // atribuindo o complemento de 2 do subtraendo a ele mesmo
        operacao = somaBit(minuendo, subtraendo); // fazendo a soma do minuendo e subtraendo
        
        // RESULTADO MAIOR QUE 3 CASAS
        if ((operacao.length() == 4) && (entrada[0] == entrada[3])) { // se o resultado tiver mais de 3 casas e o sinal do minuendo e subtraendo forem iguais, remove o bit a esqueda
          operacao = operacao.substring(1,4); // removendo o bit a esquerda
        } 
        
        // RESULTADO DA OPERAÇÃO - SUBTRAÇÃO POR COMPLEMENTO DE 2
        saida = operacao;
      }
        
        // PRINTANDO O RESULTADO
        lcd.print(entrada.substring(0,3));
        delay(tempo);
        lcd.print("-");
        delay(tempo);
        lcd.print(entrada.substring(3,6));
        delay(tempo);
        lcd.print("=");
        delay(tempo);
        lcd.print(saida);
    }
  }    

  // FIM DO PROJETO
  delay(10000); // atraso para reiniciar o projeto
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FIM");
  lcd.setCursor(0,1);
  lcd.print(":)");
  delay(10000);
  lcd.clear();
}
