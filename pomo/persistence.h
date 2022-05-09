
/*To be saved, in order:
- currentWorkMinutes
- currentPauseMinutes
- totWorkTime
- totWorkSessions
*/

void persistenceInit();

int getCurrentWorkMinutes();
int getCurrentPauseMinutes();

void setCurrentWorkMinutes(int time);
void setCurrentPauseMinutes(int time);

int getTotWorkTime();
int getTotWorkSessions();

void setTotWorkTime(int time);
void setTotWorkSessions(int sessions);