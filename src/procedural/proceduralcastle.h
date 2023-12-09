#pragma once

#include "scene/scene.h"

/*
 *
 * Mainly creating a temp file here.
 *
 * We want one place to call into the procedural generation to say "getScene"
 * but otherwise we probably want the code to be decently spread out / modularized
 *
 */


class ProceduralCastle
{
public:
    ProceduralCastle();

    void generateScene(Scene& scene);
};
