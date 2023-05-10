/*
Integrantes:
Thaís Bustamante
Maria Giulia Pessanha
Vitor Lobianco
Matheus Santos
Gabriel Martinez
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 16 
#define lin  2 
#define ende  0x27 

LiquidCrystal_I2C lcd(ende,col,lin); 

void setup()
{  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  lcd.setCursor(0, 0); 
  lcd.print("ENTRADA:"); 
}
void loop() {
  
  if (Serial.available() >= 1) { // VERIFICA
      long entrada = Serial.parseInt();//  RECEBE O BINARIO COMO VALOR INTEIRO DECIMAL
      char lixo = Serial.read();//LIMPA O LIXO
      int resultado;

      // CRIA UMA VARIAVEL PARA CARA VALOR DO BINARIA 
      long sobra = entrada;
      int e5 = sobra%10;
      sobra = (sobra-e5)/10;
      int e4 = sobra%10;
      sobra = (sobra-e4)/10;
      int e3 = sobra%10;
      sobra = (sobra-e3)/10;
      int e2 = sobra%10;
      sobra = (sobra-e2)/10;
      int e1 = sobra%10;
      sobra = (sobra-e1)/10;
      int e0 = sobra%10;
      sobra = (sobra-e0)/10;

      int valor = ( e0*32 + e1*16 + e2*8 + e3*4 + e4*2 + e5*1); // CONVERTE TODOS OS DIGITOS PARA DECIMAL
      int valor_l = (e0*4+e1*2+e2*1); // VALOR DOS PRIMEIROS 3 DIGITOS BINARIOS EM DECIMAL
      int valor_r = (e3*4+e4*2+e5*1); //VALOR DOS ULTIMOS 3 DIGITOS BINARIOS EM DECIMAL
      int cod_operacao = (valor_l - (valor_l%2))/2; // CRIA UM VARIAVEL COM VALOR ENTRE 0 E 3
      // OPERAÇÃO = 0 -> COMPLEMENTO DE 1
      // OPERAÇÃO = 1 -> COMPLEMENTO DE 2
      // OPERAÇÃO = 2 -> ADIÇÃO 
      // OPERAÇÃO = 3 -> SUBTRAÇÃO
      if(cod_operacao == 0){  //  COMPLEMENTO DE 1
        lcd.setCursor(0, 1); //
        lcd.print("COMPL 1:"); // IMPRIME A OPERAÇÃO
        int resultado = 63 - valor; // OPERAÇÃO EM DECIMAL 
        //CONVERTE EM BINARIO
        int sobra2 = resultado;
        int s0 = (sobra2/32);
        sobra2 -= s0*32;
        int s1 = (sobra2/16);
        sobra2 -= s1*16;
        int s2 = (sobra2/8);
        sobra2 -= s2*8;
        int s3 = (sobra2/4);
        sobra2 -= s3*4;
        int s4 = (sobra2/2);
        sobra2 -= s4*2;                  
        int s5 = (sobra2/1);        
        // PRINTA O RESULTADO
        char saida[6];
        sprintf(saida,"%d%d%d%d%d%d", s0, s1, s2, s3, s4, s5);
        lcd.setCursor(9, 1); // Define a posição do cursor
        lcd.print(saida); // Imprime o texto "Binario:"  
      }

      if(cod_operacao == 1){  //  COMPLEMENTO DE 2
        lcd.setCursor(0, 1);
        lcd.print("COMPL 2:"); // IMPRIME A OPERAÇÃO
        int resultado = 64 - valor; // RESULTADO EM DECIMAL 
        // CONVERTE EM BINARIO
        int sobra2 = resultado;
        int s0 = (sobra2/32);
        sobra2 -= s0*32;
        int s1 = (sobra2/16);
        sobra2 -= s1*16;
        int s2 = (sobra2/8);
        sobra2 -= s2*8;
        int s3 = (sobra2/4);
        sobra2 -= s3*4;
        int s4 = (sobra2/2);
        sobra2 -= s4*2;                  
        int s5 = (sobra2/1);        
        //PRINTA O RESULTADO
        char saida[6];
        sprintf(saida,"%d%d%d%d%d%d", s0, s1, s2, s3, s4, s5);
        lcd.setCursor(9, 1); // Define a posição do cursor
        lcd.print(saida); // Imprime o texto "Binario:"  
        lcd.printstr("");
      }
            
      if(cod_operacao == 2){  //  ADIÇÃO
        lcd.setCursor(0, 1); // 
        lcd.print("ADICAO :"); // IMPRIME A OPERAÇÃO
        int resultado = valor_l + valor_r; // RESULTADO EM DECIMAL 
        //CONVERTE EM BINARIO
        int sobra2 = resultado;
        int s0 = (sobra2/32);
        sobra2 -= s0*32;
        int s1 = (sobra2/16);
        sobra2 -= s1*16;
        int s2 = (sobra2/8);
        sobra2 -= s2*8;
        int s3 = (sobra2/4);
        sobra2 -= s3*4;
        int s4 = (sobra2/2);
        sobra2 -= s4*2;                  
        int s5 = (sobra2/1);
        //PRINTA O RESULTADO
        char saida[6];
        sprintf(saida,"%d%d%d%d%d%d", s0, s1, s2, s3, s4, s5);
        lcd.setCursor(9, 1); // Define a posição do cursor
        lcd.print(saida); // Imprime o texto "Binario:"  
        lcd.printstr("");  
      }

      if(cod_operacao == 3){ //SUBTRAÇÃO
        lcd.setCursor(0, 1); 
        int resultado;
        if(valor_l < valor_r){ // VALOR NEGATIVO
          lcd.print("SUB/c-1:");
          int compl1 = valor_r - valor_l; // RESULTADO EM DECIMAL 
          resultado = 63 - compl1; // CONVERTE EM COMPLEMENTO DE 1
        }else{
          lcd.print("SUBTRAC:"); 
          resultado = valor_l - valor_r;
        }
        // CONVERTE EM BINARIO
        int sobra2 = resultado;
        int s0 = (sobra2/32);
        sobra2 -= s0*32;
        int s1 = (sobra2/16);
        sobra2 -= s1*16;
        int s2 = (sobra2/8);
        sobra2 -= s2*8;
        int s3 = (sobra2/4);
        sobra2 -= s3*4;
        int s4 = (sobra2/2);
        sobra2 -= s4*2;                  
        int s5 = (sobra2/1);
        // PRINTA O RESULTADO
        char saida[6];
        sprintf(saida,"%d%d%d%d%d%d", s0, s1, s2, s3, s4, s5);
        lcd.setCursor(9, 1); // Define a posição do cursor
        lcd.print(saida); // Imprime o texto "Binario:"  
        lcd.printstr("");    
      }
      // PRINTA A ENTRADA
      char binario[7];
      sprintf(binario,"%d%d%d%d%d%d", e0, e1, e2, e3, e4, e5);
      lcd.setCursor(9, 0); // Define a posição do cursor
      lcd.print(binario); // Imprime o texto "Binario:" 
    }
  }
