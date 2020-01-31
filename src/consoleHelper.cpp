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
    return getch_(0);
}

char CInputReader::getche()
{
    return getch_(1);
}

void CInputReader::initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        current.c_lflag |= ECHO; /* set echo mode */
    } else {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

void CInputReader::resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

char CInputReader::getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

