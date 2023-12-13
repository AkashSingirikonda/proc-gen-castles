#ifndef GRID_H
#define GRID_H

#include "tile.h"

#include <iostream>
#include <vector>
#include "cell.h"
#include "unordered_map"
#include "set"

class Grid
{
public:
    Grid(int width, int height, int rez, std::vector<Tile> options, std::unordered_map<int, std::vector<int>> m_tileMap);
    void initiate(int rez, std::vector<Tile> options);
    void collapse();
    Cell* heuristicPick();
    int m_rez;
    int m_w;
    int m_h;
    std::unordered_map<int, std::vector<int>> m_tileMap;
    std::vector<std::vector<Cell*>> m_grid;
    std::vector<Tile> m_options;
    void printGrid();
};

#endif // GRID_H
