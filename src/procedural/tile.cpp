#include "tile.h"
#include "iostream"

Tile::Tile()
{

}

void Tile::setRules(std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        // Upper edge
        if (m_edges[0] == tile.m_edges[2]) {
            m_back.push_back(tile);
        }

        // Right edge
        if (m_edges[1] == tile.m_edges[3]) {
            m_right.push_back(tile);
        }

        // Lower edge
        if (m_edges[2] == tile.m_edges[0]) {
            m_front.push_back(tile);
        }

        // Left edge
        if (m_edges[3] == tile.m_edges[1]) {
            m_left.push_back(tile);
        }
    }
}
