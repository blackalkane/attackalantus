#include "waterCurrent.hpp"
std::vector<Texture*> WaterCurrent::currentTexture = {};
bool WaterCurrent::newWorld = true;
bool WaterCurrent::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 5.0, scaleY = 2.5;
    int frame = 0, spriteTime = 4, startIndex = 0, numberOfSprite = 3;
    frame = spriteTime * numberOfSprite;
    preloadTexture();
    drawComp.physics.scale = {scaleX, scaleY};
    drawComp.setStaticTexture(nullptr);
    drawComp.setNewAnimation(currentTexture, frame, spriteTime);
    drawComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.init();
    positionComp.setWidth((texture->width) * scaleX * 0.8);
    positionComp.setHeight((texture->height) * scaleY * 0.6);
    positionComp.setPositionOffset(0, - (texture->height) * scaleY);
    type = EntityType::WATERCURRENT;
    return true;
}

void WaterCurrent::destroy()
{
    drawComp.destroy();
}

DrawComponent *WaterCurrent::getDrawComponent() {
    return &drawComp;
}

PositionComponent *WaterCurrent::getPositionComponent() {
    return &positionComp;
}

bool WaterCurrent::handleCollision(Collides *collidedWith) {
    // should never die
    return false;
}

void WaterCurrent::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/environment/props_items/current";
        startIndex = 0, numOfSprite = 3;
        currentTexture = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;
}
