#ifndef __MODUL_COMUNICARE_H__INCLUDED__
#define __MODUL_COMUNICARE_H__INCLUDED__

#include "Arduino.h"

//http://myosuploads3.banggood.com/products/20190515/20190515050356JDY-18-V1.5Englishmanual.pdf
#define bluetoothInit() Serial.begin(9600)
#define getInt() Serial.parseInt()
#define getFloat() Serial.parseFloat()
#define getString() Serial.readString()
#define sendInfo(x) Serial.println(x) //in mod normal, cu bt era Serial1.write(x)
#define bytesAvailable() Serial.available()
#define BluetoothAvailable() Serial

/*coduri
 * 1000 - noapte
 * 1001 - zi
 * 1002 - ceata
 * 200  - om
 */

#endif
