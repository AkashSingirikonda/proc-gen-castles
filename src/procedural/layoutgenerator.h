#pragma once

#include <iostream>
#include <math.h>

#include "glm/gtx/transform.hpp"
#include "algorithms/lsystem.h"
#include "algorithms/lsystemstructuretypes.h"





struct Region
{
    // This defines a region dedicated to some generation
    // the center defines the rough location of the structure
    // the radius defines the rough size of the structure
    glm::vec2 center;
    float radius;
    StructureType structureType;
};

class CastleLayoutGenerator
{
public:

    static float randFloat()
    {
        return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }

    static glm::vec2 randDirection()
    {
        float r = randFloat() * 2 * M_PI;
        return glm::vec2(cos(r), sin(r));
    }

    static void GenerateCastleLayout(int seed)
    {
        LSystem layoutGenerator = LSystem<StructureType>();

        layoutGenerator.addRule(KEEP, {KEEP, WALL});
        layoutGenerator.addRule(KEEP, {KEEP, KEEP});

        std::vector<StructureType> layout;
        layoutGenerator.generate(seed, KEEP, 3, layout);


        std::vector<Region> regions;

        glm::vec2 center = glm::vec3(0);
        float radius = 0;

        float margin = 5;

        for(StructureType structureType : layout)
        {
            Region region;

            float structureRadius;
            region.structureType = structureType;

            switch(structureType)
            {
            case KEEP:
                structureRadius = 10;
                region.center = center + randDirection() * (radius + structureRadius + margin);
                region.radius = structureRadius;
                center = (region.center * structureRadius + center * radius) / (structureRadius + radius);
                radius = radius + structureRadius + margin;
                break;
            case WALL:
                structureRadius = 20;
                region.center = center;
                region.radius = structureRadius + radius + margin;
                radius = structureRadius + radius + margin;
                break;
            default:
                break;
            }

            regions.push_back(region);
        }
    }
};
