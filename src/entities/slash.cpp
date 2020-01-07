#include <global.hpp>
#include "slash.hpp"

bool Slash::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
//    drawComp.PNGPath = "../data/textures/others/slash.png";
    preloadTexture();
    float scaleX = 0.13, scaleY = 0.13;
    drawComp.physics.scale = {scaleX, scaleY};
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *dtexture = drawComp.texture;
    positionComp.setWidth((dtexture->width) * scaleX);
    positionComp.setHeight((dtexture->height) * scaleY);
    return true;
}

void Slash::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *Slash::getPositionComponent() {
    return &positionComp;
}


DrawComponent *Slash::getDrawComponent() {
    return &drawComp;
}

void Slash::preloadTexture() {
    std::string path = "../data/textures/others/slash.png";
    texture = setTexture(path);
}
