// Código Copiado del Wokwi que se realizó
//Sophia Frankr | 23030

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdint.h>

LiquidCrystal lcd(23, 22, 5, 4, 2, 15, 18, 19, 21, 27); // lcd(rs, enable, D0-D7) //En el wokwi no se necesita pero V0 va a un potenciómetro de 10k para la brillosidad de la pantalla.

#define pot1 12
#define pot2 25

#define PBUp 35
#define PBDown 34

int Vpot1=0;
int Vpot2=0;

float pot2Volt=0.0;
uint8_t contador =0;

//Antirrebote
bool ultimoEstadoUp = HIGH;
bool ultimoEstadoDown = HIGH;

void setup(){
  lcd.begin(16,2);                      //Setup inicial de la pantalla
  lcd.setCursor(0,0);
  lcd.print("Pot1: Pot2 Cont:");

  pinMode(PBUp, INPUT_PULLUP);
  pinMode(PBDown, INPUT_PULLUP);
}

void loop(){
  Vpot1 =analogRead(pot1);        
  Vpot2 =analogRead(pot2);  
  pot2Volt = (Vpot2/4096.0)*3.3;            //Conversión de bits a voltaje

  bool currentEstadoUp = digitalRead(PBUp); //Botón 1 con antirrebote
  if (ultimoEstadoUp == HIGH && currentEstadoUp == LOW) {
    contador=(contador + 1) % 256; // Incrementa el contador y lo envuelve a 256 (8bits)
  }
  ultimoEstadoUp = currentEstadoUp;

  bool currentEstadoDown = digitalRead(PBDown); //Botón 2 con antirrebote
  if (ultimoEstadoDown == HIGH && currentEstadoDown == LOW) {
    contador=(contador - 1) % 256; // Decrementa el contador y lo envuelve a 256 (8bits)
  }
  ultimoEstadoDown = currentEstadoDown;

  //Impresión de los estados
  lcd.setCursor(0,1);
  lcd.print("    "); 
  lcd.setCursor(0,1);
  lcd.print(Vpot1); //Bits leídos

  lcd.setCursor(6,1);
  lcd.print("    "); 
  lcd.setCursor(6,1);
  lcd.print(pot2Volt,2); //Voltaje (convertido de bits)

  lcd.setCursor(12,1);
  lcd.print("    "); 
  lcd.setCursor(12,1); //Contador 0-255 cíclico
  lcd.print(contador);
  delay(50);
}
