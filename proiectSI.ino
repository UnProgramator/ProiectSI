#include "comunicare.h"
#include "sdistanta.h"
#include "sfotores.h"
#include "stempumid.h"
#include "slumina.h"
#include "smiscare.h"
#include "comandaBec.h"

//initializari
defBec(22);
sDist dstSen(49,48);
sfotores foto(46,A0);
daylightSensorDefine(52);
PYR(8);
STEMPUMID(53);
//end

//variabile si macrodefinitii pentru init-loop
bool nightTime=false;
bool lightsOn=false;
long turnOffTime=-1; //trebuie sa retin secunde;
signed char day_to_night_loop=0; //am nevoie doar pe un bit; 0 inseamna ca nu a fost folosit; >0 trecere zi->noapte; <0 trecere noapte->zi
bool isNight(); //functii de comanda
bool check_for_people(); //functii de comanda

#define isDebugOn true

#define TIME_TO_STAY_ON_AFTER_DETECTION_STOP 20
#define loop_holdout 500
#define day_night_loop_holdout 10

void setup() {
  initBec();
  initDaylightSensor();
  initPYR();
  dstSen.init();
  foto.init();
  bluetoothInit();
}

void loop() {
  if(isNight()){
//aici stau un timp de ... miilisecunde/secunde pentru a ma asigura ca este nevoie sa aprind lumina si ca nu au fost 2-3 citiri eronate. 
//pentru aceasta astept un ciclu de 10 citiri care trebuie sa dea toate ca este noapte; la fel va fi si pentru zi (! noapte)
    if(nightTime==false){
      //day_to_night_loop>0 inseamna ca am tot detectat noapte 
      if(day_to_night_loop>0){
        if(day_to_night_loop==1){//aici s-a terminat loopul de validare a schimbarii starii zi-noapte
          //trimitem la server ca am detectat ca este noapte
          sendInfo(1000);//codul 100 inseaman noapte
          nightTime=true;//setam ca am trecut pe modul de noapte
        }
        else//ciclez prin loop
          day_to_night_loop--;
      }else//aici initializez loopul de trecere zi-noapte
          day_to_night_loop=day_night_loop_holdout;
    }//if(nightTime==false)
    else {
      foto.activate();
      if(check_for_people()){//aici tratez daca e noapte
        if(!lightsOn){
          //aici pornim lumina daca nu e deja pornita
          arindeBec();
          lightsOn=true;
          sendInfo(200);//aici trimit mesaj ca am detectat om
        }
        else{//lumina e deja aprinsa, fie pentru ca inca detectam omul, fie pentru ca nu a trecut perioada de hold de la incetarea detectie omului precedent
          if(turnOffTime!=-1){
            //inseamna ca am detectat un om cand inca era aprinsa lumina de la perioada de hold 
            turnOffTime=-1;
            sendInfo(200);//aici trimit mesaj ca am detectat om
          }
        }
      }
      else{//daca nu (mai) detectam nici un om
        if(lightsOn){
          
          //aici oprim lumina daca e pornita, deoarece nu am mai detectat nici un om
          if(turnOffTime==-1){
            sendInfo("incepe perioada de hold");//debugging reasons
            turnOffTime=TIME_TO_STAY_ON_AFTER_DETECTION_STOP; 
          }else{
            if(--turnOffTime==-1){
              //stingem luminile dupa perioada de hold
              stingeBec();
              lightsOn=false;
            }
            sendInfo("hold ");
              sendInfo(turnOffTime);
         }
        }
      }
    }
  }//if night()
  else{//if night()==false
    if(nightTime){// aici fac oarecum detectia de la noapte la zi; analog cu ce am facut pt trecerea de la zi la noapte
      if(day_to_night_loop<0){
        if(day_to_night_loop==-1){
          //trimitem la server ca am detectat ca este noapte
          sendInfo(1001);//codul 1001 inseaman zi
          nightTime=false;//setam ca am trecut pe modul de noapte
            if(lightsOn){
              lightsOn=false;
              //stingem luminile daca au ramas aprinse de pe timpul de noaptea
              stingeBec();
            }
        }
        else
          day_to_night_loop++;
      }else
          day_to_night_loop=-day_night_loop_holdout;
    }
  }//else-if !night()
  delay(loop_holdout);
}

bool isNight(){//returneaza true daca necesita aprinderea luminiilor daca este noapte sau ceata, altfel false
 //stempumid.h, slumina.h
  if(getDayState()==DAY){
    //Serial.println("zi");
    saveSTUResults();
    if(getHumidity()>HUMIDITY_TRESHHOLD){
      if(getTemp()>30/* *C */){
      //este ceata; transmit si calculatorului ca am detectat ceata
      sendInfo(1002);//codul 1002 inseaman ceata
      return true;//trebuie bec
      }
    }
    //este zi si nu e ceata
    return false;
  }
  //Serial.println("noapte");
  //altfel lumina este prea slaba si trebuie aprins becul
  return true;
}

bool tmp();//functia care inlocuieste senzorul de miscare ars
bool check_for_people(){
  //if(readPirState()==MVDETECT){ // asta ar fi fost linia daca merge senzorul de miscare
  if(tmp()){
    if(foto.detect()){
      //aici am detectat farurile unei masini
      if(dstSen.getDistInTime()<2){//consider ca un om merge cu o viteza <=20 km/h = 1m/180ms -> 2m/360ms; getSpeed masoara viteza
        //aici e verificat ca exista si un om pe trotuar
        return true;//exista om
      }
      return false;//a fost doar o masina
    }
    else{//nu e masina
      return true;//a fost detectata miscare si nu au fost detectate lumina farurilor unei masini
    }
  }
  return false; //nu este detectata miscare
}

//toata partea aceasta este pentru detectia miscarii folosind senzorul de distanta
int v[4];
int lastTrueDist;
int getTrueDist(){
  
  v[0]=dstSen.getDist();
 
  delay(10);
  v[1]=dstSen.getDist();
    
  delay(10);
  v[2]=dstSen.getDist();
    
  delay(10);
  v[3]=dstSen.getDist();
    
  delay(10);
  return (v[0]+v[1]+v[2]+v[3])>>2;//media aritmetic din motiv de debouncing; formula gasita experimental; 
}

bool tmp(){
  int dst = getTrueDist();
  if(lastTrueDist-dst > 20){
    lastTrueDist=dst;
    return true;
  }
  lastTrueDist=dst;
  return false;
}
