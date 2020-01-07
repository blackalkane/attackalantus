#include <global.hpp>
#include "menu_items.hpp"

bool MenuItems::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 0.8, scaleY = 0.5;
    drawComp.physics.scale = {scaleX, scaleY};
    preloadTexture();
    drawComp.setStaticTexture(texture);
    drawComp.init();
    Texture *texture = drawComp.texture;
    // positionComp.setPosition({600.f, 300.f});
    positionComp.init();
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    type = EntityType::OTHERS;
    return true;
}

void MenuItems::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *MenuItems::getPositionComponent() {
    return &positionComp;
}


DrawComponent *MenuItems::getDrawComponent() {
    return &drawComp;
}

void MenuItems::preloadTexture() {
}

void MenuItems::setMenuTexture(std::string &path) {
    texture = setTexture(path);
    drawComp.setStaticTexture(texture);
}
