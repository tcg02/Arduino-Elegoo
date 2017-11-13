
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "semaforo.h"
#include "timer.h"

#define FALSE 0
#define TRUE 1

#define SEMAFORO_ROJO_1 0
#define SEMAFORO_AMARILLO_1 1
#define SEMAFORO_VERDE_1 2
#define SEMAFORO_WAIT 3

#define SEMAFORO_ROJO_2 4
#define SEMAFORO_AMARILLO_2 5
#define SEMAFORO_VERDE_2 6
#define SEMAFORO_WAIT_2 7
#define SEMAFORO_VERDE_2_2 6

#define LED_PIN_ROJO 5
#define LED_PIN_AMARILLO 6
#define LED_PIN_VERDE 7

#define LED_PIN_ROJO_2 8
#define LED_PIN_AMARILLO_2 9
#define LED_PIN_VERDE_2 10

#define TIEMPO_VERDE1 6000
#define TIEMPO_VERDE2  8000
#define TIEMPO_AMARILLO 2000

static int state_semaforo;
static int state_semaforo_2;
static int tiempoRojo1;
static int tiempoRojo2;

/** \brief  Se invoca una sola vez cuando el programa empieza.
            Se utiliza para inicializar los modos de trabajo
            de los pines, el puerto serie, etc...
   \param void
   \return void
*/
void semaforo_setup(void)
{
  Serial.begin(9600);
  state_semaforo = SEMAFORO_ROJO_1;
  state_semaforo_2 = SEMAFORO_VERDE_2;
  pinMode(LED_PIN_AMARILLO, OUTPUT);
  pinMode(LED_PIN_ROJO, OUTPUT);
  pinMode(LED_PIN_VERDE, OUTPUT);
  pinMode(LED_PIN_AMARILLO_2, OUTPUT);
  pinMode(LED_PIN_ROJO_2, OUTPUT);
  pinMode(LED_PIN_VERDE_2, OUTPUT);
  tiempoRojo2 = TIEMPO_VERDE1 + TIEMPO_AMARILLO; 
  tiempoRojo1 = TIEMPO_VERDE2 + TIEMPO_AMARILLO; 
}


/** \brief  Contiene el programa del semaforo que se ejecutará cíclicamente

   \param void
   \return void
*/
void semaforo_loop(void)
{

  if ( state_semaforo == SEMAFORO_ROJO_1 && timer_waitMs(RELOJ_TIMER_4, 2000))
  {
    state_semaforo = SEMAFORO_AMARILLO_1;
  }
  else if ( state_semaforo == SEMAFORO_AMARILLO_1 && timer_waitMs(RELOJ_TIMER_4, 1000))
  {
    state_semaforo = SEMAFORO_VERDE_1;
  }
  else if ( state_semaforo == SEMAFORO_VERDE_1 && timer_waitMs(RELOJ_TIMER_4, 3000))
  {
    state_semaforo = SEMAFORO_WAIT;
  }

  if( state_semaforo_2 == SEMAFORO_VERDE_2 && timer_waitMs(RELOJ_TIMER_6,TIEMPO_VERDE2))
  {
      state_semaforo_2 = SEMAFORO_AMARILLO_2;      
  }
  else if( state_semaforo_2 == SEMAFORO_AMARILLO_2 && timer_waitMs(RELOJ_TIMER_6,TIEMPO_AMARILLO))
  {
      state_semaforo_2= SEMAFORO_ROJO_2;
  }      
  else if( state_semaforo_2 == SEMAFORO_ROJO_2 && timer_waitMs(RELOJ_TIMER_6,tiempoRojo2))
  {
      state_semaforo_2= SEMAFORO_WAIT_2;
  } 

  if (timer_waitMs(RELOJ_TIMER_5, 1000))
  {
    switch (state_semaforo)
    {
      case SEMAFORO_ROJO_1:
      case SEMAFORO_WAIT:
        Serial.println("ROJO");
        digitalWrite(LED_PIN_ROJO, HIGH);
        digitalWrite(LED_PIN_AMARILLO, LOW);
        digitalWrite(LED_PIN_VERDE, LOW);
        break;
      case SEMAFORO_AMARILLO_1:
        Serial.println("AMARILLO");
        digitalWrite(LED_PIN_ROJO, LOW);
        digitalWrite(LED_PIN_AMARILLO, HIGH);
        digitalWrite(LED_PIN_VERDE, LOW);
        break;
      case SEMAFORO_VERDE_1:
        Serial.println("VERDE");
        digitalWrite(LED_PIN_ROJO, LOW);
        digitalWrite(LED_PIN_AMARILLO, LOW);
        digitalWrite(LED_PIN_VERDE, HIGH);
        break;
    }
  }
  if (timer_waitMs(RELOJ_TIMER_7, 1000))
  {
    switch (state_semaforo_2)
    {
      case SEMAFORO_ROJO_2:
      digitalWrite(LED_PIN_ROJO_2, HIGH);
      digitalWrite(LED_PIN_AMARILLO_2, LOW);
      digitalWrite(LED_PIN_VERDE_2, LOW);
      Serial.println("ROJO");
      break;
    case SEMAFORO_AMARILLO_2:
      digitalWrite(LED_PIN_ROJO_2, LOW);
      digitalWrite(LED_PIN_AMARILLO_2, HIGH);
      digitalWrite(LED_PIN_VERDE_2, LOW);
      Serial.println("AMARILLO");
      break;
    case SEMAFORO_VERDE_2:
    case SEMAFORO_WAIT_2:
      digitalWrite(LED_PIN_ROJO_2, LOW);
      digitalWrite(LED_PIN_AMARILLO_2, LOW);
      digitalWrite(LED_PIN_VERDE_2, HIGH);
      Serial.println("VERDE");
      break;
      }
    }
}

void semaforo_start()
{
  if (state_semaforo_2 == SEMAFORO_WAIT_2)
    state_semaforo = SEMAFORO_ROJO_1;
    state_semaforo_2 = SEMAFORO_VERDE_2;
}

