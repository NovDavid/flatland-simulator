#include "consoleHelper.hpp"

#include <iostream>
#include <fstream>

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
    CInputReader keyboardIn;
    
    while(c != 'q')
    {
        c = keyboardIn.getch();
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
