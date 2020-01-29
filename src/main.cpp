#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <unistd.h>
#include <term.h>

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

void printMap(const map_t& f_map)
{
    clearScreen();
    for(int i = 0; i < g_mapHeight; ++i)
    {
        for(int j = 0; j < g_mapWidth; ++j)
        {
            std::cout << f_map[j][i];
        }
        std::cout << std::endl;
    }
}

int main()
{
    map_t map;
    
    std::fstream fin("/Users/dnoveczky/git/flatland-simulator/data/map", std::fstream::in);
    if(fin.is_open())
    {
        for(int i = 0; i < g_mapHeight; ++i)
        {
            for(int j = 0; j < g_mapWidth; ++j)
            {
                fin >> std::noskipws >> map[j][i];
            }
            fin >> std::ws;
        }
    }
    std::chrono::seconds sec(1);
    
    
    for(int i = 0; i<10; ++i)
    {
        map[10+i][10] = 'x';
        map[10+i-1][10] = ' ';
        printMap(map);
        
        std::this_thread::sleep_for(sec);
    }
    

    return 0;
}
