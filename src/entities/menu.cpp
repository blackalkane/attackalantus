#include "menu.hpp"

bool Menu::init()
{
    drawComponent.fragmentShaderPath = shader_path("world.fs.glsl");
    drawComponent.vertexShaderPath = shader_path("world.vs.glsl");
//    drawComponent.PNGPath = "../data/textures/menu.png";
    preloadTexture();
    drawComponent.setStaticTexture(texture);
    drawComponent.init();

    return true;
}

// Releases all graphics resources
void Menu::destroy() {
    drawComponent.destroy();
}

DrawComponent *Menu::getDrawComponent() {
    return &drawComponent;
}

PositionComponent *Menu::getPositionComponent() {
    return &positionComponent;
}

bool Menu::handleCollision(Collides *collidedWith) {
    // TODO
    return false;
}

void Menu::preloadTexture() {
    std::string path = "../data/textures/menu.png";
    texture = setTexture(path);
}

