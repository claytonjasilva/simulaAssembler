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

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void setup() {
  Serial.begin(9600); 
  lcd.begin(16, 2); 
}

void loop() {
  if (Serial.available()) { 
    String input = Serial.readString();
    
    int value = input.toInt();
    int soma =(value);
    int subs =(value);
    int comp = ~value;
    int comp2= -1*(value);
    

    if (value >= 0 and value <= 15) { 
      lcd.clear(); 
      lcd.println("cp1: " );
      lcd.println(comp, HEX);
      lcd.println(comp, BIN);
    
      delay(5000);
      lcd.clear();
      lcd.println("cp2: " );
      lcd.println(comp2, HEX);
      lcd.println(comp2,BIN);
      
     
    }
    else if (value >15  and value <=31 ) { 
      lcd.clear(); 
      lcd.println("Soma: "); 
      lcd.print(soma, BIN);
    }
    else if (value >31  and value <=47 ) { 
      lcd.clear(); 
      lcd.print("SUBS: "); 
      lcd.print(subs, BIN); 
    }
     else if (value >47  and value <=63 ) { 
      lcd.print("Sub comp");
    }else { 
      lcd.clear(); 
      lcd.print("Valor inválido!"); 
    }
  }
}
