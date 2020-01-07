#include "bombExplosion.hpp"

std::vector<Texture*> BombExplosion::EXPLOSION_TEXTURES = {};
bool BombExplosion::newWorld = true;

bool BombExplosion::init()
{
    drawComp.fragmentShaderPath = shader_path("projectile.fs.glsl");
    drawComp.vertexShaderPath = shader_path("projectile.vs.glsl");
//    drawComp.PNGPath = "../data/textures/effects/dungon_effects/explosion_anim_f0.png";
    float scaleX = 2.5, scaleY = 2.5;
    drawComp.physics.scale = {scaleX, scaleY};
//    char* path = (char*)"../data/textures/effects/dungon_effects/explosion_anim_f";
    int frame = 0, spriteTime = 10, startIndex = 0, numberOfSprite = 7;
    frame = spriteTime * numberOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(EXPLOSION_TEXTURES, frame, spriteTime);
//    drawComp.preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    drawComp.init();
//    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);
    type = EntityType::PROJECTILE;
    return true;
}

void BombExplosion::destroy()
{
    drawComp.destroy();
    positionComp.destroy();
}

DrawComponent *BombExplosion::getDrawComponent() {
    return &drawComp;
}

PositionComponent *BombExplosion::getPositionComponent() {
    return &positionComp;
}

bool BombExplosion::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        // SHOULD DISAPPEAR
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        case EntityType::ROCK:
//            return true;
            // SHOULD PASS THROUGH
        case EntityType::THEGUY: break;
        case EntityType::PROJECTILE: break;
        default:;
    }
    return false;
}

void BombExplosion::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/effects/dungon_effects/explosion_anim_f";
        startIndex = 0, numOfSprite = 7;
        EXPLOSION_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    newWorld = false;
}



