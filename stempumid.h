#ifndef __SENZOR_TEMPERATURA_SI_UMIDITATE_H__INCLUDED__
#define __SENZOR_TEMPERATURA_SI_UMIDITATE_H__INCLUDED__
//datasheet: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf

//sursa "https://github.com/adidax/dht11.git"
//momentan folosesc ceva de pe net, o sa scriu propria biblioteca, dupa fisa
#include "extern/umid_temp_sensor/dht11.h"

#define createConection(pinNo) dth11 t; const int dth11Pin = pinNo
#define saveResults() t.read(dth11Pin)
#define getTemp() t.temperature
#define getHumidity() t.humidity

#endif
