#include "boomerangIcon.hpp"

bool BoomerangIcon::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 0.8f, scaleY = 0.8f;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    return true;
}

void BoomerangIcon::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *BoomerangIcon::getPositionComponent() {
    return &positionComp;
}


DrawComponent *BoomerangIcon::getDrawComponent() {
    return &drawComp;
}

void BoomerangIcon::preloadTexture() {
    std::string path = "../data/textures/others/boomerang/bullet006.0002.png";
    texture = setTexture(path);
}