#include "persistence.h"
#include "oled.h"
#include "pages.h"  //contains enum pages
#include <Ticker.h>

#define BUTTON1_PIN 1     //ok
#define BUTTON2_PIN 2     //arrow
#define TIMERDELAYMS 999
#define DONEDELAY 2000
#define FAILDELAY 5000

enum buttons { button1, button2, none };
enum states { working, paused, none };

Ticker ticker;

int timer=[0,0];
int page=0;
int currentStatus=none
int currentSettings[25,5];

void startTimer();
void stopTimer();
void timerHandler();

void setup() {

  persistenceInit();
  setupOled();
  pinMode(1, INPUT);
  pinMode(2, INPUT);

  ticker.attach(TIMERDELAY, timerHandler);

}

int lastButton=none;

void loop() {
  
  lastbutton=checkButton();

  if(lastButton==button1){

      switch(page){
        case startp:
          running1();
          page=running1p;
          timer[0]=currentSettings[0];
          timer[1]=0;
          startTimer();
          status=working;

          break;
        case running1p:
          stopTimer();
          status=none;
          fail();
          page=failp;
          delay(FAILDELAY);
          menu_start();
          page=menu_startp;
          break;

        case running2p:
          stopTimer();
          status=none;
          fail();
          page=failp;
          delay(FAILDELAY);
          menu_start();
          page=menu_startp;
          break;
        

      }
  }

  if(page==pausep || page==pausep){
    ticker.attach(TIMERDELAY, timerHandlerPause)
  }
}


int checkButton(){

  if(digitalRead(BUTTON1_PIN)==HIGH)
    return button1;
  else if (digitalRead(BUTTON2_PIN) ==HIGH)
    return button2;
  else
    return none;

}


void startTimer(){
  timer.attach_ms(TIMERDELAYMS, timerHandler);
}
void stopTimer(){
  timer.detach();
};

void timerHandler(){
  if(timer[0]==0 && timer[1]==0){
    if(status==working){
    stopTimer();
    done();
    page=donep;
    delay(DONEDELAY);
    pause();
    page=pausep;
    } else if(status==paused){
      stopTimer();
      done();
      page=donep;
      delay(DONEDELAY);
      page=donep;
      pause();
      page=pausep
    }
    
  } else {
    timer[1]--;
    if(timer[1]==-1){
      timer[1]=59;
      timer[0]--;
    }

    if(page==running2p)
      running2(time[0], time[1]);
  }
}