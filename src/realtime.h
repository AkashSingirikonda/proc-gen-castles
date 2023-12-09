#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

#include "scene/scene.h"
#include "utils/camera.h"
#include "utils/renderobject.h"
#include "procedural/proceduralcastle.h"

class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void finish();                                      // Called on program exit
    void settingsChanged();
    void saveViewportImage(std::string filePath);

public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 prevMousePos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    float pixelRatio;
    void updateSizes();

    ProceduralCastle castleGenerator;

    // This is the scene where we want to generate our castle.
    Scene scene;
    // collection of render objects loaded from the scene
    std::vector<RenderObject*> renderObjects;
    std::vector<RenderLight*> renderLights;

    void generateScenePrimitives();
    std::map<PrimitiveType, ScenePrimitive*> primitiveTypes;

    void generateSceneMaterials();
    std::map<TextureType, SceneMaterial> materialTypes;

    void renderScene();
    // helper function for finish()
    void clearScene(){}; //TODO



    Camera camera;
    const float movementSpeed = 5;
    const float rotationSpeed = .003;



    // TODO It might make more sense to just have all of the light data in the scene since that is where it is generated anyway
    const int MAX_LIGHTS = 10;
    std::vector<int> lightTypes;
    std::vector<glm::vec4> lightColors;
    std::vector<glm::vec4> lightPositions;
    std::vector<glm::vec4> lightDirections;
    std::vector<glm::vec2> lightDatas;
    std::vector<glm::vec3> lightFuncs;

    const std::map<LightType, int> LIGHT_TYPE_TO_INT_MAP = {{LightType::LIGHT_POINT, 1}, {LightType::LIGHT_DIRECTIONAL, 2}, {LightType::LIGHT_SPOT, 3}};

    void updateLights();


    // For each scene primitive generate the necessary VAO, VBO, and VBO data
    void initVBOandVAOs();
    void updateVBOs();
    void clearVBOandVAOs(){}; //TODO








    GLuint shader;

    // FBO for screen level filters

    GLuint FBO_idDefault;
    int FBO_width;
    int FBO_height;
    int screenWidth;
    int screenHeight;

    GLuint textureShader;
    GLuint fullscreenVbo;
    GLuint fullscreenVao;
    QImage image;
    GLuint FBO_id;
    GLuint FBO_texture;
    GLuint FBO_renderBuffer;

    void makeFBO();
    void makeTextureVBOandVAO();
    void paintTexture(GLuint texture);

};
