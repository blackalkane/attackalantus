#include <global.hpp>
#include <components/explosion.hpp>
#include "bomb.hpp"

std::vector<Texture*> Bomb::BOMB_TEXTURES = {};

bool Bomb::newWorld = true;

bool Bomb::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");
//    drawComp.PNGPath = "../data/textures/environment/props_items/bomb_anim_f0.png";
    float scaleX = 3.5, scaleY = 3.5;
    drawComp.physics.scale = {scaleX, scaleY};
//    char* path = (char*)"../data/textures/environment/props_items/bomb_anim_f";
    int frame = 0, spriteTime = 3, startIndex = 0, numberOfSprite = 10;
    frame = spriteTime * numberOfSprite;
//    drawComp.preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    preloadTexture();
    drawComp.setNewAnimation(BOMB_TEXTURES, frame, spriteTime);
    drawComp.init();
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    Explosion* explosion = new Explosion;
    explosion->setBomb(this);
    abilityComp = explosion;
    abilityComp->setPos(positionComp.getPosition());
    abilityComp->start();
    return true;
}

void Bomb::destroy() {
    drawComp.destroy();
    positionComp.destroy();
    free(abilityComp);
    abilityComp = nullptr;
}

PositionComponent *Bomb::getPositionComponent() {
    return &positionComp;
}

DrawComponent *Bomb::getDrawComponent() {
    return &drawComp;
}

AbilityComponent *Bomb::getAbilityComponent() {
    return abilityComp;
}

void Bomb::killSelf() {
//    world.killEntity(this);
    syss->removeEntityFromSystems(this);
    destroy();
}

void Bomb::preloadTexture() {
    int frame, spriteTime, startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/environment/props_items/bomb_anim_f";
        startIndex = 0, numOfSprite = 10;
        BOMB_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }

    newWorld = false;
}




