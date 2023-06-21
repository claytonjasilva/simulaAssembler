/*
Integrantes:
Thaís Bustamante
Maria Giulia Pessanha
Vitor Lobianco
Matheus Santos
Gabriel Martinez

 Arduino Calculator
 
*/

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <math.h>
#define PALAVRA 11

/* Display */
LiquidCrystal lcd(10, 8, 5, 4, 3, 2);

/* Keypad setup */
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {31, 33, 35, 37};
byte colPins[KEYPAD_COLS] = {39, 41, 43, 45};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'} // Se não tiver apagando mudar key
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

const int BITS = 11;
String dado;
String entrada;
String saida;
int x = 0;
int y = 0;

void adicao(String dado){ // Soma os operandos (E7E6E5E4) e (E3E2E1E0) e carrega o resultado em X
  int num1,num2;
  int resultado;
  num1 = (dado[3] - 48) * 8 +  (dado[4] - 48) * 4 + (dado[5] - 48) * 2 + (dado[6] - 48); // E7E6E5E4
  num2 = (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48); // E3E2E1E0
  resultado = num1 + num2;
  x = resultado;
}

void adicao1(String dado){ // Soma imediata do operando E7E6...E0 com X e devolve em X
  int num = (dado[3] - 48) * 128 +  (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);
  x += num;
}

void armazenaOperando(String dado){ // Armazena o operando E7E6...E0 na variável X
  int operando = (dado[3] - 48) * 128 +  (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);
  x = operando;
}

String converteDecimalString(int dado){ // Converte Decimal para E7E6...E0 em String
  String resultado = "";
  int j=pow(2,PALAVRA-1);
  for (int i=0;i<PALAVRA;i++){
    if (abs(dado)<j){
      resultado = resultado + "0";
    }
    else {
      resultado = resultado + "1";
      dado = abs(dado) - j;
    }
    j = j/2;  
  }
  
  return resultado;
}

void geraSaida(String dado){  // Produz a saída para a segunda linha do LCD 1602
  lcd.setCursor(0, 1); // Seta cursor para a posição coluna 0, linha 1
  lcd.print(dado);
}

String complemento1(String dado){ // Produz o complemento de 1 de E7E6...E0
  String resultado = "";
  for (int i=3;i<PALAVRA;i++){
    if (dado[i] == '1') resultado += "0"; 
    else resultado += "1";
  }
  
  x = converteStringDecimal(resultado);
  return resultado;
}

void complemento2(String dado){ // Gera o complemento de 2 de E7E6...E0
  String resultado;
  int decimal;
  resultado = complemento1(dado);
  decimal = converteStringDecimal(resultado) + 1;
  
  x = decimal;
}

int converteStringDecimal(String dado){ // Converte E7E6...E0 em String para Decimal
  int decimal = 0;
  int pot = 1;
  for (int i=3;i<PALAVRA;i++){
    decimal += (dado[PALAVRA - 1 - i] - 48) * pot;
    pot = pot * 2;
  }

  return decimal;
}

void copiaValor(){ // Copia o valor armazenado em X para uma variável Y
  y = x;
}

void ldo(String dado) { // Lê o conteúdo de X ou Y, e apresenta no LCD em bit sinal
  int valor;
  String bitPalavra, bin;
  int num = (dado[3] - 48) * 128 +  (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);
  if (num == 0) { // Armazena X ou Y em um int valor de acordo com o operando
    valor = x;
  } else {
    valor = y;
  }

  bitPalavra = converteDecimalString(valor);
  String used = bitPalavra.substring(3); // String E7E6...E0
  lcd.setCursor(0, 0);

  if (x < 0) { // Representação de 9 bits em bit sinal
    bin = "1" + used;
    char usedStr[10];
    sprintf(usedStr, "%09ld", bin.toInt());
    lcd.print(usedStr);
  } else {
    bin = "0" + used;
    char usedStr[10];
    sprintf(usedStr, "%09d", bin.toInt());
    lcd.print(usedStr);
  }
  lcd.setCursor(0, 1);
}

