#include "tile.h"
#include "iostream"

#include <unordered_map>
#include <set>

Tile::Tile()
{

}

void Tile::setRules(std::unordered_map<int, std::vector<int>>* tileMap) {
    for (auto& tile : *tileMap) {
        // Backwards Edge
        if (m_edges[0] == tile.second[2]) {
            m_back.push_back(tile.first);
        }

        // Right edge
        if (m_edges[1] == tile.second[3]) {
            m_right.push_back(tile.first);
        }

        // Front
        if (m_edges[2] == tile.second[0]) {
            m_front.push_back(tile.first);
        }

        // Left edge
        if (m_edges[3] == tile.second[1]) {
            m_left.push_back(tile.first);
        }
    }
}
