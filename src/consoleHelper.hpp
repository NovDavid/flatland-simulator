#pragma once
#include <termios.h>

void clearScreen();

class CInputReader
{
public:
    /* Read 1 character without echo */
    char getch();
    
    /* Read 1 character with echo */
    char getche();
    
private:
    
    /* Initialize new terminal i/o settings */
    void initTermios(int echo);
    
    /* Restore old terminal i/o settings */
    void resetTermios(void);
    
    /* Read 1 character - echo defines echo mode */
    char getch_(int echo);
    
    termios old, current;
};
