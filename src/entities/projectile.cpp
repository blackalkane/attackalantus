#include <global.hpp>
#include <components/shoot.hpp>
#include "projectile.hpp"


std::vector<Texture*> Projectile::IDLE_TEXTURES = {};
bool Projectile::newWorld = true;

bool Projectile::init() {
    drawComp.fragmentShaderPath = shader_path("projectile.fs.glsl");
    drawComp.vertexShaderPath = shader_path("projectile.vs.glsl");
    drawComp.physics.scale = {0.64, 0.64};

    int frame , spriteTime = 5;

    preloadTexture();
    frame = spriteTime * IDLE_TEXTURES.size();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    velocityComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * 0.036);
    positionComp.setHeight((texture->height) * 0.036);
    // TODO what is this doing? memory leak?
    Shoot* shoot = new Shoot;
    abilityComp = shoot;
    abilityComp->setPos(positionComp.getPosition());
    abilityComp->start();
    type = EntityType::PROJECTILE;
    return true;
}


void Projectile::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

DrawComponent *Projectile::getDrawComponent() {
    return &drawComp;
}

PositionComponent *Projectile::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *Projectile::getVelocityComponent() {
    return &velocityComp;
}

AbilityComponent *Projectile::getAbilityComponent() {
    return abilityComp;
}

bool Projectile::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        // SHOULD DISAPPEAR
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        case EntityType::ENEMY_PROJECTILE:
        case EntityType::ROCK:
            return true;
            // SHOULD PASS THROUGH
        case EntityType::THEGUY: break;
        case EntityType::PROJECTILE: break;
        default:;
    }
    return false;
}

void Projectile::killSelf() {
    syss->removeEntityFromSystems(this);
//    world.killEntity(this);
    destroy();
}

void Projectile::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char *) "../data/textures/effects/GameFX/PngSpritesheet_x64/IceShatter_2_96x96/IceShatter_2_96x96-";
        startIndex = 1, numOfSprite = 31;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;

}