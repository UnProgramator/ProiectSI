#include "sdistanta.h"
#include "sfotores.h"
#include "stempumid.h"
#include "Arduino.h"

//implementarea clasei pentru distanta
sDist::sDist(int triggerPin, int echoPin):trig{triggerPin}, echo{echoPin}{
  }

void sDist::init(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);
}

float sDist::getDist(){ //exemplu luat de la adresa https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH)*0.034/2; //din calculele prezentate pe siteul atasat
}

float sDist::getSpeed(unsigned int microseconds){
  float inital=this->getDist();
  delayMicroseconds(microseconds);
  return (this->getDist() - initial_distance)/microseconds;
}

float sDist::getDistInTime(){
  float inital=this->getDist();
  delay(360);
  return (this->getDist() - initial_distance)/360;
}

void sDist::initalMeasure(){this->initial_distance=this->getDist(); this->initial_time=micros();}
float sDist::getSpeed(){return (this->getDist() -this->initial_distance)/(micros()-this->initial_time);}

//implementarea clasei pentru fotorezistenta care masoara schimbarile bruste ale intensitatii luminoase
sfotores::sfotores(const int suplyPin, const int readPin):suply{suplyPin}, inp{readPin}{
}

void sfotores::init(){
  pinMode(suply, OUTPUT);
  pinMode(inp, INPUT);
  digitalWrite(suply, LOW);
}

bool sfotores::detect(){
  char tm;
  if(this->isActive){
    this->activate();
    delay(5);
  }
  tm = millis()-(long)activateTime+1;
  if(tm<5){ //daca nu au trecut 5 ms de la activarea senzorului 
    delay(5-tm);//
  }
  if(analogRead(inp)>sfotores::lightBrightnessLimit){
    this->deactivate();
    return true;
  }
  this->deactivate();
  return false;
}
