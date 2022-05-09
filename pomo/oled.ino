
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "animation.h"
#include "oled.h"


static int lastFrame=0;

void printOled(char *str);


/*
 #Draw a single pixel in white
    display.drawPixel(10, 10, WHITE);
 #Show the display buffer on the screen. You MUST call display() after
 #drawing commands to make them visible on screen!
 display.display();
*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

void setupOled(){
    Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;)
            delay(10000); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(drawDelay);
    // Clear the buffer
    display.clearDisplay();

}

//Basic block for printing text 
void printOled(char *str, int size){
    
    display.clearDisplay();

    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(str);
    display.display(); 
    delay(drawDelay);
}

char *intToChar(int num){
    char ch=num+'0';
    return &ch;
}


void menu_start(){
    printOled("START >", standardSize);
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


void running2(int h, int m){
    char buf[15];
    
    strcat(buf, intToChar(h));
    strcat(buf, ":");
    strcat(buf, intToChar(m));
    printOled(buf, standardSize);
}

void done(){
    printOled("DONE! <3", standardSize);
}

void fail(){
    printOled("FAIL! :(", standardSize);
}

void extend(){
    printOled("Extend", standardSize);
}


void ready(){
    printOled("Ready?", standardSize);
}

void menu_stats(){
    printOled("< STATS >", standardSize);
}

void stats_tot(int totMin){
    char buf[15]="T: ";
    strcat(buf, intToChar(totMin));
    printOled(buf, standardSize);
}

void stats_sessions(int totSessions){
    char buf[15]="S: ";
    strcat(buf, intToChar(totSessions));
    printOled(buf, standardSize);
}

void stats_rst(){
    printOled("< RST");
}

void set(){
    printOled("< SET >");
}

void set_work(int minShown){
    char buf[15]="W:";
    strcat(buf, intToChar(minShown));
    printOled(buf, standardSize);
}

void set_pause(int minShown){
    char buf[15]="S:";
    strcat(buf, intToChar(minShown));
    printOled(buf, standardSize);
}

void set_save(){
    printOled("< SAVE");
}


