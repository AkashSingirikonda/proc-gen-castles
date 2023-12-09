#include "realtime.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>

#include "settings.h"
#include "debug.h"

#include "utils/shaderloader.h"
#include "utils/sceneloader.h"

#include "textures/defaultmaterials.h"

Realtime::Realtime(QWidget *parent)
    : QOpenGLWidget(parent)
{
    prevMousePos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    keyMap[Qt::Key_W]       = false;
    keyMap[Qt::Key_A]       = false;
    keyMap[Qt::Key_S]       = false;
    keyMap[Qt::Key_D]       = false;
    keyMap[Qt::Key_Control] = false;
    keyMap[Qt::Key_Space]   = false;
}

void Realtime::finish() {
    killTimer(timer);
    this->makeCurrent();

    //TODO delete all pointers

    glDeleteVertexArrays(1, &fullscreenVao);
    glDeleteBuffers(1, &fullscreenVbo);

    glDeleteTextures(1, &FBO_texture);
    glDeleteRenderbuffers(1, &FBO_renderBuffer);
    glDeleteFramebuffers(1, &FBO_id);

    glDeleteProgram(shader);
    glDeleteProgram(textureShader);

    this->doneCurrent();
}

void Realtime::initializeGL() {
    pixelRatio = this->devicePixelRatio();



    FBO_idDefault = 2;
    updateSizes();
    FBO_width = size().width() * pixelRatio;
    FBO_height = size().height() * pixelRatio;

    timer = startTimer(1000/60);
    elapsedTimer.start();

    // Initializing GL.
    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0,0,0,1);


    shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
    textureShader = ShaderLoader::createShaderProgram(":/resources/shaders/texture.vert", ":/resources/shaders/texture.frag");

    glUseProgram(textureShader);
    glUniform1i(glGetUniformLocation(textureShader, "tex"), 0);
    glUseProgram(0);


    ProceduralCastle castleGenerator = ProceduralCastle();
    castleGenerator.generateScene(scene);

    generateScenePrimitives();

    SceneLoader::GetRenderObjectsForScene(scene, primitiveTypes, renderObjects);


    camera = Camera(scene.cameraData, 1.0f * size().width() / size().height(), settings.nearPlane, settings.farPlane);

    initVBOandVAOs();
    makeTextureVBOandVAO();
    makeFBO();
}

//template <T, Obj>
void insertPrimitive(std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes, ScenePrimitive* primitive)
{
    auto pair = std::pair<PrimitiveType, ScenePrimitive*>(primitive->getPrimitiveType(), primitive);
    primitiveTypes.insert(pair);
}

void Realtime::generateScenePrimitives()
{
    insertPrimitive(primitiveTypes, new PrimitiveCube());
}

void Realtime::generateSceneMaterials()
{
    std::vector<TextureType> textureTypes;
    textureTypes.push_back(TextureType::TEXTURE_GRASS);

    for(TextureType textureType : textureTypes)
    {
        auto pair = std::pair<TextureType, SceneMaterial>(textureType, DefaultMaterials::getDefaultMaterial(textureType));
        materialTypes.insert(pair);
    }
}

void Realtime::initVBOandVAOs() {
    int k1 = settings.shapeParameter1;
    int k2 = settings.shapeParameter1;

    std::map<PrimitiveType, ScenePrimitive*>::iterator it;
    for(it = primitiveTypes.begin(); it != primitiveTypes.end(); it++){
        ScenePrimitive* primitive = it->second;
        primitive->generate(k1, k2);

        glGenVertexArrays(1, &primitive->VAO_name);
        glBindVertexArray(primitive->VAO_name);

        glGenBuffers(1, &primitive->VBO_name);
        glBindBuffer(GL_ARRAY_BUFFER, primitive->VBO_name);


        glBufferData(GL_ARRAY_BUFFER, primitive->VBO.size() * sizeof(GLfloat), primitive->VBO.data(), GL_DYNAMIC_DRAW);


        //TODO add UVs to VAO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
}

void Realtime::updateVBOs(){
    int k1 = settings.shapeParameter1;
    int k2 = settings.shapeParameter2;

    std::map<PrimitiveType, ScenePrimitive*>::iterator it;
    for(it = primitiveTypes.begin(); it != primitiveTypes.end(); it++){
        ScenePrimitive* primitive = it->second;
        primitive->generate(k1, k2);
        glNamedBufferData(primitive->VBO_name, primitive->VBO.size() * sizeof(GLfloat), primitive->VBO.data(), GL_DYNAMIC_DRAW);
    }
}

void Realtime::makeFBO(){
    glGenTextures(1, &FBO_texture);
    glBindTexture(GL_TEXTURE_2D, FBO_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FBO_width, FBO_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &FBO_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, FBO_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FBO_width, FBO_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &FBO_id);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_id);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, FBO_renderBuffer);

    Debug::glErrorCheck();
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_idDefault);
    Debug::glErrorCheck();
}

