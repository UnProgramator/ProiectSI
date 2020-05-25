#ifndef __CONTROL_FOTOREZISTENTA_H__INCLUDED__
#define __CONTROL_FOTOREZISTENTA_H__INCLUDED__
#include "Arduino.h"

class sfotores{
public:
  sfotores(const int suplyPin, const int readPin);

  inline void activate(){digitalWrite(this->suply, HIGH);isActive=true;}
  inline void deactivate(){digitalWrite(this->suply, LOW);isActive=false;}

  inline int readState(){return (isActive ? analogRead(inp) : -1);}

  //aceasta calculeaza daca a aparut o diferenta suficient de mare de lumina ca rezultat a trecerii unei masini, cu farurile aprinse
  // va fi folosita pentru a decide daca va fi aprins becul
  void startDetect(); 
  inline void resetCarDetected(){carDetected=false;}
  inline bool detectCar(){return carDetected;}
  
private:
  const int suply, inp;
  unsigned long timePassed;
  bool carDetected=false;
  unsigned int lastReadValue;
  bool isActive=false;
};

#endif
