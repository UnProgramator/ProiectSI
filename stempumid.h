#ifndef __SENZOR_TEMPERATURA_SI_UMIDITATE_H__INCLUDED__
#define __SENZOR_TEMPERATURA_SI_UMIDITATE_H__INCLUDED__
//datasheet: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf

//sursa "https://github.com/adidax/dht11.git"
//momentan folosesc ceva de pe net, o sa scriu propria biblioteca, dupa fisa
#include "dht11.h"

#include "Arduino.h"

#define STEMPUMID(pinNo) dht11 t; const int dht11Pin = pinNo
#define saveSTUResults() t.read(dht11Pin)
#define getTemp() t.temperature
#define getHumidity() t.humidity

#define HUMIDITY_TRESHHOLD 80

#endif
