#include <iostream>
#include <fstream>

#include <unistd.h>
#include <term.h>

#include <termios.h>
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

static constexpr size_t g_mapWidth = 80;
static constexpr size_t g_mapHeight = 25;

using map_t = char[g_mapWidth][g_mapHeight];
struct pos
{
    size_t col;
    size_t row;
};


void printMap(const map_t& f_map, const pos& car)
{
    clearScreen();
    for(int i = 0; i < g_mapHeight; ++i)
    {
        for(int j = 0; j < g_mapWidth; ++j)
        {
            if(i == car.row && j == car.col)
                std::cout << 'x';
            else
                std::cout << f_map[j][i];
        }
        std::cout << std::endl;
    }
}

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
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

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}


int main()
{
    map_t map;
    
    pos carPosition;
    
    std::fstream fin("/Users/dnoveczky/git/flatland-simulator/data/map", std::fstream::in);
    if(fin.is_open())
    {
        for(int i = 0; i < g_mapHeight; ++i)
        {
            for(int j = 0; j < g_mapWidth; ++j)
            {
                char c;
                fin >> std::noskipws >> c;
                if('x' == c)
                {
                    carPosition = pos{static_cast<size_t>(j),static_cast<size_t>(i)};
                    map[j][i] = ' ';
                }
                else
                {
                    map[j][i] = c;
                }
                
            }
            fin >> std::ws;
        }
    }
    fin.close();
    
    printMap(map, carPosition);
    
    char c = 0;
    
    while(c != 'q')
    {
        c = getch();
        switch (c)
        {
            case 'w':
                carPosition.row -=1;
                break;
            case 'a':
                carPosition.col -= 1;
                break;
            case 's':
                carPosition.row += 1;
                break;
            case 'd':
                carPosition.col += 1;
                break;
            default:
                break;
        }
        printMap(map, carPosition);
    }
    
    
    return 0;
}
