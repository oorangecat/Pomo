#include "persistence.h"
#include "oled.h"
#include "pages.h"  //contains enum pages
#include <Ticker.h>

#define BUTTON1_PIN 1     //ok
#define BUTTON2_PIN 2     //arrow
#define TIMERDELAYMS 999
#define DONEDELAY 2000
#define FAILDELAY 5000
#define EXTENDAMOUNT
#define SETWORKSTEP 5
#define SETPAUSESTEP 2
#define MAXWORK 60
#define MAXPAUSE 20
#define MINWORK 5
#define MINPAUSE 1

enum buttons { button1, button2, none };
enum states { working, paused, none };

Ticker ticker;

int timer=[0,0];
int page=0;
int currentStatus=none
int currentSettings=[25,5];

void startTimer();
void stopTimer();
void timerHandler();
void currentSettingsGet();
void updateStats();   //add a session to stored stats


void setup() {

  persistenceInit();
  setupOled();
  currentSettingsGet();
  pinMode(1, INPUT);
  pinMode(2, INPUT);

  ticker.attach(TIMERDELAY, timerHandler);

}

int lastButton=none;

void loop() {
  
  lastbutton=checkButton();

  if(lastButton==button1){        
        //----------------------------- BUTTON OK BEHAVIOUR
      switch(page){
        case menu_startp:      //MAIN MENU (START) -> START TIMER
          running1();
          page=running1p;
          timer[0]=currentSettings[0];
          timer[1]=0;
          startTimer();
          status=working;

          break;
        case running1p:         //IF TIMER IS RUNNING -> FAIL (much shame)

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

        case readyp:         //IF WAITING AFTER PAUSE -> START TIMER
          timer[0]=currentSettings[0];
          timer[1]=0;
          status=working;
          startTimer();
          running1(timer[0], timer[1]);
          page=running1p;
          break;

        case pausep:        //IF PAUSE -> MAINMENU (no shame)
          stopTimer();
          status=none;
          menu_start();
          page=menu_startp;
          
          break;
        
        case extendp:           //EXTEND PAUSE TIMER by a programmer defined amount
          timer[0]+=EXTENDAMOUNT;
      
          pause(timer[0], timer[1]);
          page=pausep;
          break;

        case menu_statsp:   //MAINMENU (STATS) -> OPEN STATS
          stats_tot(getTotWorkTime);
          page=stats_totp;
          break;
        
        case stats_totp:    //IN STATS -> MAINMENU (STATS)
          menu_stats();
          page=menu_statsp;
          break;
        
        case stats_sessionsp:
          menu_stats();
          page=menu_statsp;
          break;
        
        case stats_rstp:     //ASK IF SURE, RESTORE OR GO BACK
          sure();
          page=surep;
          lastButton=none;        //is stuck till an answer is given
          while(lastButton==none){
            lastButton=checkButton();
            if(lastButton==button1){   //confirm, restore
              setTotWorkSessions(0);
              setTotWorkTime(0);
              menu_start();
              page=menu_startp;
            } else if(lastButton==button2){   //else go back to menu
              stats_rst();
              page=stats_rstp;
            }
          }
          break;

    

        case menu_setp:        //OPEN SETTINGS
          set_work(currentSettings[0]);
          page=set_workp;
          break;

        case set_workp:     //ADD STEP TO WORK TIME SETTING
          currentSettings[0]+=SETWORKSTEP;
          if(currentSettings[0]>MAXWORK)
            currentSettings[0]=MINWORK;
          
          set_work(currentSettings[0]);
          break;

        case set_pausep:    //ADD STEP TO PAUSE TIME SETTING
          currentSettings[1]+=SETPAUSESTEP;
          if(currentSettings[1]>MAXPAUSE)
            currentSettings[1]=MINPAUSE;
          set_pause(currentSettings[1]);
          break;

        case set_savep:       //SAVE SETTINGS -> MAINMENU(SET)
          setCurrentWorkMinutes(currentSettings[0]);
          setCurrentPauseMinutes(currentSettings[1]);
          set();
          page=menu_setp;
          break;

        case set_backp:       //GO BACK WITHOUT SAVING -> MAINMENU(SET)
          currentSettingsGet();
          set();
          page=menu_setp;
          break;
      }
  } else if(lastButton==button2){
        //--------------------------------BUTTON ARROW BEHAVIOUR
        switch(page){
          //LOOP THROUGH MENU
          case menu_startp:   
            menu_stats();
            page=menu_statsp;
            break;

          case menu_statsp:
            menu_set();
            page=menu_setp;
            break;

          case menu_setp:
            menu_start();
            page=menu_startp;
            break;

          //LOOP THROUGH RUNNING PAGES
          case running1p:
            running2(timer[0], timer[1]);
            page=running2p;
            break;
          case running2p:
            running1();
            page=running1p;
            break;

          //LOOP PAUSE PAGES
          case pausep:
            extend();
            page=extend();
            break;
          
          case extendp:
            pause(timer[0],timer[1]);
            page=pausep;
            break;

          //IF READY, GO BACK TO MAIN MENU
          case readyp:    //goo
            menu_start();
            page=menu_startp;
            break;

          //LOOP THROUGH STATS MENU
          case stats_totp:
            stats_sessions(getTotWorkSessions);
            page=stats_sessionsp;
            break;

          case stats_sessionsp:
            stats_rst();
            page=stats_rstp;
            break;

          case stats_rstp:
            stats_tot(getTotWorkTime);
            page=stats_totp;
            break;

          //LOOP THROUGH SET MENU
          case set_workp:
            set_pause(currentSettings[1]);
            page=set_pausep;
            break;

          case set_pausep:
            set_save();
            page=set_savep;
            break;
          
          case set_backp:
            set_back();
            page=set_backp; 
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
  if(timer[0]==0 && timer[1]==0){   //if timer is done
    if(status==working){        //if working, go to pause (set timer again)
      stopTimer();
      done();
      page=donep;
      delay(DONEDELAY);
      timer[0]=currentSettings[1];
      timer[1]=0;
      status=paused;
      startTimer();
      pause(timer[0], timer[1]);
      page=pausep;
      
      //add this session to stats
      updateStats();

    } else if(status==paused){      //if pause, go to ready and wait
      stopTimer();
      ready();
      page=readyp;
    }
    
  } else {              //if timer is running
    timer[1]--;
    if(timer[1]==-1){     //decrement seconds and eventually seconds
      timer[1]=59;
      timer[0]--;
    }

    if(status==working){
      if(page==running2p)   //if WORKING with the clock, update it
        running2(time[0], time[1]);
      else
        running1();         //else update animation
    } else if(status==paused){    //if paused update the clock
      pause(time[0], time[1]);  
    }
  }
}

void currentSettingsGet(){
  currentSettings[0]=getCurrentWorkMinutes();
  currentSettings[1]=getCurrentPauseMinutes();
}


void updateStats(){
  setTotWorkSessions(getTotWorkSessions+1);
  setTotWorkTime(getTotWorkTime+currentSettings[0]);
}