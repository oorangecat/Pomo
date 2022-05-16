
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "animation.h"
#include "oled.h"

#include "font.h"


static int lastFrame=0;

void printOled(char *str, int size);


/*
 #Draw a single pixel in white
    display.drawPixel(10, 10, WHITE);
 #Show the display buffer on the screen. You MUST call display() after
 #drawing commands to make them visible on screen!
 display.display();
*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

void setupOled(){

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) { 
        for(;;)
            delay(10000); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(drawDelay);
    // Clear the buffer
    display.clearDisplay();
    display.setFont(&bluesquarebold32pt7b);         //FONT
    

}

//Basic block for printing text 
void printOled(char *str, int size){            //TODO: remove size reference after testing
    
    display.clearDisplay();

    display.setTextSize(size);                
    display.setTextColor(WHITE);
    display.setCursor(0 , 50);
    display.println(str);
    display.display(); 
    delay(drawDelay);
}

char *intToChar(int num){
    char ch=num+'0';
    return &ch;
}


void menu_start(){
    printOled(" START", standardSize);
}

void running1(){
    if(lastFrame>=frameNum)
        lastFrame=0;

    display.clearDisplay();
    display.drawBitmap(0,0,animation[lastFrame],128,64,1);
    
    display.display();
    delay(drawDelay*2);

    lastFrame++;
}


void running2(int m, int s){
    char buf[15];
    //strcat(buf, intToChar(m));    //this makes it crash
    //strcat(buf, ":");
    //strcat(buf, intToChar(s));

    sprintf(buf," %02d:%02d",m,s);
    Serial.print(buf);
    printOled(buf, standardSize);
}

void done(){
    printOled("DONE! <3", standardSize);
}

void fail(){
    printOled(" FAIL :(", standardSize);
}

void pause(int m, int s){           //same as running2, showing clock
    running2(m,s);
}

void extend(){
    printOled("EXTEND", standardSize);
}


void ready(){
    printOled("READY?", standardSize);
}


void sure(){
    printOled("SURE??", standardSize);
}

void menu_stats(){
    printOled(" STATS", standardSize);
}

void stats_tot(int totMin){
    char buf[15];
    sprintf(buf,"T:%05d",totMin);

    printOled(buf, standardSize);
}

void stats_sessions(int totSessions){
    char buf[15];
    sprintf(buf,"S:%05d",totSessions);

    printOled(buf, standardSize);
}

void stats_rst(){
    printOled("  RST", standardSize);
}

void menu_set(){
    printOled("  SET", standardSize);
}

void set_work(int minShown){
    char buf[15];
    sprintf(buf,"W: %02d",minShown);

    printOled(buf, standardSize);
}

void set_pause(int minShown){
    char buf[15];

    sprintf(buf,"P:%02d",minShown);
    printOled(buf, standardSize);
}

void set_save(){
    printOled("  SAVE",standardSize);
}

void set_back(){
    printOled("  BACK", standardSize);
}
