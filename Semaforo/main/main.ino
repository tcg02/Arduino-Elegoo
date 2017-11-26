

/******************************************************************
  Programa: Ejemplo de uso del LCD Keypad Shield

  Objetivo:
    Mostrar los aspectos bÃ¡sicos de funcionamiento del LCD Keypad Shield
    Manejar una entrada analÃ³gica

  Aspectos a destacar:
    -Lectura de la entrada analogica

  VersiÃ³n: 0.6 del 19 de Junio de 2017
  Autor: Mauricio DÃ¡vila
  RevisiÃ³n: -

* *******************************************************************/
#include "reloj.h"
#include "timer.h"
#include "semaforo.h"


/** \brief  Se invoca una sola vez cuando el programa empieza.
            Se utiliza para inicializar los modos de trabajo
            de los pines, el puerto serie, etc...
   \param void
   \return void
*/
void setup(void)
{

  timer_setup();
  //reloj_setup(); // inicializo el reloj
  //semaforo_setup(); // inicializo el semaforo
}


/** \brief  Contiene el programa que se ejecutarÃ¡ cÃ­clicamente

   \param void
   \return void
*/
void loop(void)
{
  timer_loop();
  //reloj_loop();
  //semaforo_loop();
}

