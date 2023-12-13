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

    for (int i = 0; i < m_w; i++) {
        m_grid[0][i] = new Cell(i, 0, m_rez, {options[0]}, &m_tileMap);
        m_grid[0][i]->m_collapsed = true;
        m_grid[m_w-1][i] = new Cell(i, m_w-1, m_rez, {options[0]}, &m_tileMap);
        m_grid[m_w-1][i]->m_collapsed = true;
    }

    for (int i = 0; i < m_h; i++) {
        m_grid[i][0] = new Cell(0, i, m_rez, {options[0]}, &m_tileMap);
        m_grid[i][0]->m_collapsed = true;
        m_grid[i][m_h-1] = new Cell(m_h-1, i, m_rez, {options[0]}, &m_tileMap);
        m_grid[i][m_h-1]->m_collapsed = true;
    }
    // In this special case, we'll make the outside boxes all the same edges
    m_options = options;
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



    // Filter cells with entropy greater than 1
    std::vector<Cell*> filteredGrid;
    for (auto c : gridCopy) {
        if (c->entropy() > 1) {
            filteredGrid.push_back(c);
        }
    }

    if (filteredGrid.empty()) {
        return nullptr;
    }

    // Find the least entropy cell
    Cell* leastEntropyCell = filteredGrid[0];
    for (auto c : filteredGrid) {
        if (c->entropy() <= leastEntropyCell->entropy()) {
            leastEntropyCell = c;
        }
    }


    std::vector<Cell*> new_filteredGrid;
    for (auto c : filteredGrid) {
        if (c->entropy() <= leastEntropyCell->entropy()) {
            new_filteredGrid.push_back(c);
        }
    }

    filteredGrid = new_filteredGrid;

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
    // Store all the states in the state matrix:
//    std::vector<std::vector<Cell>> to_store;
//    for (auto& row : m_grid) {
//        std::vector<Cell> curRow;
//        for (int i = 0 ; i < row.size(); i++) {
//            curRow.push_back(*row[i]);
//        }
//        to_store.push_back(curRow);
//    }

//    m_history.push_back(to_store);

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
                std::vector<int> cumulative_value_options;
                for (int k = 0; k < m_options.size(); k++) {
                    cumulative_value_options.push_back(k);
                }

                // Back
                Cell* cell_back = m_grid[pythonMod(i-1, m_h)][j];
                std::set<int> valid_options;
                for (int k = 0; k < cell_back->m_options.size(); k++) {
                    for (int l = 0; l < cell_back->m_options[k].m_front.size(); l++) {
                        valid_options.insert(cell_back->m_options[k].m_front[l]);
                    }
                }
                cumulative_value_options.erase(std::remove_if(cumulative_value_options.begin(), cumulative_value_options.end(),
                                                              [&valid_options](int value) {
                                                                  return valid_options.find(value) == valid_options.end();
                                                              }),
                                               cumulative_value_options.end());

                // Right
                Cell* cell_right = m_grid[i][pythonMod(j+1, m_w)];
                valid_options.clear();
                for (int k = 0; k < cell_right->m_options.size(); k++) {
                    for (int l = 0; l < cell_right->m_options[k].m_left.size(); l++) {
                        valid_options.insert(cell_right->m_options[k].m_left[l]);
                    }
                }
                cumulative_value_options.erase(std::remove_if(cumulative_value_options.begin(), cumulative_value_options.end(),
                                                              [&valid_options](int value) {
                                                                  return valid_options.find(value) == valid_options.end();
                                                              }),
                                               cumulative_value_options.end());



                // Front
                Cell* cell_front = m_grid[pythonMod(i+1, m_h)][j];
                valid_options.clear();
                for (int k = 0; k < cell_front->m_options.size(); k++) {
                    for (int l = 0; l < cell_front->m_options[k].m_back.size(); l++) {
                        valid_options.insert(cell_front->m_options[k].m_back[l]);
                    }
                }
                cumulative_value_options.erase(std::remove_if(cumulative_value_options.begin(), cumulative_value_options.end(),
                                                              [&valid_options](int value) {
                                                                  return valid_options.find(value) == valid_options.end();
                                                              }),
                                               cumulative_value_options.end());
                valid_options.clear();

                // Left
                Cell* cell_left = m_grid[i][pythonMod(j-1, m_w)];
                valid_options.clear();
                for (int k = 0; k < cell_left->m_options.size(); k++) {
                    for (int l = 0; l < cell_left->m_options[k].m_right.size(); l++) {
                        valid_options.insert(cell_left->m_options[k].m_right[l]);
                    }
                }
                cumulative_value_options.erase(std::remove_if(cumulative_value_options.begin(), cumulative_value_options.end(),
                                                              [&valid_options](int value) {
                                                                  return valid_options.find(value) == valid_options.end();
                                                              }),
                                               cumulative_value_options.end());
                valid_options.clear();

                // Updating the next grid.
                std::vector<int> new_options_int(cumulative_value_options.begin(), cumulative_value_options.end());
                nextGrid[i][j]->m_options.clear();
                for (auto neighbor : new_options_int) {
                    nextGrid[i][j]->m_options.push_back(m_options[neighbor]);
                }
                if (nextGrid[i][j]->m_options.size() == 0) {
                    std::cout << "no valid moves" << std::endl;
                }
                nextGrid[i][j]->update();
                std::cout << nextGrid[i][j]->entropy() << " ";
            }
            std::cout << std::endl;
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

