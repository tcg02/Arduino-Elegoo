
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "semaforo.h"
#include "timer.h"

#define FALSE 0
#define TRUE 1

#define SEMAFORO_ROJO_1 0
#define SEMAFORO_ROJO2_1 8
#define SEMAFORO_AMARILLO_1 1
#define SEMAFORO_VERDE_1 2
#define SEMAFORO_ROJO_2 4
#define SEMAFORO_AMARILLO_2 5
#define SEMAFORO_VERDE_2 6
#define SEMAFORO_VERDE2_2 7
#define SEMAFORO_WAIT1 3
#define SEMAFORO_WAIT2 9

#define TIEMPO_VERDE1 6000
#define TIEMPO_VERDE2  8000
#define TIEMPO_AMARILLO 2000


const int led1 = 11;
const int led2 = 12;
const int led3 = 13;

const int led4 = A3;
const int led5 = A4;
const int led6 = A5;

static int state_semaforo1;
static int state_semaforo2;

static int tiempoRojo1;
static int tiempoRojo2;

/** \brief  Se invoca una sola vez cuando el programa empieza. 
 *          Se utiliza para inicializar los modos de trabajo 
 *          de los pines, el puerto serie, etc... 
 * \param void
 * \return void
 */
void semaforo_setup(void)
{
 
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);

    Serial.begin(9600);
    state_semaforo1 = SEMAFORO_ROJO_1;
    state_semaforo2 = SEMAFORO_VERDE_2;
    tiempoRojo2 = TIEMPO_VERDE1 + TIEMPO_AMARILLO; 
    tiempoRojo1 = TIEMPO_VERDE2 + TIEMPO_AMARILLO; 
}


/** \brief  Contiene el programa del semaforo que se ejecutará cíclicamente
 *          
 * \param void
 * \return void
 */
void semaforo_loop(void)
{

    if( state_semaforo1 == SEMAFORO_ROJO_1 && timer_waitMs(RELOJ_TIMER_4,tiempoRojo1))
    {
        state_semaforo1 = SEMAFORO_VERDE_1;      
    }
    else if( state_semaforo1 == SEMAFORO_VERDE_1 && timer_waitMs(RELOJ_TIMER_4,TIEMPO_VERDE1))
    {
        state_semaforo1 = SEMAFORO_AMARILLO_1;
    }      
    else if( state_semaforo1 == SEMAFORO_AMARILLO_1 && timer_waitMs(RELOJ_TIMER_4,TIEMPO_AMARILLO))
    {
        state_semaforo1 = SEMAFORO_WAIT1;
    }   
      

    
    if( state_semaforo2 == SEMAFORO_VERDE_2 && timer_waitMs(RELOJ_TIMER_6,TIEMPO_VERDE2))
    {
        state_semaforo2 = SEMAFORO_AMARILLO_2;      
    }
    else if( state_semaforo2 == SEMAFORO_AMARILLO_2 && timer_waitMs(RELOJ_TIMER_6,TIEMPO_AMARILLO))
    {
        state_semaforo2= SEMAFORO_ROJO_2;
    }      
    else if( state_semaforo2 == SEMAFORO_ROJO_2 && timer_waitMs(RELOJ_TIMER_6,tiempoRojo2))
    {
        state_semaforo2= SEMAFORO_WAIT2;
    } 
    
    
    if(timer_waitMs(RELOJ_TIMER_5,1000))
    {
        switch(state_semaforo1)
        {
          case SEMAFORO_ROJO_1:
          case SEMAFORO_WAIT1:
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
            digitalWrite(led3,HIGH);
        
            Serial.println("ROJO");
            break;
          case SEMAFORO_AMARILLO_1:
            digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,LOW);
      
            Serial.println("AMARILLO");
            break;
          case SEMAFORO_VERDE_1:
            digitalWrite(led1,HIGH);
            digitalWrite(led2,LOW);
            digitalWrite(led3,LOW);
           
            Serial.println("VERDE");
            break;
        }
    }     

    if(timer_waitMs(RELOJ_TIMER_7,1000))
    {
        switch(state_semaforo2)
        {
          case SEMAFORO_ROJO_2:
          
            digitalWrite(led4,HIGH);
            digitalWrite(led5,LOW);
            digitalWrite(led6,LOW);
            Serial.println("ROJO");
            break;
          case SEMAFORO_AMARILLO_2:
           
            digitalWrite(led4,LOW);
            digitalWrite(led5,HIGH);
            digitalWrite(led6,LOW);
            Serial.println("AMARILLO");
            break;
          case SEMAFORO_VERDE_2:
          case SEMAFORO_WAIT2:
            
            digitalWrite(led4,LOW);
            digitalWrite(led5,LOW);
            digitalWrite(led6,HIGH);
            Serial.println("VERDE");
            break;
        }
    }     
      
}


void semaforo_start()
{
  if(state_semaforo2 == SEMAFORO_WAIT2)
  {
      state_semaforo1 = SEMAFORO_ROJO_1;
      state_semaforo2 = SEMAFORO_VERDE_2;
  }
}



