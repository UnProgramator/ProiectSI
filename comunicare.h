#ifndef __MODUL_COMUNICARE_H__INCLUDED__
#define __MODUL_COMUNICARE_H__INCLUDED__

//http://myosuploads3.banggood.com/products/20190515/20190515050356JDY-18-V1.5Englishmanual.pdf
#define bluetoothInit() Serial1.begin(9600)
#define getInt() Serial1.parseInt()
#define getFloat() Serial.parseFloat()
#define getString() Serial1.readString()
#define sendInfo(x) Serial1.write(x)
#define bytesAvailable() Serial.available()
#define BluetoothAvailable() Serial1

#endif
