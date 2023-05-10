// Caio Araújo da Luz
// JOAO LUCAS DE REZENDE CURVELLO DE PAULA
// JOAO PEDRO DALLEPRANE CORREIA
// João Pedro Takamoto Constant
// Théo furtado mauricio

#include <LiquidCrystal.h>

const int rs = 10, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5, modo = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {             
  // configura o número de colunas e linhas do lcd:
  lcd.begin(16, 2);
  Serial.begin(9600);
}


String decimalParaBinario(int decimal) {
  	String binario = "";

    while (decimal > 0) {
        int resto = decimal % 2;
        binario = String(resto) + binario;
        decimal /= 2;
    }

    while (binario.length() < 6) {
        binario = "0" + binario;
    }

    return binario;
}

String decimalParaBitSinal(int decimal) {
  String binario = "";
  
  binario = decimalParaBinario(abs(decimal));

  binario[0] = '1';

  return binario;
}



int binarioParaDecimal(String bin) {
  int decimal = 0;
  int len = bin.length();

  for (int i = 0; i < len; i++) {
    char c = bin.charAt(i);
    if (c == '1') {
      decimal += pow(2, len - i - 1);
    }
  }

  return decimal;
}

int adicao(int num1, int num2){
  return num1+num2;
}

int subtracao(int num1, int num2){  
  return num1-num2;
}


String binarioParaCompl1(String binario) {
  String complemento_1 = "";

  for (int i = 0; i < binario.length(); i++) {
    if (binario.charAt(i) == '0') {
      complemento_1 += '1';
    } else {
      complemento_1 += '0';
    }
  }

  return complemento_1;
}

String binarioParaCompl2(String binario) {
  String resultado = "";
  bool carry = true;
  // Começa com carry true para adicionar 1 no final

  // Inverte todos os bits do número original
  for (int i = 0; i < 6; i++) {
    if (binario.charAt(i) == '0') {
      resultado += '1';
    } else {
      resultado += '0';
    }
  }

  // Adiciona 1 ao resultado invertido
  for (int i = 5; i >= 0; i--) {
    if (resultado.charAt(i) == '1' && carry) {
      resultado.setCharAt(i, '0');
    } else if (resultado.charAt(i) == '0' && carry) {
      resultado.setCharAt(i, '1');
      carry = false;
    }
  }

  return resultado;
}

void loop() {

  if(Serial.available() > 0){
    String binario = Serial.readString();
    lcd.setCursor(5,0);
    lcd.print(binario);
    
    String resultado = "";
    
    if(binario[0] == '0' && binario[1] == '0'){ // complemento de 1

      resultado = binarioParaCompl1(binario);

    } else if(binario[0] == '0' && binario[1] == '1'){ // complemento de 2
      
      resultado = binarioParaCompl2(binario);
      
    } else if(binario[0] == '1' && binario[1] == '0') { 
    	
      int num1 = binarioParaDecimal(binario.substring(0,3));
      int num2 = binarioParaDecimal(binario.substring(3,6));

      resultado = decimalParaBinario(adicao(num1,num2));

    } else {
      
      int num1 = binarioParaDecimal(binario.substring(0,3));
      int num2 = binarioParaDecimal(binario.substring(3,6));

      int sub = subtracao(num1, num2);

      if(sub > 0){
        resultado = decimalParaBinario(sub);
      } else {
        if(modo == 0){
          resultado = decimalParaBitSinal(sub);
        } else if (modo == 1){
          resultado = binarioParaCompl1(decimalParaBinario(abs(sub)));
        } else if (modo == 2){
          resultado = binarioParaCompl2(decimalParaBinario(abs(sub)));
        }
      }

       
    }
     
    lcd.setCursor(5,1);
    lcd.print(resultado);
  }
}
