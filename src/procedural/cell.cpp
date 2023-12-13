#include "cell.h"

Cell::Cell(int x, int y, int rez, std::vector<Tile> options, std::unordered_map<int, std::vector<int>>* tileMap) {
    m_x = x;
    m_y = y;
    m_rez = rez;
    m_options = options;
    m_tileMap = tileMap;
    m_collapsed = false;
}
