#include <global.hpp>
#include "defaultTexture.hpp"

bool DefaultTexture::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.8, scaleY = 1.8;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.init();
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    type = EntityType::OTHERS;
    return true;
}

void DefaultTexture::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *DefaultTexture::getPositionComponent() {
    return &positionComp;
}


DrawComponent *DefaultTexture::getDrawComponent() {
    return &drawComp;
}

void DefaultTexture::preloadTexture() {
}

void DefaultTexture::setLevelTexture(const std::string& path) {
    texture = setTexture(path);
    drawComp.setStaticTexture(texture);
}
