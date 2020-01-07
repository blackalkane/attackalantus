//
// Created by Tim Guo on 2019-10-20.
//

#include <global.hpp>
#include "enemyProjectile.hpp"

std::vector<Texture*> EnemyProjectile::PROJECTILE_TEXTURES = {};
bool EnemyProjectile::newWorld = true;

bool EnemyProjectile::init() {
    drawComp.fragmentShaderPath = shader_path("projectile.fs.glsl");
    drawComp.vertexShaderPath = shader_path("projectile.vs.glsl");
    drawComp.physics.scale = {0.64, 0.64};
//    drawComp.PNGPath = "../data/textures/effects/GameFX/PngSpritesheet_x64/FireBall_64x64/FireBall_64x64-1.png";
//    char* path = (char*)"../data/textures/effects/GameFX/PngSpritesheet_x64/FireBall_64x64/FireBall_64x64-";
    int frame = 0, spriteTime = 2, startIndex = 1, numberOfSprite = 41;
    frame = spriteTime * numberOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(PROJECTILE_TEXTURES, frame, spriteTime);
//    drawComp.preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    drawComp.init();
    velocityComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * 0.25);
    positionComp.setHeight((texture->height) * 0.25);
    type = EntityType::ENEMY_PROJECTILE;
    return true;
}

void EnemyProjectile::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

DrawComponent *EnemyProjectile::getDrawComponent() {
    return &drawComp;
}

PositionComponent *EnemyProjectile::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *EnemyProjectile::getVelocityComponent() {
    return &velocityComp;
}

bool EnemyProjectile::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        // SHOULD DISAPPEAR
        case EntityType::ENVIRONMENT:
        case EntityType::ROCK:
        case EntityType::THEGUY:
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
        case EntityType::PET:
            return true;
            // SHOULD PASS THROUGH
        case EntityType::ENEMY:
            break;
        default:;
    }
    return false;
}

void EnemyProjectile::killSelf() {
//    world.killEntity(this);
    syss->removeEntityFromSystems(this);
    destroy();
}

void EnemyProjectile::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/effects/GameFX/PngSpritesheet_x64/FireBall_64x64/FireBall_64x64-";
        startIndex = 1, numOfSprite = 41;
        PROJECTILE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    newWorld = false;
}
