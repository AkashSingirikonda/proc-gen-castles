#include "grid.h"
#include "tile.h"
#include "cell.h"
#include <random>
Grid::Grid(int width, int height, int rez, std::vector<int> options)
{
    m_width = width;
    m_height = height;
    m_rez = rez;
    m_options = options;
}

void Grid::initiate(int rez, std::vector<Tile> options) {
    for (int i = 0; i < m_w; ++i) {
        std::vector<Cell> curRow;
        m_grid.push_back(curRow);
        for (int j = 0; j < m_h; ++j) {
            Cell curCell = Cell(i, j, m_rez, options);
            m_grid[i].push_back(curCell);
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
            gridCopy.push_back(&row[i]);
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
    filteredGrid.erase(std::remove_if(filteredGrid.begin(), filteredGrid.end(),
                                      [leastEntropyCell](Cell* x) { return x->entropy() == leastEntropyCell->entropy();}),
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

void Grid::collapse() {
    // Pick a random cell using entropy heuristic
    Cell* pick = heuristicPick();
    if (pick) {
        pick->m_options;
        m_grid[pick->m_x][pick->m_y].observe();
    } else {
        return;
    }

    // Shallow copy of the grid
    std::vector<Cell*> nextGrid;
    for (auto& row : m_grid) {
        for (int i = 0 ; i < row.size(); i++) {
            nextGrid.push_back(&row[i]);
        }
    }

//    for (int i = 0; i < m_grid.size(); i++) {
//        for (int j = 0; j < m_grid[0].size(); j++) {
//            if (m_grid[i][j].m_collapsed) {
//                nextGrid[i][j] = m_grid[i][j];
//            } else {
//                auto cum_valid_options = m_options;
//                //Check above cell
//                Cell& cell_back = m_grid[(i - 1) % m_w][j];
//                std::vector<Tile&> valid_options;
//                for (Tile& option : cell_back.m_options) {
//                    valid_options.insert(valid_options.end(), option.m_front.begin(), option.m_front.end());
//                }
//                // If option is in valid options then
//                cum_valid_options.erase(std::remove_if(cum_valid_options.begin(), cum_valid_options.end(),
//                                                              [&valid_options](const Tile& option) {
//                                                                  return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end();
//                                                              }), cum_valid_options.end());

//                // Check right cell
//                Cell& cell_right = grid[i][(j + 1) % grid[0].size()];
//                valid_options.clear();
//                for (const auto& option : cell_right.options) {
//                    valid_options.insert(valid_options.end(), option.left.begin(), option.left.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Check down cell
//                Cell& cell_down = grid[(i + 1) % grid.size()][j];
//                valid_options.clear();
//                for (const auto& option : cell_down.options) {
//                    valid_options.insert(valid_options.end(), option.up.begin(), option.up.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Check left cell
//                Cell& cell_left = grid[i][(j - 1 + grid[0].size()) % grid[0].size()];
//                valid_options.clear();
//                for (const auto& option : cell_left.options) {
//                    valid_options.insert(valid_options.end(), option.right.begin(), option.right.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Finally, assign the cumulative_valid_options options to be the current cell's valid options
//                next_grid[i][j].options = cumulative_valid_options;
//                next_grid[i][j].update();
//            }
//        }
//    }
//    // Update the entropy values and superpositions of each cell in the grid
//    for (size_t i = 0; i < grid.size(); ++i) {
//        for (size_t j = 0; j < grid[0].size(); ++j) {
//            if (grid[i][j].collapsed) {
//                next_grid[i][j] = grid[i][j];
//            } else {
//                // Cumulative valid options will hold the options that will satisfy the "down", "right", "up", "left"
//                // conditions of each cell in the grid.

//                std::vector<Option> cumulative_valid_options = options;

//                // Check above cell
//                Cell& cell_above = grid[(i - 1 + grid.size()) % grid.size()][j];
//                std::vector<Option> valid_options;
//                for (const auto& option : cell_above.options) {
//                    valid_options.insert(valid_options.end(), option.down.begin(), option.down.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Check right cell
//                Cell& cell_right = grid[i][(j + 1) % grid[0].size()];
//                valid_options.clear();
//                for (const auto& option : cell_right.options) {
//                    valid_options.insert(valid_options.end(), option.left.begin(), option.left.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Check down cell
//                Cell& cell_down = grid[(i + 1) % grid.size()][j];
//                valid_options.clear();
//                for (const auto& option : cell_down.options) {
//                    valid_options.insert(valid_options.end(), option.up.begin(), option.up.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Check left cell
//                Cell& cell_left = grid[i][(j - 1 + grid[0].size()) % grid[0].size()];
//                valid_options.clear();
//                for (const auto& option : cell_left.options) {
//                    valid_options.insert(valid_options.end(), option.right.begin(), option.right.end());
//                }
//                cumulative_valid_options.erase(std::remove_if(cumulative_valid_options.begin(), cumulative_valid_options.end(),
//                                                              [&](const Option& option) { return std::find(valid_options.begin(), valid_options.end(), option) == valid_options.end(); }),
//                                               cumulative_valid_options.end());

//                // Finally, assign the cumulative_valid_options options to be the current cell's valid options
//                next_grid[i][j].options = cumulative_valid_options;
//                next_grid[i][j].update();
//            }
//        }
//    }

//    // Re-assign the grid value after cell evaluation
//    grid = next_grid;
}
