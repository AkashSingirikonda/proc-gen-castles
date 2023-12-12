#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
class Tile
{
public:
    Tile();

    void setRules(std::vector<Tile>& tiles);

    int index = -1;
    std::vector<bool> m_edges;
    std::vector<Tile> m_front;
    std::vector<Tile> m_back;
    std::vector<Tile> m_right;
    std::vector<Tile> m_left;
};

#endif // TILE_H
