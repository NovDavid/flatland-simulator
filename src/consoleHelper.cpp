#include "consoleHelper.hpp"

#include <unistd.h>
#include <term.h>

#include <stdio.h>


void clearScreen()
{
    if (!cur_term)
    {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }
    
    putp( tigetstr( "clear" ) );
}


char CInputReader::getch()
{
    char ch;
    initTermios();
    ch = getchar();
    resetTermios();
    return ch;
    
}

void CInputReader::initTermios()
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    
    current.c_lflag &= ~ECHO; /* set no echo mode */
    
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

void CInputReader::resetTermios()
{
    tcsetattr(0, TCSANOW, &old);
}

