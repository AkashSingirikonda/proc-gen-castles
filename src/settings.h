#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct Settings {
    int shapeParameter1 = 1;
    int shapeParameter2 = 1;
    float nearPlane = 1;
    float farPlane = 1;


    int rootSeed = 0;
};


// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
