#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <oled.h>

#define drawDelay 5
#define standardSize 5

void printOled(char[] str);

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
            sleep(10000); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(drawDelay);
    // Clear the buffer
    display.clearDisplay();

}

//Basic block for printing text 
void printOled(char[] str, int size){
    
    display.clearDisplay();

    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(str);
    display.display(); 
    delay(drawDelay);
}

}
void menu_start(){
     printOled("START >", standardSize);

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

void ready(){
    printOled("Ready?", standardSize);
}

void menu_stats(){
    printOled("< STATS >", standardSize);
}

void stats_tot(int totMin){
    printOled("T: %d",totMin, standardSize);
}

void stats_sessions(int totSessions){
    printOled("S: %d", totSessions);
}

void stats_rst(){
    printOled("< RST");
}

void set(){
    printOled("< SET >");
}

void set_work(int minShown){
    printOled("W:%d", minShown);
}

void set_pause(int minShown){
    printOled("P:%d", minShown);
}

void set_save(){
    printOled("< SAVE");
}


