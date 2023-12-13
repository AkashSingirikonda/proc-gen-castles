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



void ProceduralCastle::generateScene(Scene& scene)
{
    // Initialize Seed
    auto seed = settings.rootSeed;
    srand(seed);

    int tileNum = 5;
    // Testing out Wave Function Collapse:
    std::vector<Tile> options;
    std::unordered_map<int, std::vector<int>> tileMap;

    for (int i = 0; i < tileNum; i++) {
        options.push_back(Tile());
    }
    // Scheme: Back, Right, Front, Left
    options[0].m_edges = {0, 0, 0, 0};
    options[1].m_edges = {1, 1, 0, 1};
    options[2].m_edges = {1, 1, 1, 0};
    options[3].m_edges = {0, 1, 1, 1};
    options[4].m_edges = {1, 0, 1, 1};

    for (int i = 0; i < tileNum; i++) {
        options[i].m_id = i;
        tileMap[i] = options[i].m_edges;
    }

    for (int i = 0; i < tileNum; i++) {
        options[i].setRules(&tileMap);
    }

    int width = 10;
    int height = 10;
    Grid wave = Grid(width, height, 0, options, tileMap);

    wave.initiate(0, options);

    std::map<int, std::string> to_print;
    to_print[0].append("OOOOOOOOO");
    to_print[1].append("OXOXXXOOO");
    to_print[2].append("OXOOXXOXO");
    to_print[3].append("OOOXXXOXO");
    to_print[4].append("OXOXXOOXO");

    for (int i = 0; i < width*height; i++) {
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
}
