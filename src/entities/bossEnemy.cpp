//
// Created by Tim Guo on 2019-11-04.
//

#include <global.hpp>
#include "bossEnemy.hpp"

std::vector<Texture*> BossEnemy::IDLE_TEXTURES = {};
std::vector<Texture*> BossEnemy::DEATH_TEXTURES = {};
std::vector<Texture*> BossEnemy::MOVE_TEXTURES = {};
std::vector<Texture*> BossEnemy::ABILITY_TEXTURES = {};
bool BossEnemy::newWorld = true;

bool BossEnemy::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");

    drawComp.physics.scale = {2, 2};
    preloadTexture();
    int frame, spriteTime = 4, numOfSprite = 12;
    frame = spriteTime * numOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;

    positionComp.setWidth((texture->width) * 1);
    positionComp.setHeight((texture->height) * 1);

    healthComp.init();
    healthComp.setHealth(8);
    healthComp.alive();

    collideAgain = 0;

    type = EntityType::ENEMY;
    enemyType = EnemyType::BOSS;
    return true;
}

void BossEnemy::destroy() {
    positionComp.destroy();
    velocityComp.destroy();
    drawComp.destroy();
    healthComp.destroy();
}

PositionComponent *BossEnemy::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *BossEnemy::getVelocityComponent() {
    return &velocityComp;
}

DrawComponent *BossEnemy::getDrawComponent() {
    return &drawComp;
}

HealthComponent *BossEnemy::getHealthComponent() {
    return &healthComp;
}

bool BossEnemy::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::THEGUY:
        case EntityType::PET:
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
            if (collideAgain > 0) return false;
//            resetPosition(collidedWith);
            positionComp.resetPosition();
            healthComp.decrementHealth();
            syss->getSoundSystem()->playBossDamageMusic();
//            printf("health now: %d\n", healthComp.getHealth());
            if (healthComp.getHealth() < 1) {
                healthComp.dead();
            }
            collideAgain = 30;
            return !healthComp.isAlive();
        case EntityType::ROCK:
            resetPosition(collidedWith);
            break;
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        default:;
    }
    return false;
}

void BossEnemy::killSelf() {
    syss->removeEntityFromSystems(this);
    destroy();
}

void BossEnemy::resetPosition(Collides* collidedWith) {
//    positionComp.setPosition({positionComp.getPosX() - velocityComp.getVX(),
//                              positionComp.getPosY() -velocityComp.getVY()});
    // check x position
    vec2 current_pos = positionComp.getPosition();
    positionComp.resetPosX();
    if(!syss->getCollisionSystem()->didCollide((Collides*)this, collidedWith)) {
        return;
    }

    positionComp.setPosX(current_pos.x);
    // check y position
    positionComp.resetPosY();
    if(!syss->getCollisionSystem()->didCollide((Collides*)this, collidedWith)) {
        return;

    }
    positionComp.setPosY(current_pos.y);

    // check if it still are colliding after both attempt on x and y
    positionComp.resetPosition();
}

void BossEnemy::loadStateSprite() {
    int currentState = entityState.getState();
    if (currentState == entityState.getPreFrameState()) {
        // do nothing
        return;
    }
    int frame, spriteTime, startIndex, numOfSprite;
    char* path;
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
        case GameState::ABILITY:
            spriteTime = 4;
            frame = spriteTime * ABILITY_TEXTURES.size();
            drawComp.setNewAnimation(ABILITY_TEXTURES, frame, spriteTime);
            return;
        case GameState::DEATH:
            spriteTime = 4;
            frame = spriteTime * DEATH_TEXTURES.size();
            drawComp.setNewAnimation(DEATH_TEXTURES, frame, spriteTime);
            return;
        default:
            break;
    }
}

void BossEnemy::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        emptyTextureVector(IDLE_TEXTURES);
        path = (char *) "../data/textures/characters/yasuo/Idle/Character_01_Idle";
        startIndex = 1, numOfSprite = 12;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(DEATH_TEXTURES);
        startIndex = 1, numOfSprite = 16;
        path = (char *) "../data/textures/characters/yasuo/Death/Character_01_Death_";
        DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(MOVE_TEXTURES);
        startIndex = 1, numOfSprite = 15;
        path = (char *) "../data/textures/characters/yasuo/Run/Character_01_Run_0";
        MOVE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(ABILITY_TEXTURES);
        startIndex = 1, numOfSprite = 12;
        path = (char *) "../data/textures/characters/yasuo/Attack_02/Character_01_Attack_02_";
        ABILITY_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    BossEnemy::newWorld = false;
}

void BossEnemy::collideAgainDecrement() {
    collideAgain--;
}