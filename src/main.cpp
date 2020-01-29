#include <iostream>
#include <fstream>

static constexpr size_t g_mapWidth = 80;
static constexpr size_t g_mapHeight = 25;

using map_t = char[g_mapWidth][g_mapHeight];

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

    for(int i = 0; i < g_mapHeight; ++i)
    {
        for(int j = 0; j < g_mapWidth; ++j)
        {
            std::cout << map[j][i];
        }
        std::cout << std::endl;
    }
    
    return 0;
}
