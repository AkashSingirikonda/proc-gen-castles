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

    int tileNum = 10;
    // Testing out Wave Function Collapse:
    std::vector<Tile> options;
    std::unordered_map<int, std::vector<int>> tileMap;

    for (int i = 0; i < tileNum; i++) {
        options.push_back(Tile());
    }

    std::vector<std::string> to_print;
//    to_print.push_back("WEWWEEWEW");
//    to_print.push_back("WWWEEEWEW");
//    to_print.push_back("WEWEEEWWW");
//    to_print.push_back("WEWEEWWEW");
//    to_print.push_back("WWWWWWWWW");
    to_print.push_back("WWWWWWWWW");
    to_print.push_back("EEEEEEEEE");
    to_print.push_back("EWWEWWEWW");
    to_print.push_back("EEEWWWWWW");
    to_print.push_back("WWEWWEWWE");
    to_print.push_back("WWWWWWEEE");
    to_print.push_back("EWWEWWEEE");
    to_print.push_back("EEEEWWEWW");
    to_print.push_back("EEEWWEWWE");
    to_print.push_back("WWEWWEEEE");
//    to_print.push_back("WEEEEEEEE");
//    to_print.push_back("EEWEEEEEE");
//    to_print.push_back("EEEEEEEEW");
//    to_print.push_back("EEEEEEWEE");
    // Scheme: Back, Right, Front, Left
    // 1s refer to walls, 0s refer to air/edges
    for (int i = 0; i < to_print.size(); i++) {
        options[i].m_edges = string_to_edges(to_print[i]);
        options[i].m_id = i;
        tileMap[i] = options[i].m_edges;
    }

    for (int i = 0; i < options.size(); i++) {
        options[i].setRules(&tileMap);
    }

    // Ws are 0s, Es are 1s, binary representation. left to right largest digit, up to down largest digit to smallest digit.

//    // Air
//    options[0].m_edges = {7, 7, 7, 7};
//    // Wall
//    options[1].m_edges = {0, 0, 0, 0};

//    // External Corner Pieces:
//    options[2].m_edges = {4, 1, 7, 7}; // LF
//    options[3].m_edges = {7, 4, 4, 7}; // BL
//    options[4].m_edges = {7, 7, 1, 4}; // BR
//    options[5].m_edges = {1, 7, 7, 1}; // RF

//    // Walls:
//    options[6].m_edges = {4, 0, 4, 7}; // L
//    options[7].m_edges = {7, 4, 0, 4}; // B
//    options[8].m_edges = {1, 7, 1, 0}; // R
//    options[9].m_edges = {0, 1, 7, 1}; // F

    // Rotations take place in clockwise direction around y axis.

    //

    int width = 15;
    int height = 15;
    Grid wave = Grid(width, height, 0, options, tileMap);

    wave.initiate(0, options);


    for (int i = 0; i < 100; i++) {
        wave.collapse();
        //wave.printGrid();
        for (int x = 0; x < height; x++) {
            for (int j = 0; j < 3; j++) {
                for (int y = 0; y < width; y++) {
                    if (!wave.m_grid[x][y]->m_collapsed) {
                        std::cout << "LLL";
                    } else {
                        std::cout << to_print[wave.m_grid[x][y]->m_options[0].m_id].substr(j*3, 3);
                    }
                }
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    std::cout << "done";
    // Done with Wave function collapse

    // Not testing right now:::
    //CastleLayoutGenerator::GenerateCastleLayout(seed);

    // TODO
    SceneNode* root = new SceneNode();
    SceneObject* cube = new SceneObject(PrimitiveType::PRIMITIVE_CUBE, TextureType::TEXTURE_STONE);
    SceneObject* plane = new SceneObject(PrimitiveType::PRIMITIVE_PLANE, TextureType::TEXTURE_ROOF);
    SceneObject* cone = new SceneObject(PrimitiveType::PRIMITIVE_CONE, TextureType::TEXTURE_ROOF);
    SceneObject* stairs = new SceneObject(PrimitiveType::STAIRS_STONE, TextureType::TEXTURE_ROOF);
    SceneObject* tower_top_roof = new SceneObject(PrimitiveType::WALL_CORNER_HALF_TOWER, TextureType::TEXTURE_ROOF);

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
    SceneObject* wall = new SceneObject(PrimitiveType::WALL_DOOR, TextureType::TEXTURE_STONE);
    SceneObject* wallCorner = new SceneObject(PrimitiveType::WALL_DOOR, TextureType::TEXTURE_STONE);
    SceneObject* towerSquareRoof = new SceneObject(PrimitiveType::WALL_DOOR, TextureType::TEXTURE_STONE);

    plane->transform = glm::rotate(plane->transform, 0.8f, glm::vec3(1.0f, 0.0f, 0.0f));
    plane->transform = glm::translate(plane->transform, glm::vec3(0.0f, 0.5f, -0.5f));





    // Adding Scene Light Data
    SceneLightData sceneLightData;
    sceneLightData.type = LightType::LIGHT_DIRECTIONAL;
    sceneLightData.color = SceneColor(1,1,1,1);
    sceneLightData.direction = glm::vec4(0, -1, 0, 0);
    SceneLight* sceneLight = new SceneLight(sceneLightData);
    sceneLight->transform = glm::translate(sceneLight->transform, glm::vec3(0.0f, 100.0f, 0.0f));
    root->lights.push_back(sceneLight);

    scene.root = root;

    // Creating an nxn graph:
    int n = 5;
    std::vector<SceneNode*> vals(n*n);

    for (int i = 0; i < n*n; i++) {
        vals[i] = new SceneNode();
        //vals[i]->objects.push_back(cube);
        //vals[i]->objects.push_back(plane);
        vals[i]->objects.push_back(tower_top_roof);

        //vals[i]->objects.push_back(cone);

        vals[i]->transform = glm::translate(vals[i]->transform, glm::vec3(2 * (rand()/(float)RAND_MAX) * (i/n), 0, 2 * (rand()/(float)RAND_MAX) * (i % n)));
        vals[i]->transform = glm::scale(vals[i]->transform, glm::vec3(0.1, 0.1, 0.1));
        scene.root->children.push_back(vals[i]);
    }

    auto va = string_to_edges("WWWWWWWWW");
    auto vb = string_to_edges("EWWEWWEWW");
    for (auto v1 : va) {
        std::cout << v1 << std::endl;
    }
    for (auto v1 : vb) {
        std::cout << v1 << std::endl;
    }
}
