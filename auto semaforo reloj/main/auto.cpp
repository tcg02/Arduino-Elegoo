#include <Arduino.h>
#include "timer.h"
#include "auto.h"

#define ENA 10 
#define IN1 9 //Izquierda retrocede
#define IN2 8 //Izquierda avanza
#define ENB 5 
#define IN3 7 //Derecha retrocede
#define IN4 6 //Derecha avanza

#define AUTO_AVANZAR 0
#define AUTO_RETROCEDER 1
#define AUTO_DERECHA 2
#define AUTO_IZQUIERDA 3
#define AUTO_DER_REV 4
#define AUTO_IZQ_REV 5
#define AUTO_STOP 6

static int state_auto;

void auto_setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  Serial.begin(9600);
  state_auto = AUTO_STOP;
  
}
void auto_loop()
{
  
  auto_accion();
}

void auto_accion()
{
  if (timer_waitMs(RELOJ_TIMER_5, 1000))
  {
    switch (state_auto)
    {
      case AUTO_AVANZAR:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);        
        digitalWrite(IN3, LOW);         
        digitalWrite(IN4, HIGH);        
        Serial.println("AVANZAR");
        break;
      case AUTO_RETROCEDER:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);       
        digitalWrite(IN3, HIGH);      
        digitalWrite(IN4, LOW);       
        Serial.println("RETROCEDER");
        break;
      case AUTO_DERECHA:
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        Serial.println("DERECHA");
        break;
      case AUTO_IZQUIERDA:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        Serial.println("IZQUIERDA");
        break;
      case AUTO_DER_REV:
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        Serial.println("DERECHA REVERSA");
        break;
      case AUTO_IZQ_REV:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        Serial.println("IZQUIERDA REVERSA");
        break;
      case AUTO_STOP:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
  }
}
