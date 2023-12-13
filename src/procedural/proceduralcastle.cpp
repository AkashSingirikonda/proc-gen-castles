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
    tileStrings.push_back("EWWEWWEWW");
    tileStrings.push_back("EEEWWWWWW");
    tileStrings.push_back("WWEWWEWWE");
    tileStrings.push_back("WWWWWWEEE");
    // External Corners
    tileStrings.push_back("EWWEWWEEE");
    tileStrings.push_back("EEEEWWEWW");
    tileStrings.push_back("EEEWWEWWE");
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

    int width = 15;
    int height = 15;
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
    SceneObject* wallCorner = new SceneObject(PrimitiveType::WALL_CORNER_HALF_TOWER, TextureType::TEXTURE_STONE);
    SceneObject* towerSquareRoof = new SceneObject(PrimitiveType::TOWER_SQUARE_BASE, TextureType::TEXTURE_STONE);

    scene.root = root;

    // Creating an nxn graph:
    int n = 5;
    std::vector<SceneNode*> vals(n*n);

    for (int i = 0; i < n*n; i++) {
        vals[i] = new SceneNode();
        //vals[i]->objects.push_back(cube);
        //vals[i]->objects.push_back(plane);
        vals[i]->objects.push_back(wall);

        //vals[i]->objects.push_back(cone);

        vals[i]->transform = glm::translate(vals[i]->transform, glm::vec3(2 * (rand()/(float)RAND_MAX) * (i/n), 0, 2 * (rand()/(float)RAND_MAX) * (i % n)));
        vals[i]->transform = glm::scale(vals[i]->transform, glm::vec3(0.1, 0.1, 0.1));
        scene.root->children.push_back(vals[i]);
    }
}
