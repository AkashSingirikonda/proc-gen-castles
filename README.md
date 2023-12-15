Procedurally Generated Castles



General Code Layout

The starting point for the repository is project 6 template with portions of project 6 copied in primarily in realtime.cpp/realtime.h
Some other bits of code are shared but for the most part the architecture is new and designed specifically for parallel group work.

Realtime.cpp handles the setup of VAO's, VBO's, and general initialization for other parts of the code. This is also where input handling
and settings updates take place.

The general code flow is as follows:
1. Procedural generation is delegated to a function in the procedural generation folder: ProceduralCastle::generateScene()
  - This allows procedural generation code to be setup independently from the rest of the project. New classes, structures, 
    algorithms, etc can all be setup and organized in the procedural generation folder as needed.
2. The procedural generation builds a scene tree analogous to the scene tree defined in the json scene files of previous projects.
  - Please refer to the definitions of SceneNode, SceneObject, and SceneLight in the scene folder.
  - This allows the procedural generation to rely on relative transforms.
  - Multiple scene nodes can reference the same sub-tree reducing memory usage. For example a single scene node for a tower can be
    made allowing multiple other scene nodes to reference it with different relative transforms, placing multiple towers in the
    final scene.
  - Procedural generation doesn't need to worry about references to primitives or textures. Instead convenient enums are defined:
    TextureType and PrimitiveType. This allows for expressions like this:
    new SceneObject(PrimitiveType::PRIMITIVE_CUBE, TextureType::TEXTURE_STONE);
3. Scene Materials and Scene Primitives are generated in generateScenePrimitives() and generateSceneMaterials()
  - This allows all RenderObjects with the same primitive/material to reference a single instance again saving on memory.
4. The Scene tree is parsed into a list of RenderObjects in SceneLoader::GetRenderObjectsForScene()
  - This handles all of the linking and converts all transforms to be in world space.
  - This logic is similar to that of the scene parser from previous projects.
5. The scene is rendered in the same way as previous projects.
  - A normal map from the material is passed to the fragment shader in addition to a flag to indicate if it should be used.


Camera Work : Alexander Ivanov

A camera track class is defined which allows the specification of animation tracks for individual camera parameters. 
This is initially setup for just camera position and look vectors but because the splines are templated and the animation tracks take
a reference to the parameter that needs to be updated it is fairly easy to animate all sorts of parameters and not necessarily just
the parameters on the camera (this would take some additional refactoring though to convert the appropriate classes into templates)

Each animation track is composed of multiple track segments. Each segment can have its own duration and the animation tracks don't need to 
have the same length. Additionally, each segment can take an easing function which applies an easing function to the time at which a segment
is evaluated. This can create effects like moving quickly at the star of a segment and slowing down towards the end.
The available easing functions are:
    LINEAR
    EASE
    EASE_IN
    EASE_OUT
    EASE_IN_OUT
and more can be defined in easefunctions.h

The main track segments that are provided for animation are:
 - Constant: Returns the same parameter for the full duration of the track.
 - Linear: Linear interpolation of paramters from the start to the end of a track.
 - Bezier: Bezier interpolation of paramters based on the two control points.
 - Tangent: A spline which matches the provided tangent vectors at the end points.
 
Tracks can be composed in any order and additionally can take the previous track as an input in the constructor to automatically
set the starting point to the ending point of the previous track.


L System : Alexander Ivanov

In procedural/algorithms we have a simple L-System implementation. The L-System is templated to allow an arbitrary type that supports
comparison to be used (intended to be used with an enum although other types could work). The rules for the L-system are simple, 
allowing only the conversion of a single vocabulary word into an arbitrary successor list. Conditional rules were not implemented.

The Lsystem is used to generate a sample hierachical layout for a castle in procedural/layoutgenerator.h
This demonstraights how the LSystem can be setup with an enum and then how the output can be used to produce a data structure that can
be piped into more procedural generation.


Normal Mapping Textures : Yaara Kaplan

For the textures, we used normal maps to add more depth to the primitives. We decided to have 3 different texture types that were 
attached to different primitives: Stone for the walls, a roof texture for roofs, and grass for the ground which was implemented using 
simple cubes. 

To create the normal maps, I found images online that matched the texture we wanted to replicate and edited them into normal maps 
using Photoshop. These normal maps are then loaded into the shader based on the material of the primitive. Unlike regularly mapped 
textures, we use the pixel data from the normal map to overwrite the primitive normals, so that the surface of the primitive reacts more 
realistically to light shining. We then compute the rest of the lighting using the phong illumination model, just as we did in Action.

In order to implement these textures, we added uv coordinates as well as tangent vectors to the VBO. The uv coordinates allow us to map 
the textures onto the primitives with the correct pixels, and the tangent vectors are used in the vertex shader to compute a 
transformation matrix that converts the normals from the normal map from tangent space into object space. This transformation matrix is
what ensures accurate lighting effects using the phong illumination model.
