#include "drawComponent.hpp"
#include "common.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream> // stdout, stderr..

// glfw
#define NOMINMAX
#include <gl3w.h>
#include <GLFW/glfw3.h>

DrawComponent::DrawComponent() {
    texture = nullptr;
}

DrawComponent::~DrawComponent(){

}

bool DrawComponent::init(){
//    // free texture first
//    for(Texture* tex: textures){
//        free(tex);
//    }
//    textures.clear();

    if(textures.empty() && texture == nullptr) {
        printf("error, the textures vector is empty");
    }

    // make sure that sprite time is initiate
    if (!spriteTime){
        spriteTime = 2;
    }

    radian = 0;

//    if (!texture.is_valid())
//    {
//        if (!texture.load_from_file(PNGPath))
//        {
//            fprintf(stderr, "Failed to load texture!");
//            return false;
//        }else{
//
//        }
//    }else{
//        printf("gg");
//    }

//    for(char* path : PNGPaths){
//        Texture* curTexture = new Texture();
////        if (!curTexture->is_valid())
////        {
//        if (!curTexture->load_from_file(path))
//        {
//            fprintf(stderr, "Failed to texture: %s\n", path);
//            return false;
//        }else{
//        }
////        }else{
////            printf("gg2");
////        }
//        textures.push_back(curTexture);
//    }
    if(texture == nullptr) {
        texture = textures.at(0);
    }

    // The positionComp corresponds to the center of the texture
    float wr = (float)texture->width * 0.5f;
    float hr = (float)texture->height * 0.5f;

    TexturedVertex vertices[4];
    vertices[0].position = { -wr, +hr, vdepth };
    vertices[0].texcoord = { 0.f, 1.f };
    vertices[1].position = { +wr, +hr, vdepth };
    vertices[1].texcoord = { 1.f, 1.f };
    vertices[2].position = { +wr, -hr, vdepth };
    vertices[2].texcoord = { 1.f, 0.f };
    vertices[3].position = { -wr, -hr, vdepth };
    vertices[3].texcoord = { 0.f, 0.f };

    // Counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;

    // Loading shaders
    if (!effect.load_from_file(vertexShaderPath, fragmentShaderPath))
        return false;


    // Setting initial values, scale is negative to make it face the opposite way
    // 1.0 would be as big as the original texture.
//    physics.scale = { -0.4f, 0.4f };

    return true;
    }

void DrawComponent::destroy(){
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ibo);
    glDeleteBuffers(1, &mesh.vao);

    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
    glDeleteShader(effect.program);

//    for(char* path: PNGPaths){
//        free(path);
//    }
    free(texture);

    textures.clear();
}

namespace
{
    bool gl_compile_shader(GLuint shader)
    {
        glCompileShader(shader);
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLint log_len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetShaderInfoLog(shader, log_len, &log_len, log.data());
            glDeleteShader(shader);

            fprintf(stderr, "GLSL: %s", log.data());
            return false;
        }

        return true;
    }
}

bool DrawComponent::Effect::load_from_file(const char* vs_path, const char* fs_path)
{
    gl_flush_errors();

    // Opening files
    std::ifstream vs_is(vs_path);
    std::ifstream fs_is(fs_path);

    if (!vs_is.good() || !fs_is.good())
    {
        fprintf(stderr, "Failed to load shader files %s, %s", vs_path, fs_path);
        return false;
    }

    // Reading sources
    std::stringstream vs_ss, fs_ss;
    vs_ss << vs_is.rdbuf();
    fs_ss << fs_is.rdbuf();
    std::string vs_str = vs_ss.str();
    std::string fs_str = fs_ss.str();
    const char* vs_src = vs_str.c_str();
    const char* fs_src = fs_str.c_str();
    GLsizei vs_len = (GLsizei)vs_str.size();
    GLsizei fs_len = (GLsizei)fs_str.size();

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vs_src, &vs_len);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs_src, &fs_len);

    // Compiling
    // Shaders already delete if compilation fails
    if (!gl_compile_shader(vertex))
        return false;

    if (!gl_compile_shader(fragment))
    {
        glDeleteShader(vertex);
        return false;
    }

    // Linking
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    {
        GLint is_linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
        if (is_linked == GL_FALSE)
        {
            GLint log_len;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetProgramInfoLog(program, log_len, &log_len, log.data());

            release();
            fprintf(stderr, "Link error: %s", log.data());
            return false;
        }
    }

    if (gl_has_errors())
    {
        release();
        fprintf(stderr, "OpenGL errors occured while compiling Effect");
        return false;
    }

    return true;
}

void DrawComponent::Effect::release()
{
    glDeleteProgram(program);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void DrawComponent::updateFrame() {
    if (textures.size() <= 0){
        return;
    }
    texture = textures.at(currentFrame / spriteTime);
    currentFrame = (currentFrame + 1) % totalFrame;
}

void DrawComponent::setScale(vec2 sc) {
    physics.scale = sc;
}

vec2 DrawComponent::getScale() {
    return physics.scale;
}

void DrawComponent::preInit(int frameInTotal, int spriteT, char *generalPath, char* picType, int indexBegin, int size) {
    currentFrame = 0;
    totalFrame = frameInTotal;
    spriteTime = spriteT;
//    loadAllTexturePaths(generalPath, picType, indexBegin, size);
}

//void DrawComponent::loadAllTexturePaths(char* generalPath, char* picType, int indexBegin, int size) {
//    //clear PNGPaths first
//    for(char* path: PNGPaths){
//        free(path);
//    }
//    PNGPaths.clear();
//
//    for(int i = indexBegin; i < size + indexBegin; i++){
//        char* spritePath = new char[256];
//        sprintf(spritePath, "%s%d.%s", generalPath, i, picType);
//        PNGPaths.push_back(spritePath);
//    }
//}

void DrawComponent::setSpriteTime(int spt) {
    spriteTime = spt;
}

int DrawComponent::getCurrentFrame() {
    return currentFrame;
}

int DrawComponent::getTotalFrame() {
    return totalFrame;
}

bool DrawComponent::cycleFinish() {
    return (currentFrame + 1) == totalFrame;
}

void DrawComponent::setTextures(std::vector<Texture *> ts) {
    textures = ts;
}

void DrawComponent::setNewAnimation(std::vector<Texture *> ts, int frameInTotal, int spriteT) {
    setTextures(ts);
    currentFrame = 0;
    totalFrame = frameInTotal;
    spriteTime = spriteT;
}

void DrawComponent::setStaticTexture(Texture* t) {
    texture = t;
}

void DrawComponent::setRadian(float r) {
    radian = r;
}

float DrawComponent::getRadian() {
    return radian;
}


