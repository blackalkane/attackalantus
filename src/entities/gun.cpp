#include <global.hpp>
#include "gun.hpp"

bool Gun::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 0.2, scaleY = 0.2;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    return true;
}

void Gun::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *Gun::getPositionComponent() {
    return &positionComp;
}


DrawComponent *Gun::getDrawComponent() {
    return &drawComp;
}

void Gun::preloadTexture() {
    std::string path = "../data/textures/others/gun.png";
    texture = setTexture(path);
}
