#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "textures/texturetypes.h"

/*
 * The most simple component of a scene like a single triangle or some basic shape (cube, cone, etc.)
 *
 * A scene primitive can only have one texture but multiple scene primitives can be combined into a single scene object.
 */
class ScenePrimitive
{
public:
    ScenePrimitive();
    ~ScenePrimitive();

    void getVBOData(){}; // TODO

private:
    TextureType texture;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> norms;
    std::vector<glm::vec2> uvs;
};
