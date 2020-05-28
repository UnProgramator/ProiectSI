#ifndef __CONTROL_FOTOREZISTENTA_H__INCLUDED__
#define __CONTROL_FOTOREZISTENTA_H__INCLUDED__
#include "Arduino.h"

class sfotores{
public:
  sfotores(const int suplyPin, const int readPin);
  void init();

  inline void activate(){digitalWrite(this->suply, HIGH);isActive=true;activateTime=millis();}
  inline void deactivate(){digitalWrite(this->suply, LOW);isActive=false;}

  inline int readState(){return (isActive ? analogRead(inp) : -1);}
  
  //aceasta calculeaza daca a aparut o diferenta suficient de mare de lumina ca rezultat a trecerii unei masini, cu farurile aprinse
  // va fi folosita pentru a decide daca va fi aprins becul
  bool detect(); 
 
private:
  const int suply, inp;
  bool isActive=false;
  unsigned long activateTime;
  static const unsigned int lightBrightnessLimit=250; 
};

#endif
