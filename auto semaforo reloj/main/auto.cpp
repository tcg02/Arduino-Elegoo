#include <Arduino.h>
#include "timer.h"
#include "auto.h"

#define ENA 10 
#define IN1 9 //Izquierda retrocede
#define IN2 8 //Izquierda avanza
#define ENB 5 
#define IN3 7 //Derecha retrocede
#define IN4 6 //Derecha avanza
#define LED 13

#define AUTO_AVANZAR 0
#define AUTO_RETROCEDER 1
#define AUTO_DERECHA 2
#define AUTO_IZQUIERDA 3
#define AUTO_DER_REV 4
#define AUTO_IZQ_REV 5
#define AUTO_STOP 6

volatile int state = LOW;
static int state_auto;
static int ABS = 135;
char getstr;

void auto_setup()
{
  pinMode(LED, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  state_auto = AUTO_STOP;
  auto_stop();
}

void auto_loop()
{
  
  
    getstr = Serial.read();

    switch(getstr)
    {
      case 'f':
        auto_avanzar();
        break;
      case 'b':
        auto_retroceder();
        break;
      case 'l':
        auto_izquierda();
        break;
      case 'r':
        auto_derecha();
        break;
      case 's':
        auto_stop();
        break;
      case 'A':
        void stateChange();
        break;  
    }

}

void auto_avanzar()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);        
  digitalWrite(IN3, LOW);         
  digitalWrite(IN4, HIGH);        
  Serial.println("AVANZAR");
}
void auto_retroceder()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);       
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);       
  Serial.println("RETROCEDER");
}
void auto_derecha()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("DERECHA");
}
void auto_izquierda()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("IZQUIERDA");
}
void auto_derechaRev()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("DERECHA REVERSA");
}
void auto_izquierdaRev()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("IZQUIERDA REVERSA");
}    
void auto_stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("STOP");
}    

void stateChange()
{
  state = !state;
  digitalWrite(LED, state);  
}
       
