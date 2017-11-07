#include <Arduino.h>
#include <IRremote.h>
#include "timer.h"

#define RECV_PIN 12
#define ENA 10
#define IN1 9
#define IN2 8
#define ENB 5
#define IN3 7
#define IN4 6

#define F 16736925
#define B 16754775
#define L 16720605
#define R 16761405
#define S 16712445
#define UNKNOWN_F 5316027
#define UNKNOWN_B 2747854299
#define UNKNOWN_L 1386468383
#define UNKNOWN_R 553536955
#define UNKNOWN_S 3622325019

#define AUTO_AVANZAR 0
#define AUTO_RETROCEDER 1
#define AUTO_DERECHA 2
#define AUTO_IZQUIERDA 3
#define AUTO_DER_REV 4
#define AUTO_IZQ_REV 5
#define AUTO_WAIT 6

IRrecv irrecv(RECV_PIN);
decode_results results;
static unsigned long val;

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
  state_auto = AUTO_WAIT;
  irrecv.enableIRIn();
}
void auto_loop()
{
  if (irrecv.decode(&results)) {
    val = results.value;
    Serial.println(val);
    irrecv.resume();
    switch (val) {
      case F:
      case UNKNOWN_F: state_auto = AUTO_AVANZAR; break;
      case B:
      case UNKNOWN_B: state_auto = AUTO_RETROCEDER; break;
      case L:
      case UNKNOWN_L: //_mleft(); break;
      case R:
      case UNKNOWN_R: //_mright();break;
      case S:
      case UNKNOWN_S: state_auto = AUTO_WAIT; break;
      default: break;
    }
  }

  if (timer_waitMs(RELOJ_TIMER_5, 1000))
  {
    switch (state_auto)
    {
      case AUTO_AVANZAR:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);        // left wheel goes forward
        digitalWrite(IN3, LOW);         // GIRAN TODAS HACIA ADELANTE
        digitalWrite(IN4, HIGH);        // right wheel goes forward
        Serial.println("AVANZAR");
        break;
      case AUTO_RETROCEDER:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);       //left wheel is back up
        digitalWrite(IN3, HIGH);      //GIRAN LAS 4 PARA ATRAS
        digitalWrite(IN4, LOW);       // right wheel is back up
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
      case AUTO_WAIT:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
  }
}

