#include <global.hpp>
#include "healthBar.hpp"

bool HealthBar::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
//    drawComp.PNGPath = "../data/textures/others/Hearts/PNG/basic/heart.png";
    float scaleX = 1, scaleY = 1;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    return true;
}

void HealthBar::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *HealthBar::getPositionComponent() {
    return &positionComp;
}


DrawComponent *HealthBar::getDrawComponent() {
    return &drawComp;
}

void HealthBar::preloadTexture() {
    std::string path = "../data/textures/others/Hearts/PNG/basic/heart.png";
    texture = setTexture(path);
}
