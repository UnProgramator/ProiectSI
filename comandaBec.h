#ifndef __MODUL_BEC_H__INCLUDED__
#define __MODUL_BEC_H__INCLUDED__

#define defBec(port) const int becPt=port
#define initBec() pinMode(becPt, OUTPUT)
#define arindeBec() digitalWrite(becPt, HIGH)
#define stingeBec() digitalWrite(becPt, LOW)

#endif
