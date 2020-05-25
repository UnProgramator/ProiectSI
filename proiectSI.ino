//#include "comunicare.h"
#include "sdistanta.h"
#include "sfotores.h"
#include "stempumid.h"
#include "slumina.h"
#include "smiscare.h"
#include "comandaBec.h"

//initializari



//end

//variabile si macrodefinitii pentru init-loop
bool nightTime=false;
bool lightsOn=false;
unsigned long turnOffTime=-1; //trebuie sa retin secunde;
signed char day_to_night_loop=0; //am nevoie doar pe un bit; 0 inseamna ca nu a fost folosit; >0 trecere zi->noapte; <0 trecere noapte->zi
bool isNight(); //functii de comanda
bool check_for_people(); //functii de comanda

#define isDebugOn true

#define TIME_TO_STAY_ON_AFTER_DETECTION_STOP 250
#define loop_holdout 500
#define day_night_loop_holdout 10

void setup() {

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
          #warning "needImplemented BT serial"
          nightTime=true;//setam ca am trecut pe modul de noapte
        }
        else//ciclez prin loop
          day_to_night_loop--;
      }else//aici initializez loopul de trecere zi-noapte
          day_to_night_loop=day_night_loop_holdout;
    }//if(nightTime==false)
    else if(check_for_people()){//aici tratez daca e noapte
      if(!lightsOn){
        //aici pornim lumina daca nu e deja pornita
        arindeBec();
      }
      else{//lumina e deja aprinsa, fie pentru ca inca detectam omul, fie pentru ca nu a trecut perioada de hold de la incetarea detectie omului precedent
        if(turnOffTime!=-1){
          //inseamna ca am detectat un om cand inca era aprinsa lumina de la perioada de hold 
          turnOffTime=-1;
        }
      }
    }
    else{//daca nu (mai) detectam nici un om
      if(lightsOn){
        //aici oprim lumina daca e pornita, deoarece nu am mai detectat nici un om
        if(turnOffTime==-1)
          turnOffTime=TIME_TO_STAY_ON_AFTER_DETECTION_STOP; 
         else
          if(--turnOffTime<0){
            //stingem luminile dupa perioada de hold
            stingeBec();
          }
      }
    }
    
  }//if night()
  else{//if night()==false
    if(nightTime){// aici fac oarecum detectia de la noapte la zi; analog cu ce am facut pt trecerea de la zi la noapte
      if(day_to_night_loop<0){
        if(day_to_night_loop==-1){
          //trimitem la server ca am detectat ca este noapte
          #warning "needImplemented"
          nightTime=true;//setam ca am trecut pe modul de noapte
        }
        else
          day_to_night_loop++;
      }else
          day_to_night_loop=-day_night_loop_holdout;
    }
    if(lightsOn){
      lightsOn=false;
      //stingem luminile daca au ramas aprinse de pe timpul de noaptea
      stingeBec();
    }
  }//else-if !night()
  delay(loop_holdout);
}

bool isNight(){//returneaza true daca necesita aprinderea luminiilor daca este noapte sau ceata, altfel false


  return true;
}


bool check_for_people(){


  
}
