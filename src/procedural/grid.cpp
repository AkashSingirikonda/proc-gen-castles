#include "grid.h"
#include "tile.h"
#include "cell.h"
#include <random>
void Grid::printGrid() {
    for (int i = 0; i < m_grid.size(); i++) {
        for (int j = 0; j < m_grid[i].size(); j++) {
            if (m_grid[i][j]->m_collapsed) {
                std::cout << m_grid[i][j]->m_options[0].m_id;
            } else {
                std::cout << "L";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

Grid::Grid(int width, int height, int rez, std::vector<Tile> options, std::unordered_map<int, std::vector<int>> tileMap)
{
    m_w = width;
    m_h = height;
    m_rez = rez;
    m_options = options;
    m_tileMap = tileMap;
}

void Grid::initiate(int rez, std::vector<Tile> options) {
    for (int i = 0; i < m_w; i++) {
        std::vector<Cell*> curRow;
        m_grid.push_back(curRow);
        for (int j = 0; j < m_h; j++) {
            m_grid[i].push_back(new Cell(i, j, m_rez, options, &m_tileMap));
        }
    }
}

// Arbitrarily pick a cell using entropy heuristic
// There is some randomness in this function.
Cell* Grid::heuristicPick() {
    // Shallow copy of a grid
    std::vector<Cell*> gridCopy;
    for (auto& row : m_grid) {
        for (int i = 0 ; i < row.size(); i++) {
            gridCopy.push_back(row[i]);
        }
    }

    // Sort based on entropy
    std::sort(gridCopy.begin(), gridCopy.end(), [](Cell* a, Cell* b) {
        return a->entropy() < b->entropy();
    });

    // Filter cells with entropy greater than 1
    std::vector<Cell*> filteredGrid = gridCopy;
    auto entropyGreaterThanOne = [](Cell* x) { return x->entropy() > 1.0; };
    filteredGrid.erase(std::remove_if(filteredGrid.begin(), filteredGrid.end(), entropyGreaterThanOne), filteredGrid.end());

    if (filteredGrid.empty()) {
        return nullptr;
    }

    // Find the least entropy cell
    Cell* leastEntropyCell = filteredGrid[0];
    for (int i = 0; i < gridCopy.size(); i++) {
        if (leastEntropyCell->entropy() > gridCopy[i]->entropy()) {
            leastEntropyCell = gridCopy[i];
        }
    }

    filteredGrid.erase(std::remove_if(filteredGrid.begin(), filteredGrid.end(),
                                      [leastEntropyCell](Cell* x) { return x->entropy() != leastEntropyCell->entropy();}),
                       filteredGrid.end());

    // Return a random pick if filtered copy is not empty
    if (!filteredGrid.empty()) {
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(0, filteredGrid.size() - 1);
        Cell* pick = filteredGrid[dis(gen)];
        return pick;
    }

    return nullptr;
}
int pythonMod(int a, int b) {
    return (b + (a % b)) % b;
}
void Grid::collapse() {
    // Pick a random cell using entropy heuristic
    Cell* pick = heuristicPick();
    if (pick) {
        m_grid[pick->m_x][pick->m_y]->observe();
    } else {
        std::cerr << "No pick found" << std::endl;
        return;
    }

    // Shallow copy of the grid
    std::vector<std::vector<Cell*>> nextGrid;
    for (auto& row : m_grid) {
        std::vector<Cell*> curRow;
        for (int i = 0 ; i < row.size(); i++) {
            curRow.push_back(row[i]);
        }
        nextGrid.push_back(curRow);
    }

    // Need to take care of references outside.
    for (int i = 0; i < m_grid.size(); i++) {
        for (int j = 0; j < m_grid[0].size(); j++) {
            if (!m_grid[i][j]->m_collapsed) {
                std::vector<Tile> cumulative_value_options = m_options;

                // Check the backward cell:
                Cell* cell_back = m_grid[pythonMod(i-1, m_h)][j];
                std::vector<int> valid_options;
                for (Tile& option : cell_back->m_options) {
                    valid_options.insert(valid_options.end(), option.m_front.begin(), option.m_front.end());
                }

                std::vector<Tile> temp_options = cumulative_value_options;
                for (int i = 0; i < cumulative_value_options.size(); i++) {
                    std::vector<int>::iterator it = find(valid_options.begin(), valid_options.end(), cumulative_value_options[i].m_id);
                    if (it != valid_options.end()) {
                        temp_options.push_back(cumulative_value_options[i]);
                    }
                }
                cumulative_value_options = temp_options;


                // Check the right cell:
                valid_options.clear();
                Cell* cell_right = m_grid[i][pythonMod(j+1, m_w)];
                for (Tile& option : cell_right->m_options) {
                    valid_options.insert(valid_options.end(), option.m_left.begin(), option.m_left.end());
                }

                temp_options = cumulative_value_options;
                for (int i = 0; i < cumulative_value_options.size(); i++) {
                    std::vector<int>::iterator it = find(valid_options.begin(), valid_options.end(), cumulative_value_options[i].m_id);
                    if (it != valid_options.end()) {
                        temp_options.push_back(cumulative_value_options[i]);
                    }
                }
                cumulative_value_options = temp_options;


                // Check the front:
                valid_options.clear();
                Cell* cell_front = m_grid[pythonMod(i+1, m_h)][j];
                for (Tile& option : cell_front->m_options) {
                    valid_options.insert(valid_options.end(), option.m_back.begin(), option.m_back.end());
                }

                temp_options = cumulative_value_options;
                for (int i = 0; i < cumulative_value_options.size(); i++) {
                    std::vector<int>::iterator it = find(valid_options.begin(), valid_options.end(), cumulative_value_options[i].m_id);
                    if (it != valid_options.end()) {
                        temp_options.push_back(cumulative_value_options[i]);
                    }
                }
                cumulative_value_options = temp_options;


                // Check the left:
                valid_options.clear();
                Cell* cell_left = m_grid[i][pythonMod(j-1, m_w)];
                for (Tile& option : cell_left->m_options) {
                    valid_options.insert(valid_options.end(), option.m_right.begin(), option.m_right.end());
                }

                temp_options = cumulative_value_options;
                for (int i = 0; i < cumulative_value_options.size(); i++) {
                    std::vector<int>::iterator it = find(valid_options.begin(), valid_options.end(), cumulative_value_options[i].m_id);
                    if (it != valid_options.end()) {
                        temp_options.push_back(cumulative_value_options[i]);
                    }
                }
                cumulative_value_options = temp_options;


                // Updating the next grid.
                nextGrid[i][j]->m_options = cumulative_value_options;
                if (nextGrid[i][j]->m_options.size() == 0) {
                    std::cout << "no valid moves" << std::endl;
                }
                nextGrid[i][j]->update();
            }
        }
    }
    // Copying next_grid into current grid
    for (int i = 0; i < nextGrid.size(); i++) {
        std::vector<Cell*> curRow;
        for (int j = 0 ; j < nextGrid[i].size(); j++) {
            curRow.push_back(nextGrid[i][j]);
        }
        m_grid[i] = curRow;
    }
}
