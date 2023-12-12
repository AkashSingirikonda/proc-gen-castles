#ifndef GRID_H
#define GRID_H

#include "tile.h"

#include <iostream>
#include <vector>
#include "cell.h"
class Grid
{
public:
    Grid(int width, int height, int rez, std::vector<int> options);
    void initiate(int rez, std::vector<Tile> options);
    void collapse();
    Cell* heuristicPick();
    int m_width;
    int m_height;
    int m_rez;
    int m_w;
    int m_h;
    std::vector<std::vector<Cell>> m_grid;
    std::vector<int> m_options;
};

#endif // GRID_H
