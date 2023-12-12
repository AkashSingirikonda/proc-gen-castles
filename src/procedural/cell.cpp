#include "cell.h"

Cell::Cell(int x, int y, int rez, std::vector<Tile> options) {
    m_x = x;
    m_y = y;
    m_rez = rez;
    m_options = options;
    m_collapsed = false;
}
