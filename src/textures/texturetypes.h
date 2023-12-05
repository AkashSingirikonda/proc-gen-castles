# pragma once

/*
 * Generic texture enum to make it easier to specify texutres for scene objects.
 *
 * During generation we can indicate which parts of the scene need which texture via the enum.
 * During rendering we use the enum to look up the actual texture.
 *
 * To start we should render different textures as just colors. Then as textures become available we can
 * use them to replace the base colors.
 */

enum TextureType {
    TEXTURE_STONE = 0,
    TEXTURE_ROOF = 1,
    TEXTURE_GRASS = 2,
};
