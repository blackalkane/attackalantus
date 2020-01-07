#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "gcomponent.hpp"
#include "common.hpp"

#include <vector>
#include <iostream>
#include <sstream>

// glfw
#define NOMINMAX
#include <gl3w.h>
#include <GLFW/glfw3.h>

class DrawComponent: public GComponent
{
public:
    DrawComponent();
    ~DrawComponent();

    bool init() override;

    void destroy();

    struct Mesh {
        GLuint vao;
        GLuint vbo;
        GLuint ibo;
    } mesh;

    struct Effect {
        GLuint vertex;
        GLuint fragment;
        GLuint program;

        bool load_from_file(const char* vs_path, const char* fs_path); // load shaders from files and link into program
        void release(); // release shaders and program
    } effect;

    struct Physics {
        vec2 scale;
    } physics;

    Texture* texture;
    const char *vertexShaderPath;
    const char *fragmentShaderPath;
//    const char * PNGPath;
//    std::vector<char*> PNGPaths;
    std::vector<Texture*> textures;
    int totalFrame;
    int currentFrame;
    int spriteTime;
    float radian;
    float vdepth = -0.02;

    void updateFrame();

    void setScale(vec2 sc);

    vec2 getScale();

    void preInit(int frameInTotal, int spriteT, char* generalPath, char* picType, int indexBegin, int size);

//    void loadAllTexturePaths(char* generalPath, char* picType, int indexBegin, int size);

    void setSpriteTime(int spt);

    int getCurrentFrame();

    int getTotalFrame();

    bool cycleFinish();

    void setTextures(std::vector<Texture*> ts);

    void setStaticTexture(Texture* t);

    void setNewAnimation(std::vector<Texture*> ts, int frameInTotal, int spriteT);

    void setRadian(float r);

    float getRadian();

};

#endif