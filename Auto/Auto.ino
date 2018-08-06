#include <Arduino.h>
#include "timer.h"
#include "auto.h"

void setup()
{
  auto_setup();
  timer_setup();
}

void loop()
{
  auto_loop();
  timer_loop();
}
