#ifndef CELL_H
#define CELL_H

#include <vector>
#include "tile.h"
class Cell
{
public:
    Cell(int x, int y, int rez, std::vector<Tile> options, std::unordered_map<int, std::vector<int>>* tileMap);
    float entropy() {m_options.size();};
    void update() {m_collapsed = bool(this->entropy() == 1);};
    void observe() {
        if (!m_options.empty()) {
            m_options = {m_options[std::rand() % m_options.size()]};  // Randomly choose an option
            m_collapsed = true;
        } else {
            std::cerr << "observed cell with no options" << std::endl;
        }
    };

    int m_x;
    int m_y;
    int m_rez;
    std::unordered_map<int, std::vector<int>>* m_tileMap;
    std::vector<Tile> m_options;
    bool m_collapsed = false;

};

#endif // CELL_H
