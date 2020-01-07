#include <global.hpp>
#include "levelSelectionBackground.hpp"

bool LevelSelectionBackground::init() {
    drawComp.fragmentShaderPath = shader_path("world.fs.glsl");
    drawComp.vertexShaderPath = shader_path("world.vs.glsl");
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();

    return true;
}

void LevelSelectionBackground::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *LevelSelectionBackground::getPositionComponent() {
    return &positionComp;
}


DrawComponent *LevelSelectionBackground::getDrawComponent() {
    return &drawComp;
}

void LevelSelectionBackground::preloadTexture() {
    std::string path = "../data/textures/levelSelection.png";
    texture = setTexture(path);
}

