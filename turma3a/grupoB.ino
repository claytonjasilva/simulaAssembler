/* Componentes:
Carolina Cruz dos Santos
Fernanda Garcia Moysés de Oliveira (R) 
Juliana Azeredo Hall
Larissa Aparecida Moreira Nobrega
Lucas jose cola Abreu
Maria da Graça Oliveira Castro de Mello
VICTOR DA CONCEIÇÃO COUTINHO
*/


#include <LiquidCrystal.h>

int modo = 1; //Variável para armazenar o modo de complemento (1 ou 2)
int entrada; //Variável para armazenar a entrada de 6 bits
int saida; //Variável para armazenar a saída de 6 bits

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600); 
  lcd.begin(16, 2); //Especifica o número de linhas e colunas 

  entrada = 0b001001;
}

int complemento(int bin) {
  int result = ~bin;
  if (modo == 1) { // Comp 1
    return result;
  } else { // Comp 2
    return result + 1;
  }
}

int adicao(int bin) {
  int num1, num2;
  num1 = (bin & 0b111000) >> 3;
  num2 = (bin & 0b111);
  return num1 + num2;
}

int subtracaoBin(int bin) {
  int num1, num2;
  num1 = (bin & 0b111000) >> 3;
  num2 = (bin & 0b111);
  return num1 - num2;
}

int subtracaoComp(int bin) {
  int num1, num2;
  num1 = (bin & 0b111000) >> 3;
  num2 = (bin & 0b111);
  return num1 + complemento(num2);
}

void loop()
{
  if (Serial.available()) {
    delay(100);
    lcd.clear();
    entrada = 0;

    while (Serial.available() > 0) {
      int sInput = Serial.read() - '0';
      entrada = entrada << 1;
      entrada += sInput;
    }
    Serial.println(entrada, BIN);
    
	int operacao = (entrada & 0b110000) >> 4;
    
    switch (operacao) {
      case 0: // Complemento
      	saida = complemento(entrada);
	    Serial.println("complemento");
      	break;
      case 1: // Adicao
      	saida = adicao(entrada);
  	    Serial.println("Adicao");
      	break;
      case 2: // Subtracao bin
      	saida = subtracaoBin(entrada);
        Serial.println("Subtracao bin");
      	break;
      case 3: // Subtracao complem
      	saida = subtracaoComp(entrada);
        Serial.println("Subtracao compl");
      	break;
    }
    saida = saida & 0b111111;
    Serial.println(saida, BIN);
    lcd.print(saida, BIN);
  }
}
