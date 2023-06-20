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
#include <Keypad.h> // Biblioteca do codigo

const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {22,24,26,28}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[COLUNAS] = {30,32,34,36}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

const int rs = 10, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

#include <math.h>
#define PALAVRA 11

String entrada;
String X;
String Y;
int sinal = 0;

String adicao(String dado){ 
  int num1,num2, soma;
  String resultado;

  num1 = (dado[3] - 48) * 8 + (dado[4] - 48) * 4 + (dado[5] - 48) * 2 + (dado[6] - 48);
  num2 = (dado[7] - 48) * 8 + (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48); 

  soma = num1 + num2;
  if(soma > 255)
  {
    lcd.print("Deu overflow!");
    return X;
  }

  resultado = converteDecimalString(soma);

  sinal = 0;
  Serial.println("ad: "+resultado);
  return resultado; 
}

String adicaoImediata(String dado)
{
  int num, numx, soma;
  String resultado;

  num = (dado[3] - 48) * 128 + (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + 
  (dado[7] - 48) * 8 + (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);

  numx = (X[0] - 48) * 128 + (X[1] - 48) * 64 + (X[2] - 48) * 32 + (X[3] - 48) * 16 + 
  (X[4] - 48) * 8 + (X[5] - 48) * 4 + (X[6] - 48) * 2 + (X[7] - 48);

  soma = num + numx;
  if(soma > 255)
  {
    lcd.print("Deu overflow!");
    return X;
  }

  sinal = 0;
  resultado = converteDecimalString(soma);
  Serial.println("adi: "+resultado);
  return resultado;
  
}

String converteDecimalString(int dado){ 
  String resultado = "";
  int j=pow(2,PALAVRA-4);
  for (int i=0;i<PALAVRA-3;i++){
    if (dado<j){
      resultado = resultado + "0";
    }
    else {
      resultado = resultado + "1";
      dado = dado - j;
    }
    j = j/2;  
  }
  
  return resultado;
}

void geraSaida(String dado){ 
  Serial.println(dado);
  lcd.setCursor(0, 0);
  lcd.print(dado);
  lcd.setCursor(0, 1);

}

String complemento1(String dado){ 
  String resultado = "";
  for (int i=3;i<PALAVRA;i++){
    if (dado[i] == '1')
    {
        resultado = resultado + "0";
    } 
    else resultado = resultado + "1";
  }

  Serial.println("com1: "+resultado);
  return resultado;
}


int converteStringDecimal(String dado){ 
  int decimal = 0;
  int pot = 1;
  for (int i=0;i<PALAVRA - 3;i++){
    decimal += (dado[PALAVRA - 1 - i] - 48) * pot;
    pot = pot * 2;
  }
  return decimal;
}

String subtracao(String dado){ 
                               
  int num1,num2;
  String resultado;

  num1 = (dado[3] - 48) * 8 + (dado[4] - 48) * 4 + (dado[5] - 48) * 2 + 
  (dado[6] - 48); 

  num2 = (dado[7] - 48) * 8 + (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + 
  (dado[10] - 48); 
  
  if (num1 > num2) 
    resultado = converteDecimalString(num1 - num2);
  else 
  {
    resultado = converteDecimalString(num2 - num1);
    sinal = 1;
  }

  Serial.println("sub: "+resultado);
  return resultado;
}

String subtracaoImediata(String dado)
{
  int num1,numx;
  String resultado;
  num1 = (dado[3] - 48) * 128 + (dado[4] - 48) * 64 + (dado[5] - 48) * 32 + (dado[6] - 48) * 16 + 
  (dado[7] - 48) * 8 + (dado[8] - 48) * 4 + (dado[9] - 48) * 2 + (dado[10] - 48);

  numx = (X[0] - 48) * 128 + (X[1] - 48) * 64 + (X[2] - 48) * 32 + (X[3] - 48) * 16 + 
  (X[4] - 48) * 8 + (X[5] - 48) * 4 + (X[6] - 48) * 2 + (X[7] - 48);
  if (num1 > numx) 
    resultado = converteDecimalString(num1 - numx);
  else 
  {
    sinal = 1;
    resultado = converteDecimalString(numx - num1);
  }

  Serial.println("subi: "+resultado);
  return resultado;
}

void Armazenar(String dado)
{
  X = dado.substring(3, 11);
}

void Copiar(String dado)
{
  Y = X;
}


void TratarEntrada(char input) {
  if (input != '*') {
    entrada += String(input);
  }
  else {
    Serial.print("\nentrada: " + entrada);
    lcd.clear();
    selecaoOp(entrada);
    entrada = "";
  }
}

String ler(String dado)
{
  String valor = X;
  String resposta;

  for(int i=3;i<PALAVRA;i++)
  {
    if(dado[i] == '1')
    {
      valor = Y;
    }
  }

  resposta = sinal + valor;
  Serial.println("resposta: " + resposta);
  return resposta;

}




int selecaoOp(String dado){ // Seleciona a opção com base na String E5E4E3E2E1E0
  if (dado[0] == '0' && dado[1] == '0' && dado[2] == '0') // Operação 1
      X = complemento1(entrada);
  else if (dado[0] == '0' && dado[1] == '0' && dado[2] == '1') // Operação 2
    X = adicao(entrada);
  else if (dado[0] == '0' && dado[1] == '1' && dado[2] == '0') // Operação 3
    X = adicaoImediata(entrada);
  else if (dado[0] == '0' && dado[1] == '1' && dado[2] == '1') // Operação 4
    X = subtracao(entrada); 
  else if (dado[0] == '1' && dado[1] == '0' && dado[2] == '0') // Operação 5
    X = subtracaoImediata(entrada);
  else if (dado[0] == '1' && dado[1] == '0' && dado[2] == '1') // Operação 6
    geraSaida(ler(entrada));
  else if (dado[0] == '1' && dado[1] == '1' && dado[2] == '0') // Operação 7
    Armazenar(entrada);
  else if (dado[0] == '1' && dado[1] == '1' && dado[2] == '1') // Operação 8
    Copiar(entrada);

}

void setup() {
  lcd.begin(16, 2); // Inicializa o lcd
  Serial.begin(9600); // Inicializa o monitor serial

  lcd.print("digite os dados:"); // e disponibiliza a mensagem na linha 1
  delay(1000);
  lcd.clear();

  
}

void loop() {
  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
  if (leitura_teclas) { // Se alguma tecla foi pressionada
    lcd.print(leitura_teclas);
    TratarEntrada(leitura_teclas);
  }
}
