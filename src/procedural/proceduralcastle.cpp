#include "proceduralcastle.h"
#include "glm/gtx/transform.hpp"
#include "graph.h"
#include "unordered_map"
#include "set"
#include "scene/sceneobject.h"
#include <random>
#include <settings.h>

#include "layoutgenerator.h"

ProceduralCastle::ProceduralCastle()
{

}



void ProceduralCastle::generateScene(Scene& scene)
{
    // Initialize Seed
    auto seed = settings.rootSeed;
    srand(seed);

    //CastleLayoutGenerator::GenerateCastleLayout(seed);

    // TODO
    SceneNode* root = new SceneNode();
    SceneObject* cube = new SceneObject(PrimitiveType::PRIMITIVE_CUBE, TextureType::TEXTURE_STONE);
    SceneObject* plane = new SceneObject(PrimitiveType::PRIMITIVE_PLANE, TextureType::TEXTURE_ROOF);
    SceneObject* cone = new SceneObject(PrimitiveType::PRIMITIVE_CONE, TextureType::TEXTURE_ROOF);
    SceneObject* tower = new SceneObject(PrimitiveType::PRIMITIVE_MESH, TextureType::TEXTURE_ROOF);



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
        vals[i]->objects.push_back(tower);

        //vals[i]->objects.push_back(cone);
//        vals[i]->transform = glm::scale(vals[i]->transform, glm::vec3(0.01, 0.01, 0.01));

        vals[i]->transform = glm::translate(vals[i]->transform, glm::vec3(2 * (rand()/(float)RAND_MAX) * (i/n), 0, 2 * (rand()/(float)RAND_MAX) * (i % n)));
        vals[i]->transform = glm::scale(vals[i]->transform, glm::vec3(0.1, 0.1, 0.1));
        scene.root->children.push_back(vals[i]);
    }

//    Graph<SceneNode> g = Graph<SceneNode>();
//    for (int i = 0; i < n*n; i++) {
//        g.addNode(i, vals[i]);
//    }

//    for (int i = 0; i < n*n; i++) {
//        // Horizontal Edges
//        if (i % n > 0 ) {
//            g.addEdge(i, i-1);
//        }

//        if (i % n != n-1) {
//            g.addEdge(i, i+1);
//        }

//        // Vertical Edges
//        if (i / n != 0) {
//            g.addEdge(i, i - n);
//        }

//        if (i / n != n-1) {
//            g.addEdge(i, i + n);
//        }
//    }

    //g.printGraph();
}