void subtracao(String dado){ // Subtrai os operandos (E7E6E5E4) e (E3E2E1E0) e carrega o resultado em X
                               // Gera o resultado de acordo com o modo desejado
  int num1,num2;
  String resultado;
  num1 = (dado[3] - 48) * 8 +  (dado[4] - 48) * 4 + (dado[5] - 48) * 2 + (dado[6] - 48); // E7E6E5E4
  num2 = (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48); // E3E2E1E0
  x = num1 - num2;
  // Serial.println(x);
}

void subtracao1(String dado){ // Subtração imediata do operando E7E6...E0 com X e devolve em X
  int num = (dado[3] - 48) * 128 +  (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + (dado[7] - 48) * 8 +  (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);
  x -= num;
  // Serial.println(x);
}

void showSpalshScreen() {
  lcd.print("GoodArduinoCode");
  lcd.setCursor(3, 1);
  String message = "Calculator";
  for (byte i = 0; i < message.length(); i++) {
    lcd.print(message[i]);
    delay(100);
  }
  delay(500);
}

void updateCursor() {
  if (millis() / 250 % 2 == 0 ) {
    lcd.cursor();
  } else {
    lcd.noCursor();
  }
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  showSpalshScreen();
  lcd.clear();
  lcd.cursor();
  lcd.setCursor(0, 0);
}

int selecaoOp(String dado){ // Seleciona a opção com base na String E10E9...1E0
  if (dado[0] == '0' && dado[1] == '0' && dado[2] == '0') {
    complemento1(dado); // Mnemônico: Comp1
  } else if (dado[0] == '0' && dado[1] == '0' && dado[2] == '1'){
      adicao(dado); // Mnemônico: Add
  } else if (dado[0] == '0' && dado[1] == '1' && dado[2] == '0'){
      adicao1(dado); // Mnemônico: Add1
  } else if (dado[0] == '0' && dado[1] == '1' && dado[2] == '1'){
      subtracao(dado); // Mnemônico: Sub
  } else if (dado[0] == '1' && dado[1] == '0' && dado[2] == '0'){
      subtracao1(dado); // Mnemônico: Sub1
  } else if (dado[0] == '1' && dado[1] == '0' && dado[2] == '1'){
      ldo(dado); // Mnemônico: Ldo
  } else if (dado[0] == '1' && dado[1] == '1' && dado[2] == '0'){
      armazenaOperando(dado); // Mnemônico: Sto
  } else if (dado[0] == '1' && dado[1] == '1' && dado[2] == '1'){
      copiaValor(); // Mnemônico: Trans
  }
}

void processInput(char key) {
  // Caso tenha cometido algum erro de digitação
  if (key == '.') {
    delay(500);
    lcd.clear();
    lcd.print("apagando...");
    delay(500);
    lcd.clear();
    dado = "";
  }
  // Verifica se a tecla pressionada é 0 ou 1
  if (key == '0' || key == '1') {
    // Adiciona o caractere no dado
    dado += key;
    // Exibe o caractere no LCD
    lcd.print(key);
    // Verifica se a instrução atual está completa
    if (dado.length() == BITS) {
      delay(500);
      lcd.clear();
      delay(500);
      
      selecaoOp(dado);
      dado = "";
    }
  }
}

void loop() {
  updateCursor();
  char key = keypad.getKey();
  if (key) {
    processInput(key);
  }
}

// 00100111010  ->  x = 13
// 10100000000  ->  lê x, print 0 0000 1101
// 01000000001  ->  x = 14
// 10100000000  ->  lê x. print 0 0000 1110
// 01000000001  ->  x = 15
// 11100000000  ->  y = x = 15
// 01000001010  ->  x = 25
// 10111111111  ->  lê y, print 0 0000 1111
// 10100000000  ->  lê x, print 0 0001 1001
// 11000000000  ->  x = 0
