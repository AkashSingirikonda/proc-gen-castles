#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

class Tile
{
public:
    Tile();

    void setRules(std::unordered_map<int, std::vector<int>>* tileMap);
    std::unordered_map<int, std::vector<int>>* tileMap = nullptr;
    int m_id;
    std::vector<int> m_edges;
    std::vector<int> m_front;
    std::vector<int> m_back;
    std::vector<int> m_right;
    std::vector<int> m_left;
};

#endif // TILE_H