void Realtime::makeTextureVBOandVAO(){
    std::vector<GLfloat> fullscreen_quad_data =
        { //     POSITIONS    //
         -1.0f,  1.0f, 0.0f, 0, 1,
         -1.0f, -1.0f, 0.0f, 0, 0,
         1.0f, -1.0f, 0.0f, 1, 0,
         1.0f,  1.0f, 0.0f, 1, 1,
         -1.0f,  1.0f, 0.0f, 0, 1,
         1.0f, -1.0f, 0.0f, 1, 0,
         };

    glGenBuffers(1, &fullscreenVbo);
    glBindBuffer(GL_ARRAY_BUFFER, fullscreenVbo);
    glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size()*sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &fullscreenVao);
    glBindVertexArray(fullscreenVao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Realtime::updateLights(){
    lightTypes.clear();
    lightPositions.clear();
    lightDirections.clear();
    lightDatas.clear();
    lightColors.clear();
    lightFuncs.clear();

    for(int i = 0; i < MAX_LIGHTS; i++){
        int type = -1;
        glm::vec4 pos = glm::vec4(0.0f);
        glm::vec4 dir = glm::vec4(0.0f);
        glm::vec2 data = glm::vec2(0.0f);
        glm::vec4 color = glm::vec4(0.0f);
        glm::vec3 func = glm::vec3(0.0f);

        //TODO add lights to scene and into relevant structures
//        if(i < renderData.lights.size()){
//            auto light = renderData.lights[i];
//            type = LIGHT_TYPE_TO_INT_MAP.find(light.type)->second;
//            pos = light.pos;
//            dir = light.dir;
//            data = glm::vec2(light.penumbra, light.angle);
//            color = light.color;
//            func = light.function;
//        }

        lightTypes.push_back(type);
        lightPositions.push_back(pos);
        lightDirections.push_back(dir);
        lightDatas.push_back(data);
        lightColors.push_back(color);
        lightFuncs.push_back(func);
    }
}

void Realtime::paintGL() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_id);
    glViewport(0, 0, FBO_width, FBO_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderScene();

    glBindFramebuffer(GL_FRAMEBUFFER, FBO_idDefault);
    glViewport(0, 0, screenWidth, screenHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintTexture(FBO_texture);

    glFinish();
}


void Realtime::renderScene(){
    glUseProgram(shader);
    Debug::glErrorCheck();

    glUniform1f(glGetUniformLocation(shader, "k_a"), scene.globalData.ka);
    glUniform1f(glGetUniformLocation(shader, "k_d"), scene.globalData.kd);
    glUniform1f(glGetUniformLocation(shader, "k_s"), scene.globalData.ks);

    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, &camera.getViewMatrix()[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, false, &camera.getProjMatrix()[0][0]);

    glUniform4fv(glGetUniformLocation(shader, "camera_position"), 1, &camera.getCameraPos()[0]);

//    glUniform1iv(glGetUniformLocation(shader, "light_type"), MAX_LIGHTS, &lightTypes[0]);
//    glUniform4fv(glGetUniformLocation(shader, "light_position"), MAX_LIGHTS, &lightPositions[0][0]);
//    glUniform4fv(glGetUniformLocation(shader, "light_direction"), MAX_LIGHTS, &lightDirections[0][0]);
//    glUniform2fv(glGetUniformLocation(shader, "light_data"), MAX_LIGHTS, &lightDatas[0][0]);
//    glUniform4fv(glGetUniformLocation(shader, "light_color"), MAX_LIGHTS, &lightColors[0][0]);
//    glUniform3fv(glGetUniformLocation(shader, "light_func"), MAX_LIGHTS, &lightFuncs[0][0]);
    Debug::glErrorCheck();

    for(RenderObject* renderObject : renderObjects){
        ScenePrimitive* primitive = renderObject->primitive;

        if(primitive == nullptr)
        {
            std::cout << "Encountered null primitive for render object" << std::endl;
            continue;
        }

        glBindVertexArray(primitive->VAO_name);

        // TODO
        //SceneMaterial* material = renderObject->material;
        //glUniform4fv(glGetUniformLocation(shader, "cAmbient"), 1, &material->cAmbient[0]);
        //glUniform4fv(glGetUniformLocation(shader, "cDiffuse"), 1, &material->cDiffuse[0]);
        //glUniform4fv(glGetUniformLocation(shader, "cSpecular"), 1, &material->cSpecular[0]);

        //glUniform1f(glGetUniformLocation(shader, "shine"), material->shininess);

        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, false, &renderObject->ctm[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader, "norm_inv"), 1, false, &renderObject->normInv[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, primitive->VBO.size() / 6);

        glBindVertexArray(0);
        Debug::glErrorCheck();
    }
    glUseProgram(0);
}

void Realtime::paintTexture(GLuint texture){
    glUseProgram(textureShader);

    glBindVertexArray(fullscreenVao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(glGetUniformLocation(textureShader, "width"), screenWidth);
    glUniform1i(glGetUniformLocation(textureShader, "height"), screenHeight);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Realtime::resizeGL(int w, int h) {
    updateSizes();
    camera.updateAspectRatio(1.0f * size().width() / size().height());
}

void Realtime::updateSizes(){
    screenWidth = size().width() * pixelRatio;
    screenHeight = size().height() * pixelRatio;
    glViewport(0, 0, screenWidth, screenHeight);
}

void Realtime::settingsChanged() {
    camera.updateNearFar(settings.nearPlane, settings.farPlane);
    update();

    // TODO maybe we just add more callbacks for which setting specifically changed
    // otherwise it is quite annoying to add code here to try to figure out what needs to be updated
}

void Realtime::keyPressEvent(QKeyEvent *event) {
    keyMap[Qt::Key(event->key())] = true;
}

void Realtime::keyReleaseEvent(QKeyEvent *event) {
    keyMap[Qt::Key(event->key())] = false;
}

void Realtime::mousePressEvent(QMouseEvent *event) {
    if (event->buttons().testFlag(Qt::LeftButton)) {
        mouseDown = true;
        prevMousePos = glm::vec2(event->position().x(), event->position().y());
    }
}

void Realtime::mouseReleaseEvent(QMouseEvent *event) {
    if (!event->buttons().testFlag(Qt::LeftButton)) {
        mouseDown = false;
    }
}



void Realtime::mouseMoveEvent(QMouseEvent *event) {
    if (mouseDown) {
        int posX = event->position().x();
        int posY = event->position().y();
        int deltaX = posX - prevMousePos.x;
        int deltaY = posY - prevMousePos.y;
        prevMousePos = glm::vec2(posX, posY);

        // Use deltaX and deltaY here to rotate
        if(mouseDown){
            if(deltaX != 0 || deltaY != 0){
                camera.rotateYaw(-((float)deltaX) * rotationSpeed);
                camera.rotatePitch((-(float)deltaY) * rotationSpeed);
            }
        }

        update(); // asks for a PaintGL() call to occur
    }
}

void Realtime::timerEvent(QTimerEvent *event) {
    int elapsedms   = elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
    elapsedTimer.restart();

    glm::vec3 movement = glm::vec3(0.0f,0.0f, 0.0f);
    if(keyMap[Qt::Key_W]){
        movement[0] += 1;
    }
    if(keyMap[Qt::Key_S]){
        movement[0] -= 1;
    }
    if(keyMap[Qt::Key_D]){
        movement[1] -= 1;
    }
    if(keyMap[Qt::Key_A]){
        movement[1] += 1;
    }
    if(keyMap[Qt::Key_Space]){
        movement[2] -= 1;
    }
    if(keyMap[Qt::Key_Control]){
        movement[2] += 1;
    }
    if(movement.length() > .001f){
        movement *= movementSpeed * deltaTime;
        camera.move(movement[0], movement[1], movement[2]);
    }
    update();
}

// DO NOT EDIT
void Realtime::saveViewportImage(std::string filePath) {
    // Make sure we have the right context and everything has been drawn
    makeCurrent();

    int fixedWidth = 1024;
    int fixedHeight = 768;

    // Create Frame Buffer
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create a color attachment texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fixedWidth, fixedHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // Optional: Create a depth buffer if your rendering uses depth testing
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fixedWidth, fixedHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    // Render to the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, fixedWidth, fixedHeight);

    // Clear and render your scene here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintGL();

    // Read pixels from framebuffer
    std::vector<unsigned char> pixels(fixedWidth * fixedHeight * 3);
    glReadPixels(0, 0, fixedWidth, fixedHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Unbind the framebuffer to return to default rendering to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Convert to QImage
    QImage image(pixels.data(), fixedWidth, fixedHeight, QImage::Format_RGB888);
    QImage flippedImage = image.mirrored(); // Flip the image vertically

    // Save to file using Qt
    QString qFilePath = QString::fromStdString(filePath);
    if (!flippedImage.save(qFilePath)) {
        std::cerr << "Failed to save image to " << filePath << std::endl;
    }

    // Clean up
    glDeleteTextures(1, &texture);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &fbo);
}
