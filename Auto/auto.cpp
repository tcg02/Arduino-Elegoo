#include <Arduino.h>
#include "timer.h"
#include "auto.h"
#define LED 13
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

volatile int state_auto;
static int ABS = 135;
char getstr;

void auto_setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  state_auto = AUTO_STOP;
}

void auto_loop()
{
  getstr = Serial.read();

  if (getstr == 'f')
  {
    state_auto = AUTO_AVANZAR;
  }
  else if (getstr == 'b')
  {
    state_auto = AUTO_RETROCEDER;
  }
  else if (getstr == 'l')
  {
    state_auto = AUTO_IZQUIERDA;
  }
  else if (getstr == 'r')
  {
    state_auto = AUTO_DERECHA;
  }
  else if (getstr == 's')
  {
    state_auto = AUTO_STOP;
  }
  else if (getstr == 'd')
  {
    state_auto = AUTO_DER_REV;
  }
  else if (getstr == 'w')
  {
    state_auto = AUTO_IZQ_REV;
  }

  if (timer_waitMs(RELOJ_TIMER_5, 1000))
  {
    switch (state_auto)
    {
      case AUTO_AVANZAR:
        auto_avanzar();
        Serial.println("AVANZAR");
        break;
      case AUTO_RETROCEDER:
        auto_retroceder();
        Serial.println("RETROCEDER");
        break;
      case AUTO_IZQUIERDA:
        auto_izquierda();
        Serial.println("IZQUIERDA");
        break;
      case AUTO_DERECHA:
        auto_derecha();
        Serial.println("DERECHA");
        break;
      case AUTO_STOP:
        auto_stop();
        Serial.println("STOP");
        break;
      case AUTO_DER_REV:
        auto_derechaRev();
        Serial.println("DERECHA REVERSA");
        break;
      case AUTO_IZQ_REV:
        auto_izquierdaRev();
        Serial.println("IZQUIERDA REVERSA");
        break;
    }
  }
}

void auto_avanzar()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void auto_retroceder()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void auto_derecha()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void auto_izquierda()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void auto_derechaRev()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void auto_izquierdaRev()
{
  analogWrite(ENA, ABS);
  analogWrite(ENB, ABS);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void auto_stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}



