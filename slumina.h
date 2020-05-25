#ifndef __SENZOR_INTENSITATE_LUMINOASA_H__INCLUDED__
#define __SENZOR_INTENSITATE_LUMINOASA_H__INCLUDED__
//nu am gasit nici un cod, deci nici un datasheet
//informatii: https://ardushop.ro/ro/home/88-modul-senzor-lumina-intensitate-luminoasa.html?search_query=Modul+senzor+lumina+-+intensitate+luminoasa&results=410
//din cate am cautat pe net despre senzori de lumina, am descoperit:
//iesirea DO este iesire digitala (era fie AO fie DO la ceilalti senzori, eu am acesta care are doar iesire digitala)
//ajustarea luminozitatii si face cu ajutorul releuleui

#include "Arduino.h"

#define daylightSensorDefine(x) const int daylightSensor = x
#define initDaylightSensor() pinMode(daylightSensor, INPUT)
#define getDayState() digitalRead(daylightSensor)
#define DAY LOW
#define NIGHT HIGH

#endif
