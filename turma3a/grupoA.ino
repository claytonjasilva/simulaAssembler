/* Thiago Borsoni; João Campelo; Beatriz Vieira; Daniel Lloyd; Matheus Peçanha; Guilherme Almeida */


#include <LiquidCrystal.h>

#define MODO 0  // 0 para complemento de 1, 1 para complemento de 2

const int rs = 10, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  if (Serial.available()) {
    byte entrada = Serial.read();
    byte operacao = entrada >> 4;
    byte valor = entrada & 0x0F;
    byte resultado;

    switch (operacao) {
      case 0x00:
        resultado = complemento(valor, MODO);
        break;
      case 0x01:
        resultado = adicao(valor);
        break;
      case 0x02:
        resultado = subtracao_puro(valor);
        break;
      case 0x03:
        resultado = subtracao_complemento(valor, MODO);
        break;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Entrada: ");
    printBinaryLCD(entrada);
    //lcd.print(entrada, BIN);
    lcd.setCursor(0, 1);
    lcd.print("Saida: ");
    printBinaryLCD(resultado);
    //lcd.print(resultado, BIN)
    delay(5000);
  }
}

byte complemento(byte valor, bool modo) {
  if (modo) {
    return ~valor + 1;
  } else {
    return ~valor;
  }
}

byte adicao(byte valor) {
  byte parte1 = valor >> 3;
  byte parte2 = valor & 0x07;
  return (parte1 + parte2) & 0x3F;
}

byte subtracao_puro(byte valor) {
  byte parte1 = valor >> 3;
  byte parte2 = valor & 0x07;
  return (parte1 - parte2) & 0x3F;
}

byte subtracao_complemento(byte valor, bool modo) {
  byte parte1 = valor >> 3;
  byte parte2 = valor & 0x07;
  byte sub = complemento(parte2, modo);
  return adicao((parte1 << 3) | sub);
}

void printBinaryLCD(byte value) {
  for (int i = 7; i >= 0; --i) {
    lcd.print((value >> i) & 1);
  }
}

