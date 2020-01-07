//
// Created by Andy He on 2019-12-06.
//

#include "firePet.hpp"

std::vector<Texture*> FirePet::IDLE_TEXTURES = {};
std::vector<Texture*> FirePet::DEATH_TEXTURES = {};
std::vector<Texture*> FirePet::MOVE_TEXTURES = {};
bool FirePet::newWorld = true;

bool FirePet::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");

    vec2 pet_scale = {1.5, 1.5};
    drawComp.physics.scale = {pet_scale.x, pet_scale.y};
    int frame, spriteTime = 4;
    preloadTexture();
    frame = spriteTime * IDLE_TEXTURES.size();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();
    Texture *texture = drawComp.texture;

    healthComp.init();

    positionComp.init();
    positionComp.setWidth((texture->width) * pet_scale.x * 0.6);
    positionComp.setHeight((texture->height) * pet_scale.y * 0.6);
    positionComp.setPositionOffset(0, 0);
    type = EntityType::PET;
    
    velocityComp.init();

    return true;
}

void FirePet::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char *) "../data/textures/characters/enemies/fireman/idle";
        startIndex = 1, numOfSprite = 6;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        path = (char *) "../data/textures/characters/enemies/fireman/move";
        startIndex = 1, numOfSprite = 8;
        MOVE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        startIndex = 1, numOfSprite = 8;
        path = (char *) "../data/textures/characters/enemies/fireman/death";
        DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;

}

void FirePet::loadStateSprite() {
    int currentState = entityState.getState();
    if (currentState == entityState.getPreFrameState() || currentState == GameState::ABILITY) {
        // do nothing
        return;
    }
    int frame, spriteTime;
    switch(currentState) {
        case GameState::MOVE:
            spriteTime = 4;
            frame = spriteTime * MOVE_TEXTURES.size();
            drawComp.setNewAnimation(MOVE_TEXTURES, frame, spriteTime);
            break;
        case GameState::IDLE:
            spriteTime = 4;
            frame = spriteTime * IDLE_TEXTURES.size();
            drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
            break;
        case GameState::DEATH:
            spriteTime = 4;
            frame = spriteTime * DEATH_TEXTURES.size();
            drawComp.setNewAnimation(DEATH_TEXTURES, frame, spriteTime);
            return;
    }
}

void FirePet::destroy() {
    drawComp.destroy();
    positionComp.destroy();
    velocityComp.destroy();
    healthComp.destroy();

}

DrawComponent *FirePet::getDrawComponent() {
    return &drawComp;
}

PositionComponent *FirePet::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *FirePet::getVelocityComponent() {
    return &velocityComp;
}

HealthComponent *FirePet::getHealthComponent() {
    return &healthComp;
}

bool FirePet::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::THEGUY: // FALL THROUGH
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
        case EntityType::ENVIRONMENT:
        case EntityType::ROCK:
            break;
        case EntityType::ENEMY:
        case EntityType::ENEMY_PROJECTILE:
            healthComp.dead();
            return true;
        default:;
    }
    return false;
}
