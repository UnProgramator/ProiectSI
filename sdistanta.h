#ifndef __SENZOR_DISTANTA_H__INCLUDED__
#define __SENZOR_DISTANTA_H__INCLUDED__

#include "Arduino.h"

//datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
//exista posibilitatea sa renuntam la acest senzor in proiectul fina. nu am decis inca, dar pare sa fie inutil, se pare ca nu ar aduce informatii utile, ramane sa vedem la testare
class sDist{
public:
  sDist(int triggerPin, int echoPin);
  float getDist();

  //aceasta functie este folosita pentru a masura viteza unui obiect, blocheaza arduino pentru milliseconds microsecunde
  float getSpeed(int microseconds); 

  //aceste 2 functii sunt folosite pentru a masura viteza unui obiect, fara a bloca arduino pe perioada dintre esantioanele de distanta
  void initalMeasure();
  float getSpeed();
  
private:
  const int trig, echo;
  float initial_distance;
  unsigned long initial_time;
};

#endif
