#include <global.hpp>
#include "basicEnemy.hpp"

std::vector<Texture*> BasicEnemy::IDLE_TEXTURES = {};
std::vector<Texture*> BasicEnemy::DEATH_TEXTURES = {};
std::vector<Texture*> BasicEnemy::MOVE_TEXTURES = {};
bool BasicEnemy::newWorld = true;

bool BasicEnemy::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");

    vec2 basic_enemy_scale = {1.6, 1.6};
    drawComp.physics.scale = {basic_enemy_scale.x, basic_enemy_scale.y};
    int frame, spriteTime = 4, startIndex = 0, numOfSprite = 6;
    frame = spriteTime * numOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;

    healthComp.init();

    positionComp.setWidth((texture->width) * basic_enemy_scale.x * 0.6);
    positionComp.setHeight((texture->height) * basic_enemy_scale.y * 0.6);
    positionComp.setPositionOffset(0, 0);
    type = EntityType::ENEMY;
    enemyType = EnemyType::BASIC;

    OnFire* fireAbility = new OnFire();
    fireAbility->setFireEntity(this);
    abilityComp = fireAbility;

    return true;
}


void BasicEnemy::destroy() {
    drawComp.destroy();
    positionComp.destroy();
    delete abilityComp;

}

PositionComponent *BasicEnemy::getPositionComponent() {
    return &positionComp;
}

DrawComponent *BasicEnemy::getDrawComponent() {
    return &drawComp;
}

VelocityComponent *BasicEnemy::getVelocityComponent() {
    return &velocityComp;
}

bool BasicEnemy::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::THEGUY: // FALL THROUGH
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
        case EntityType::PET:
            healthComp.dead();
            syss->getSoundSystem()->playMinionDamageMusic();
            return true;
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        case EntityType::ROCK:
            resetPosition(collidedWith);
            break;
        case EntityType::ENEMY_PROJECTILE:
            abilityComp->start();
            break;
        default:;
    }
    return false;
}

void BasicEnemy::killSelf() {
    syss->removeEntityFromSystems(this);
    destroy();
}

void BasicEnemy::resetPosition(Collides* collidedWith) {
//    positionComp.setPosition({positionComp.getPosX() - velocityComp.getVX(),
//                              positionComp.getPosY() -velocityComp.getVY()});

    vec2 current_pos = positionComp.getPosition();
    vec2 pre_pos = positionComp.getPrePosition();
    // check y position
    positionComp.resetPosY();
    if(!syss->getCollisionSystem()->didCollide((Collides*)this, collidedWith)) {
        positionComp.setPosition(pre_pos);
        positionComp.setPosX(current_pos.x);
        return;

    }

    positionComp.setPosY(current_pos.y);

    // check x position
    positionComp.resetPosX();
    if(!syss->getCollisionSystem()->didCollide((Collides*)this, collidedWith)) {
        positionComp.setPosition(pre_pos);
        positionComp.setPosY(current_pos.y);
        return;
    }

    positionComp.setPosX(current_pos.x);

    // check if it still are colliding after both attempt on x and y
    positionComp.setPosition(pre_pos);
    positionComp.resetPosition();
}

HealthComponent *BasicEnemy::getHealthComponent() {
    return &healthComp;
}

void BasicEnemy::loadStateSprite() {
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
//            drawComp.preInit(frame, spriteTime, path, (char *) "png", startIndex, numOfSprite);
//            drawComp.init();
            break;
        case GameState::DEATH:
            spriteTime = 4;
            frame = spriteTime * DEATH_TEXTURES.size();
              drawComp.setNewAnimation(DEATH_TEXTURES, frame, spriteTime);
//            drawComp.preInit(frame, spriteTime, path, (char *) "png", startIndex, numOfSprite);
//            drawComp.init();
            return;
    }
}

void BasicEnemy::preloadTexture() {
    int frame, spriteTime, startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char *) "../data/textures/characters/enemies/pig/pig_idle_0";
        spriteTime = 4, startIndex = 0, numOfSprite = 4;
        frame = spriteTime * numOfSprite;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    if(newWorld) {
        path = (char *) "../data/textures/characters/enemies/pig/pig_move_0";
        spriteTime = 4, startIndex = 0, numOfSprite = 8;
        frame = spriteTime * numOfSprite;
        MOVE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    if(newWorld) {
        spriteTime = 4, startIndex = 0, numOfSprite = 5;
        path = (char *) "../data/textures/characters/enemies/pig/pig_damage_0";
        frame = spriteTime * numOfSprite;
        DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;

}

AbilityComponent *BasicEnemy::getAbilityComponent() {
    return abilityComp;
}

