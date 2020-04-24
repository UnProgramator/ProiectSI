#ifndef __SENZOR_MISCARE_H__INCLUDED__
#define __SENZOR_MISCARE_H__INCLUDED__
//datasheet: https://cdn-learn.adafruit.com/downloads/pdf/pir-passive-infrared-proximity-motion-sensor.pdf
//datasheet: https://www.mpja.com/download/31227sc.pdf

#define PYR(pinNo) const int pyrPin = pinNo
#define initPYR() pinMode(pinNo, INPUT)
#define readPirState() digitalRead(pinNo)

#endif
