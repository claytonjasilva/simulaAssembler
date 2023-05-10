/*
Breno Selem de manhães Huf
DAVI LUIS DOS SANTOS COPLE LIMA
Gabriel Lacerda da Fontoura
HENRIQUE BARBOSA DANTAS ROLAN (R) 
JULIANA DE OLIVEIRA SILVA SOUSA
RAFAEL FRANCISCO DE ABREU SOARES LIMA
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <LiquidCrystal.h>

struct palavra{
  bool bit[6];
};

int decimal(int size, char *temp);
struct palavra complemento1(char *temp);
void complemento2(struct palavra temp);
void out(struct palavra temp);
struct palavra binario(int num);
void soma(char *temp);
void sub(char *temp);

const int rs = 10, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16, 2);

}

void loop() {

  char *palavra = "001001";

  bool complemento = false;

  lcd.setCursor(0,1);

  if(decimal(6,palavra)<16){
    if(complemento){
      out(complemento1(palavra));
    }
    else{
      complemento2(complemento1(palavra));
    }
  }
  else if(decimal(6, palavra)<32){
    soma(palavra);
  }
  else if(decimal(6, palavra)<48){
    sub(palavra);
  }


}

struct palavra binario(int num){

  struct palavra res;
  int count = 0;

  for (int i = 5; i >= 0; i--) {
    if(num >= (pow(2,i))){
      res.bit[count] = true;
      num -= pow(2,i);
    }
    else{
      res.bit[count] = false;
    }
    count++;
  }

  out(res);

  return res;

}

int decimal(int size, char *temp){

  int count = 0;
  int res = 0;
  
  for (int i = size - 1; i >= 0; i--) {
    res += pow(2, count) * (*(temp+i) - 48);
    count++;
  }

  return res;
}

struct palavra complemento1(char *temp){

  struct palavra res;

  for (int i = 0; i < 6; i++) {
    if(temp[i] == '0'){
      res.bit[i] = true;
    }
    else{
      res.bit[i] = false;
    }
  }

  return res;
}

void out(struct palavra temp){

  for(int i = 0; i < 6; i++){
    lcd.setCursor(i,0);
    lcd.print(temp.bit[i]);
  }

  printf("\n");
  
}

void soma(char *temp){
  int res = decimal(3, temp) + decimal(3, temp+3);
  binario(res);
}

void sub(char *temp){
  int res = abs(decimal(3, temp) - decimal(3, temp+3));
  binario(res);
}

void complemento2(struct palavra temp){

  struct palavra res;
  bool carry = false;

  if(temp.bit[5] == true){
    carry = true;
  }
  else{
    temp.bit[5] = true;
  }

  for (int i = 5; i >= 0; i--) {
    if(carry){
      if(temp.bit[i] == true){
        res.bit[i] = false;
        carry = true;
      }
      else{
        res.bit[i] = true;
        carry = false;
      }
    }
    else{
      res.bit[i] = temp.bit[i];
      carry = false;
    }
  }

  out(res);

}
