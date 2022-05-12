#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1
#define OLED_ADDRESS 0x3C

#define drawDelay 5
#define standardSize 3
#define frameNum 15


void setupOled();

void menu_start();
void running1();
void running2(int m, int s);
void done();
void fail();
void pause(int m, int s);
void extend();
void ready();

void sure();

void menu_stats();
void stats_tot(int totMin);
void stats_sessions(int totSessions);
void stats_rst();

void menu_set();
void set_work(int minShown);
void set_pause(int minShown);
void set_save();
void set_back();
