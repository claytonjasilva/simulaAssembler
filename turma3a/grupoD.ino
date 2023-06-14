/*
Mateus Norcia
Gustavo Raia
Ian Amoedo
Bruno Pilao
Bruno Xavier
Breno de Souza
Luis Pastura
*/

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define PALAVRA 11

/* Display */
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

/* Keypad setup */
const byte LINHAS = 4;
const byte COLUNAS = 4;

const byte PINOS_LINHAS[LINHAS] = {5, 4, 3, 2};
const byte PINOS_COLUNAS[COLUNAS] = {A3, A2, A1, A0};
const char TECLAS_MATRIZ[LINHAS][COLUNAS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'}
};

const int MODO_SUB = 0; // modo 0 indica bit sinal, modo 1 indica complemento de 1 e modo 2 indica complemento de 2

String entrada;
String saida;

String X;
String Y;

String leitura_teclas = ""; // String vazia para armazenar os caracteres lidos

String sinal;

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS);

// ============================================================================================================

/* Converte binário para decimal */
int binario_decimal(String num) {
  int decimal = 0;
  int pot = 1;
  for (int i = 0; i < PALAVRA; i++) {
    decimal += (num[PALAVRA - 1 - i] - 48) * pot;
    pot = pot * 2;
  }

  return decimal;
}
/* Converte decimal para binário */
String decimal_binario(int decimal) {
  String resultado = "";
  int j = pow(2, PALAVRA - 1);
  for (int i = 0; i < PALAVRA; i++) {
    if (decimal < j) {
      resultado = resultado + "0";
    }
    else {
      resultado = resultado + "1";
      decimal = decimal - j;
    }
    j = j / 2;
  }

  return resultado;
}

/* Complemento de 1 */
String complemento_1(String dado) {
  String resposta = "";
  for (int i = 3; i < PALAVRA; i++) {
    if (dado[i] == '0')
      resposta = resposta + "1";
    else
      resposta = resposta + "0";
  }
  lcd.clear();
  lcd.println(resposta);
  return resposta;
}

/* Complemento de 2 */
String complemento_2(String input) {
  String resultado = complemento_1(input);
  int decimal = binario_decimal(resultado) + 1;
  resultado = decimal_binario(decimal);

  return resultado;
}

// FUNÇÕES MONÁDICAS =============================

// Soma de números de 8 bits
String addI(String dado, String X) {
  int num1 = ((dado[3] - 48) * 128) + ((dado[4] - 48) * 64) + ((dado[5] - 48) * 32) + ((dado[6] - 48) * 16) + ((dado[7] - 48) * 8) + ((dado[8] - 48) * 4) + ((dado[9] - 48) * 2) + ((dado[10] - 48) * 1);
  int num2 = ((X[0] - 48) * 128) + ((X[1] - 48) * 64) + ((X[2] - 48) * 32) + ((X[3] - 48) * 16) + ((X[4] - 48) * 8) + ((X[5] - 48) * 4) + ((X[6] - 48) * 2) + ((X[7] - 48) * 1);
  
  int soma = (num1 + num2);

  String resposta = decimal_binario(soma);
  resposta = resposta.substring(3,11);

  lcd.clear();
  lcd.println(resposta);

  return resposta;
}

// Subtração de números de 8 bits
String subI(String dado, String X) {
  dado = dado.substring(3,11);
  int num1 = ((dado[0] - 48) * 128) + ((dado[1] - 48) * 64) + ((dado[2] - 48) * 32) + ((dado[3] - 48) * 16) + ((dado[4] - 48) * 8) + ((dado[5] - 48) * 4) + ((dado[6] - 48) * 2) + ((dado[7] - 48) * 1);
  int num2 = ((X[0] - 48) * 128) + ((X[1] - 48) * 64) + ((X[2] - 48) * 32) + ((X[3] - 48) * 16) + ((X[4] - 48) * 8) + ((X[5] - 48) * 4) + ((X[6] - 48) * 2) + ((X[7] - 48) * 1);
  int subtracao = (num1 - num2);

  String resposta;

  if (num1 > num2){
    resposta = decimal_binario(subtracao);
    resposta = resposta.substring(3, 11);

    lcd.clear();
    lcd.println(resposta);       
  } else {
    resposta = decimal_binario(num2 - num1);
    switch (MODO_SUB) {
      case 0:
        resposta = resposta.substring(3, 11);
        resposta[0] = '1';
        break;
      case 1:
        resposta = complemento_1(resposta);
        break;
      case 2:
        resposta = complemento_2(resposta);
        break;
    }
  }
  return resposta;
}

// FUNÇÕES DIÁDICAS ==============================

// Soma de números de 4 bits
String add(String dado) {
  int num1 = ((dado[3] - 48) * 8) + ((dado[4] - 48) * 4) + ((dado[5] - 48) * 2) + ((dado[6] - 48) * 1);
  int num2 = ((dado[7] - 48) * 8) + ((dado[8] - 48) * 4) + ((dado[9] - 48) * 2) + ((dado[10] - 48) * 1);
  int soma = num1 + num2;

  String resposta = decimal_binario(soma);
  resposta = resposta.substring(3, 11);

  lcd.clear();
  lcd.println(resposta);

  return resposta;
}

