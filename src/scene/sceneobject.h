#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


#include "sceneprimitive.h"

/*
 * Parent class for all object in scenes.
 *
 * We want to use this later to generate VBO data for rendering.
 *
 * For now a scene object is composed of primitives
 *
 */
class SceneObject
{
public:
    SceneObject();
    ~SceneObject();

    void getVBOData(){}; //TODO


private:
    std::vector<ScenePrimitive*> primitives;
};
