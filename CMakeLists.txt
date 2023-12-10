cmake_minimum_required(VERSION 3.16)

# Sets project name
project(proc_gen_castles LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Sets C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specifies required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Xml)

# Allows you to include files from within those directories, without prefixing their filepaths
include_directories(src)

# Specifies .cpp and .h files to be passed to the compiler
add_executable(${PROJECT_NAME}
    src/main.cpp

    src/realtime.cpp
    src/mainwindow.cpp
    src/settings.cpp

    src/mainwindow.h
    src/realtime.h
    src/settings.h

    src/utils/shaderloader.h
    src/utils/aspectratiowidget/aspectratiowidget.hpp
)

# GLM: this creates its library and allows you to `#include "glm/..."`
add_subdirectory(glm)

# GLEW: this creates its library and allows you to `#include "GL/glew.h"`
add_library(StaticGLEW STATIC glew/src/glew.c
    src/splines/spline.h src/splines/spline.cpp
    src/splines/cameratrack.h src/splines/cameratrack.cpp
    src/splines/cameratracksegment.h src/splines/cameratracksegment.cpp
    src/scene/scene.h src/scene/scene.cpp
    src/scene/sceneobject.h src/scene/sceneobject.cpp
    src/scene/sceneprimitive.h src/scene/sceneprimitive.cpp
    src/textures/texturetypes.h
    src/procedural/proceduralcastle.h src/procedural/proceduralcastle.cpp
    src/splines/cameraparams.h
    src/utils/camera.h src/utils/camera.cpp
    src/scene/primitivetypes.h
    src/utils/renderobject.h src/utils/renderobject.cpp
    src/utils/sceneloader.h
    src/scene/scenedata.h
    src/textures/texturedata.h
    src/textures/defaultmaterials.h
    src/procedural/graph.h src/procedural/graph.cpp
    src/procedural/wfc.h src/procedural/wfc.cpp )
include_directories(${PROJECT_NAME} PRIVATE glew/include)

# Specifies libraries to be linked (Qt components, glew, etc)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Gui
    Qt::OpenGL
    Qt::OpenGLWidgets
    Qt::Xml
    StaticGLEW
)

# Specifies other files
qt6_add_resources(${PROJECT_NAME} "Resources"
    PREFIX
        "/"
    FILES
        resources/shaders/default.frag
        resources/shaders/default.vert
        resources/shaders/texture.frag
        resources/shaders/texture.vert
)

# GLEW: this provides support for Windows (including 64-bit)
if (WIN32)
  add_compile_definitions(GLEW_STATIC)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    glu32
  )
endif()

# Set this flag to silence warnings on Windows
if (MSVC OR MSYS OR MINGW)
  set(CMAKE_CXX_FLAGS "-Wno-volatile")
endif()
# Set this flag to silence warnings on MacOS
if (APPLE)
  set(CMAKE_CXX_FLAGS "-Wno-deprecated-volatile")
endif()