// Subtração de números de 4 bits
String sub(String input) {
  int num1 = ((input[3] - 48) * 8) + ((input[4] - 48) * 4) + ((input[5] - 48) * 2) + ((input[6] - 48) * 1);
  int num2 = ((input[7] - 48) * 8) + ((input[8] - 48) * 4) + ((input[9] - 48) * 2) + ((input[10] - 48) * 1);
  int subtracao = (num1 - num2);

  String resposta;

  if (num1 > num2) {
    resposta = decimal_binario(subtracao);
    resposta = resposta.substring(3, 11);

    lcd.clear();
    lcd.println(resposta);    
  } else {
    resposta = decimal_binario(num2 - num1);
    resposta = resposta.substring(3, 11);
    switch (MODO_SUB) {
      case 0:
        resposta = resposta.substring(3, 11);
        resposta[0] = '1';
        break;
      case 1:
        resposta = complemento_1(resposta);
        break;
      case 2:
        resposta = complemento_2(resposta);
        break;
    }
  }
  return resposta;
}

// FUNÇÕES QUE NÃO UTILIZAM O CAMPO DE OPERANDO ==

String storage(String input) {
  input = input.substring(3, 11);

  lcd.clear();
  lcd.println(input);

  X = input;
  return input;
}

String transport() {
  Y = X;

  lcd.clear();
  lcd.println(Y);
  return Y;
}

String ldo(String X) {
  String dado = X; // Lê o conteúdo da variável X

  for (int i = 3; i < PALAVRA; i++) {
    if (X[i] == '1')
      dado = Y;
  }
  String resposta = sinal + dado;

  return resposta;
}

// ============================================================================================================

void setup() {
  // configura o número de colunas e linhas do lcd:
  lcd.begin(16, 2);
  lcd.print("Trabalho AP2");
  Serial.begin(9600); // Inicia porta serial
}

/* Switch de Seleção de Operação */
int selecaoOp(String input) {

   /* Caso 1 - Comp1 */
  if (input[0] == '0' && input[1] == '0' && input[2] == '0') {
    Serial.println("\nCaso 1 - Comp1");
    Serial.println("Entrada: " + input);

    X = complemento_1(input);
    Serial.println(" Saída/X: " + X);
  }

  /* Caso 2 - Add */
  else if (input[0] == '0' && input[1] == '0' && input[2] == '1') {
    Serial.println("\nCaso 2 - Add");
    Serial.println("Entrada: " + input);

    X = add(input);
    Serial.println(" Saída/X: " + X);    
  }

  /* Caso 3 - AddI */
  else if (input[0] == '0' && input[1] == '1' && input[2] == '0') {
    Serial.println("\nCaso 3 - Add I");
    Serial.println("Entrada: " + input);

    X = addI(input, X);

    Serial.println(" Saída/X: " + X);
  }

  /* Caso 4 - Sub */
  else if (input[0] == '0' && input[1] == '1' && input[2] == '1') {
    Serial.println("\nCaso 4 - Sub");
    Serial.println("Entrada: " + input);

    X = sub(input);
    Serial.println(" Saída/X: " + X);
  }

  /* Caso 5 - SubI */
  else if (input[0] == '1' && input[1] == '0' && input[2] == '0') {
    Serial.println("\nCaso 5 - SubI");
    Serial.println("Entrada: " + input);

    X = subI(input, X);
    Serial.println(" Saída/X: " + X);
  }

  /* Caso 6 - Ldo */
  else if (input[0] == '1' && input[1] == '0' && input[2] == '1') {
    Serial.println("\nCaso 6 - Ldo");
    ldo(X);
  }

  /* Caso 7 - Sto */
  else if (input[0] == '1' && input[1] == '1' && input[2] == '0') {
    Serial.println("\nCaso 7 - Sto");
    Serial.println("Entrada: " + input);

    storage(input);
    Serial.println("Saída/X: " + X);
  }

  /* Caso 8 - Trans */
  else if (input[0] == '1' && input[1] == '1' && input[2] == '1') {
    Serial.println("\nCaso 8 - Trans");
    Serial.println("Entrada: " + input);

    transport();
    Serial.println("Saída/Y: " + Y);
  }
}

// ============================================================================================================

void loop() {
  char tecla;
  int contador = 0;

  // Loop para ler os caracteres individualmente
  while (contador < 11) {
    tecla = teclado_personalizado.getKey(); // Leitura do teclado para obter o caractere

    // Verifica se a tecla pressionada é válida (um caractere)
    if (tecla != NO_KEY) {
      switch (tecla) {

        case '1':
          leitura_teclas += tecla; // Concatena o caractere na string

          lcd.clear();
          lcd.println(leitura_teclas);

          contador += 1;
          break;

        case '0':
          leitura_teclas += tecla; // Concatena o caractere na string

          lcd.clear();
          lcd.println(leitura_teclas);

          contador += 1;
          break;

        case '=':
          selecaoOp(leitura_teclas);

          break;

        case '.':
          leitura_teclas = "";
          lcd.clear();
          contador = 0;

        default:
          Serial.println("Apenas 0 ou 1");
      }
    }
  }
}
