//
// Created by Peter Han on 2019-12-06.
//

#include "meteoroidIcon.hpp"
bool MeteoroidIcon::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 0.07f, scaleY = 0.07f;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    return true;
}

void MeteoroidIcon::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *MeteoroidIcon::getPositionComponent() {
    return &positionComp;
}


DrawComponent *MeteoroidIcon::getDrawComponent() {
    return &drawComp;
}

void MeteoroidIcon::preloadTexture() {
    std::string path = "../data/textures/meteor.png";
    texture = setTexture(path);
}