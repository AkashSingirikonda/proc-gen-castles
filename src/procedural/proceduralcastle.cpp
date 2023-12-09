#include "proceduralcastle.h"
#include "graph.h"

ProceduralCastle::ProceduralCastle()
{

}



void ProceduralCastle::generateScene(Scene& scene)
{
    // TODO
    SceneNode* root = new SceneNode();
    SceneObject* cube = new SceneObject(PrimitiveType::PRIMITIVE_CUBE, TextureType::TEXTURE_STONE);
    root->objects.push_back(cube);
    scene.root = root;

    // Creating an nxn graph:
//    int n = 10;
//    SceneNode[n] val = ;
//    Graph g = Graph<SceneNode>();
//    for (int i = 0; i < n*n; i++) {
//        g.addNode(i, cube);
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

//    g.printGraph();
}
