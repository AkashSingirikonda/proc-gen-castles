#include "grid.h"
#include "tile.h"
#include "cell.h"

Grid::Grid(int width, int height, int rez, std::vector<int> options)
{
    m_width = width;
    m_height = height;
    m_rez = rez;
    m_options = options;
}

void Grid::initiate(int rez, std::vector<int> options) {
    for (int i = 0; i < m_w; ++i) {
        std::vector<Cell> curRow;
        m_grid.push_back(curRow);
        for (int j = 0; j < m_h; ++j) {
            Cell curCell = Cell(i, j, m_rez, options);
            m_grid[i].push_back(curCell);
        }
    }
}
