#include "proceduralcastle.h"
#include "glm/gtx/transform.hpp"
#include "graph.h"
#include "unordered_map"
#include "set"
#include "scene/sceneobject.h"
#include "tile.h"
#include "grid.h"
#include <random>
#include <settings.h>
#include <unordered_map>

#include "layoutgenerator.h"

ProceduralCastle::ProceduralCastle()
{

}

bool check_vc(char to_check) {
    if (to_check == 'E') {
        return true;
    } else if (to_check == 'W') {
        return false;
    }
    std::cout << "invalid string" << std::endl;
    return false;
}

std::vector<int> string_to_edges(std::string to_move) {
    std::vector<int> to_ret(4);
    for (int i = 0; i < 3; i++) {
        to_ret[0] += check_vc(to_move[i]) * (1 << i);
        to_ret[1] += check_vc(to_move[3*i + 2]) * (1 << i);
        to_ret[2] += check_vc(to_move[6+i]) * (1 << i);
        to_ret[3] += check_vc(to_move[3*i]) * (1 << i);

    }
    return to_ret;
}

void ProceduralCastle::generateScene(Scene& scene)
{
    // Initialize Seed
    auto seed = settings.rootSeed;
    srand(seed);

    std::vector<std::string> tileStrings;
    // Empty Space (Used for collapsing outer box.)
    tileStrings.push_back("EEEEEEEEE");
    // Internal Walls
    tileStrings.push_back("WWWWWWWWW");
    // Single Sides, half walls
    tileStrings.push_back("EEEWWWWWW");
    tileStrings.push_back("EWWEWWEWW");
    tileStrings.push_back("WWWWWWEEE");
    tileStrings.push_back("WWEWWEWWE");

    // External Corners
    tileStrings.push_back("EEEWWEWWE");
    tileStrings.push_back("EEEEWWEWW");

    tileStrings.push_back("EWWEWWEEE");
    tileStrings.push_back("WWEWWEEEE");





//    // Bridge Wall Connector:
//    tileStrings.push_back("EWEWWWWWW");
//    tileStrings.push_back("WWEWWWWWE");
//    tileStrings.push_back("WWWWWWEWE");
//    tileStrings.push_back("EWWWWWEWW");
//    // Bridge Piece
//    tileStrings.push_back("EWEEWEEWE");
//    tileStrings.push_back("EEEWWWEEE");
//    // Twisting bridge pieces
//    tileStrings.push_back("EWEEWWEEE");
//    tileStrings.push_back("EEEEWWEWE");
//    tileStrings.push_back("EEEWWEEWE");
//    tileStrings.push_back("EWEWWEEEE");
//    // Bridge End Pieces:
//    tileStrings.push_back("EWEEWEEEE");
//    tileStrings.push_back("EEEEWWEEE");
//    tileStrings.push_back("EEEEWEEWE");
//    tileStrings.push_back("EEEWWEEEE");

    int tileNum = tileStrings.size();
    // Creating tiles from strings.
    std::vector<Tile> options;
    std::unordered_map<int, std::vector<int>> tileMap;

    for (int i = 0; i < tileNum; i++) {
        options.push_back(Tile());
    }
    // Scheme: Back, Right, Front, Left
    // 1s refer to walls, 0s refer to air/edges
    for (int i = 0; i < tileStrings.size(); i++) {
        options[i].m_edges = string_to_edges(tileStrings[i]);
        options[i].m_id = i;
        tileMap[i] = options[i].m_edges;
    }

    for (int i = 0; i < options.size(); i++) {
        options[i].setRules(&tileMap);
    }

    // Spetting up grid for Wave Function Collapse

    int width = 20;
    int height = 20;
    bool finished_collapse;
    int num_restarts = 5;
    Grid wave = Grid(width, height, 0, options, tileMap);
    for (int i = 0; i < num_restarts; i++) {
        wave = Grid(width, height, 0, options, tileMap);
        wave.initiate(0, options);
        bool acc = true;
        bool to_break_for = true;
        bool to_break_acc = true;
        while (true) {
            acc = true;
            to_break_for = false;
            wave.collapse();
            // Checks if for no collapse.
            for (auto& row : wave.m_grid) {
                for (auto& tile : row) {
                    acc &= tile->m_collapsed;
                    if (tile->m_options.size() == 0) {
                        to_break_for = true;
                        break;
                    }
                }
                if (to_break_for) {
                    break;
                }
            }

            if (to_break_for) {
                break;
            }
            // Checks for collapse.
            if (acc) {
                to_break_acc = false;
                break;
            }
        }
        if (!to_break_acc) {
            std::cout << "exited on restart" << i << std::endl;
            break;
        }
    }

    // Printing once generation is complete.
    for (int x = 0; x < height; x++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < width; y++) {
                if (!wave.m_grid[x][y]->m_collapsed) {
                    std::cout << "LLL";
                } else {
                    std::cout << tileStrings[wave.m_grid[x][y]->m_options[0].m_id].substr(j*3, 3);
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "done";
    // Done with Wave function collapse

    // Not testing right now:::
    //CastleLayoutGenerator::GenerateCastleLayout(seed);

    // TODO
    // Adding Scene Light Data
    SceneLightData sceneLightData;
    sceneLightData.type = LightType::LIGHT_DIRECTIONAL;
    sceneLightData.color = SceneColor(1,1,1,1);
    sceneLightData.direction = glm::vec4(0, -1, 0, 0);
    SceneLight* sceneLight = new SceneLight(sceneLightData);
    sceneLight->transform = glm::translate(sceneLight->transform, glm::vec3(0.0f, 100.0f, 0.0f));
    SceneNode* root = new SceneNode();
    root->lights.push_back(sceneLight);

// List of current assets:
//        STAIRS_STONE,
//        TOWER_BASE,
//        TOWER_SQUARE_BASE,
//        TOWER_SQUARE,
//        TOWER_SQUARE_ARCH,
//        TOWER_SQUARE_MID,
//        TOWER_SQUARE_ROOF,
//        TOWER_SQUARE_TOP,
//        WALL,
//        WALL_CORNER,
//        WALL_DOOR


//    to_print.push_back("WWWWWWWWW");
//    to_print.push_back("EEEEEEEEE");
//    to_print.push_back("EWWEWWEWW");
//    to_print.push_back("EEEWWWWWW");
//    to_print.push_back("WWEWWEWWE");
//    to_print.push_back("WWWWWWEEE");
//    to_print.push_back("EWWEWWEEE");
//    to_print.push_back("EEEEWWEWW");
//    to_print.push_back("EEEWWEWWE");
//    to_print.push_back("WWEWWEEEE");
//    to_print.push_back("WEEEEEEEE");
//    to_print.push_back("EEWEEEEEE");
//    to_print.push_back("EEEEEEEEW");
//    to_print.push_back("EEEEEEWEE");

    // Adding in assets:
    SceneObject* wall = new SceneObject(PrimitiveType::WALL_HALF, TextureType::TEXTURE_STONE);
    SceneObject* wallCorner = new SceneObject(PrimitiveType::WALL_CORNER_HALF, TextureType::TEXTURE_STONE);
    SceneObject* towerSquareBase = new SceneObject(PrimitiveType::TOWER_SQUARE_BASE, TextureType::TEXTURE_STONE);
    SceneObject* towerSquare = new SceneObject(PrimitiveType::TOWER_SQUARE, TextureType::TEXTURE_STONE);
    SceneObject* towerSquareTopRoof = new SceneObject(PrimitiveType::TOWER_SQUARE_TOP_ROOF, TextureType::TEXTURE_ROOF);
    // Mapping Sceneprimitives to their rotations and indices:

    std::map<int, std::pair<SceneObject*, int>> to_rotate;

    to_rotate[1].first = towerSquareBase;
    to_rotate[1].second = 0;
    for (int i = 0; i < 4; i++) {
        to_rotate[i+2].first = wall;
        to_rotate[i+2].second = i;
        to_rotate[i+6].first = wallCorner;
        to_rotate[i+6].second = i;
    }

    std::map<int, glm::vec3> offset_map;
    offset_map[1] = glm::vec3{0, 0, 0};
    offset_map[2] = glm::vec3{-1, 0, 1};
    offset_map[3] = glm::vec3{-1, 0, 0};
    offset_map[4] = glm::vec3{0, 0, 0};
    offset_map[5] = glm::vec3{0, 0, 1};
    offset_map[6] = glm::vec3{-1, 0, 1};
    offset_map[7] = glm::vec3{-1, 0, 0};
    offset_map[8] = glm::vec3{0, 0, 0};
    offset_map[9] = glm::vec3{0, 0, 1};



    scene.root = root;
    // Creating an nxn graph:
    std::vector<SceneNode*> vals;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (wave.m_grid[i][j]->m_collapsed) {
                std::pair<SceneObject*, int> asset = to_rotate[wave.m_grid[i][j]->m_options[0].m_id];
                if (wave.m_grid[i][j]->m_options[0].m_id != 0) {
                    //SceneNode* to_insert3 = new SceneNode();
//                    //std::cout << wave.m_grid[i][j]->m_options[0].m_id << std::endl;
//                    to_insert3->objects.push_back(wallCorner);
//                    to_insert3->transform = glm::scale(to_insert3->transform, glm::vec3(0.1, 0.1, 0.1));
//                    to_insert3->transform = glm::translate(to_insert3->transform, glm::vec3(10*(i+1), 20, 10*(j-1)));
//                    to_insert3->transform = glm::rotate(to_insert3->transform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//                    scene.root->children.push_back(to_insert3);
//                    vals.push_back(to_insert3);

                    SceneNode* to_insert2 = new SceneNode();
                    //std::cout << wave.m_grid[i][j]->m_options[0].m_id << std::endl;
                    to_insert2->objects.push_back(asset.first);
                    //to_insert->transform = to_insert->transform * asset.second;
                    to_insert2->transform = glm::scale(to_insert2->transform, glm::vec3(0.1, 0.1, 0.1));
                    to_insert2->transform = glm::translate(to_insert2->transform,
                                                           glm::vec3(10, 0, 10) * (glm::vec3(i, 0, j) + offset_map[wave.m_grid[i][j]->m_options[0].m_id]));
                    to_insert2->transform = glm::rotate(to_insert2->transform, glm::radians(-90.0f * asset.second), glm::vec3(0.0f, 1.0f, 0.0f));
                    scene.root->children.push_back(to_insert2);
                    vals.push_back(to_insert2);

                    if (wave.m_grid[i][j]->m_options[0].m_id == 1) {
                        SceneNode* to_insert = new SceneNode();
                        to_insert->objects.push_back(towerSquare);
                        to_insert->transform = glm::scale(to_insert->transform, glm::vec3(0.1, 0.1, 0.1));
                        to_insert->transform = glm::translate(to_insert->transform,
                                                               glm::vec3(10, 10, 10) * (glm::vec3(i, 1, j) + offset_map[wave.m_grid[i][j]->m_options[0].m_id]));
                        to_insert->transform = glm::rotate(to_insert->transform, glm::radians(-90.0f * asset.second), glm::vec3(0.0f, 1.0f, 0.0f));
                        scene.root->children.push_back(to_insert);
                        vals.push_back(to_insert);

                        SceneNode* to_insert3 = new SceneNode();
                        //std::cout << wave.m_grid[i][j]->m_options[0].m_id << std::endl;
                        to_insert3->objects.push_back(towerSquareTopRoof);
                        //to_insert->transform = to_insert->transform * asset.second;
                        to_insert3->transform = glm::scale(to_insert3->transform, glm::vec3(0.1, 0.1, 0.1));
                        to_insert3->transform = glm::translate(to_insert3->transform,
                                                              glm::vec3(10, 23, 10) * (glm::vec3(i, 1, j) + offset_map[wave.m_grid[i][j]->m_options[0].m_id]));
                        to_insert3->transform = glm::rotate(to_insert3->transform, glm::radians(-90.0f * asset.second), glm::vec3(0.0f, 1.0f, 0.0f));
                        scene.root->children.push_back(to_insert3);
                        vals.push_back(to_insert3);
                    }
//                    SceneNode* to_insert = new SceneNode();
//                    //std::cout << wave.m_grid[i][j]->m_options[0].m_id << std::endl;
//                    to_insert->objects.push_back(towerSquareBase);
//                    to_insert->transform = glm::scale(to_insert->transform, glm::vec3(0.1, 0.1, 0.1));
//                    //to_insert->transform = glm::rotate(to_insert->transform, glm::radians(i * -90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//                    to_insert->transform = glm::translate(to_insert->transform, glm::vec3(10*i, 10, 10*j));
//                    scene.root->children.push_back(to_insert);
//                    vals.push_back(to_insert);
                }
            }
        }
    }
}
