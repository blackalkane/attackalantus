//
// Created by Tim Guo on 2019-11-08.
//

#include <global.hpp>
#include "bossProjectile.hpp"

std::vector<Texture*> BossProjectile::PROJECTILE_TEXTURES = {};
bool BossProjectile::newWorld = true;

bool BossProjectile::init() {
    drawComp.fragmentShaderPath = shader_path("projectile.fs.glsl");
    drawComp.vertexShaderPath = shader_path("projectile.vs.glsl");
    drawComp.physics.scale = {0.64, 0.64};
    int frame = 0, spriteTime = 2, startIndex = 1, numberOfSprite = 30;
    frame = spriteTime * numberOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(PROJECTILE_TEXTURES, frame, spriteTime);
    drawComp.init();
    velocityComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * 0.25);
    positionComp.setHeight((texture->height) * 0.25);
    type = EntityType::ENEMY_PROJECTILE;
    rad = 10.0f;

    return true;
}

void BossProjectile::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

DrawComponent *BossProjectile::getDrawComponent() {
    return &drawComp;
}

PositionComponent *BossProjectile::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *BossProjectile::getVelocityComponent() {
    return &velocityComp;
}

bool BossProjectile::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        // SHOULD DISAPPEAR
        case EntityType::ENVIRONMENT:
        case EntityType::THEGUY:
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
        case EntityType::PET:
            return true;
            // SHOULD PASS THROUGH
        case EntityType::ROCK:
            stuck();
        case EntityType::ENEMY:
            break;
        default:;
    }
    return false;
}

void BossProjectile::killSelf() {
    syss->removeEntityFromSystems(this);
    destroy();
}

void BossProjectile::stuck() {
    velocityComp.setVelocity({0.0f,0.0f});
    if (rad == 10.0f) {
        rad = drawComp.getRadian();
    }
    drawComp.setRadian(rad);
}

void BossProjectile::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/effects/GameFX/PngSpritesheet_x64/IcePick_64x64/IcePick_64x64-";
        startIndex = 1, numOfSprite = 30;
        PROJECTILE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    newWorld = false;
}
