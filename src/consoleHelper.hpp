#pragma once
#include <termios.h>

void clearScreen();

class CInputReader
{
public:
    /* Read 1 character without echo */
    char getch();
    
private:
    
    /* Initialize new terminal i/o settings */
    void initTermios();
    
    /* Restore old terminal i/o settings */
    void resetTermios();
    
    termios old, current;
};
