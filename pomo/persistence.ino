#include <EEPROM.h>
#include "persistence.h"

/*To be saved, in order:
- currentWorkMinutes 0
- currentPauseMinutes 4
- totWorkTime 8
- totWorkSessions 12
*/


#define EEPROM_SIZE 64      //32bytes allocated
#define INT_SIZE 4
#define CURRENTWORKADDRESS 0
#define CURRENTPAUSEADDRESS 4
#define TOTWORKTIMEADDRESS 8
#define TOTWORKSESSIONSADDRESS 12

#define ADDRESS


void persistenceInit(){
      EEPROM.begin(EEPROM_SIZE);
      delay(100);
}
int getCurrentWorkMinutes(){
    return EEPROM.read(CURRENTWORKADDRESS);
}
int getCurrentPauseMinutes(){
    return EEPROM.read(CURRENTPAUSEADDRESS);
}

void setCurrentWorkMinutes(int time){
    EEPROM.put(CURRENTWORKADDRESS, time);
    EEPROM.commit();
}
void setCurrentPauseMinutes(int time){
    EEPROM.put(CURRENTPAUSEADDRESS, time);
    EEPROM.commit();
}

int getTotWorkTime(){
    return EEPROM.read(TOTWORKTIMEADDRESS);
}
int getTotWorkSessions(){
    return EEPROM.read(TOTWORKSESSIONSADDRESS);
}

void setTotWorkTime(int time){
    EEPROM.put(TOTWORKTIMEADDRESS, time);
    EEPROM.commit();
}
void setTotWorkSessions(int sessions){
    EEPROM.put(TOTWORKSESSIONSADDRESS, sessions);
    EEPROM.commit();
}
