#ifndef CELL_H
#define CELL_H

#include "tile.h"
class Cell
{
public:
    Cell(int x, int y, int rez, std::vector<int> options);
    float entropy() {return 0;};
    void update() {};
    void observe() {};

    int m_x;
    int m_y;
    int m_rez;
    std::vector<int> m_options;
    bool m_collapsed = false;

};

#endif // CELL_H
