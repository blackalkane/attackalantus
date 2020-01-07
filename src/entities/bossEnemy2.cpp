//
// Created by Tim Guo on 2019-11-12.
//

#include <global.hpp>
#include "bossEnemy2.hpp"

std::vector<Texture*> BossEnemy2::IDLE_TEXTURES = {};
std::vector<Texture*> BossEnemy2::DEATH_TEXTURES = {};
std::vector<Texture*> BossEnemy2::MOVE_TEXTURES = {};
std::vector<Texture*> BossEnemy2::ABILITY_TEXTURES = {};
bool BossEnemy2::newWorld = true;

bool BossEnemy2::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");

    drawComp.physics.scale = {2, 2};
    preloadTexture();
    int frame, spriteTime = 4, numOfSprite = 5;
    frame = spriteTime * numOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;

    positionComp.setWidth((texture->width) * 0.5);
    positionComp.setHeight((texture->height) * 0.5);

    healthComp.init();
    healthComp.setHealth(8);
    healthComp.alive();

    collideAgain = 0;

    type = EntityType::ENEMY;
    enemyType = EnemyType::BOSS2;
    return true;
}

void BossEnemy2::destroy() {
    positionComp.destroy();
    velocityComp.destroy();
    drawComp.destroy();
    healthComp.destroy();
}

PositionComponent *BossEnemy2::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *BossEnemy2::getVelocityComponent() {
    return &velocityComp;
}

DrawComponent *BossEnemy2::getDrawComponent() {
    return &drawComp;
}

HealthComponent *BossEnemy2::getHealthComponent() {
    return &healthComp;
}

bool BossEnemy2::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::THEGUY:
        case EntityType::PET:
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
            if (collideAgain > 0) return false;
//            resetPosition(collidedWith);
            positionComp.resetPosition();
            syss->getSoundSystem()->playBossDamageMusic();
            healthComp.decrementHealth();
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

void BossEnemy2::killSelf() {
    syss->removeEntityFromSystems(this);
    destroy();
}

void BossEnemy2::resetPosition(Collides* collidedWith) {
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

void BossEnemy2::loadStateSprite() {
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

void BossEnemy2::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        emptyTextureVector(IDLE_TEXTURES);
        path = (char *) "../data/textures/characters/Boss2/Idle//Idle_0";
        startIndex = 1, numOfSprite = 5;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(DEATH_TEXTURES);
        startIndex = 1, numOfSprite = 12;
        path = (char *) "../data/textures/characters/Boss2/Death/Death_0";
        DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(MOVE_TEXTURES);
        startIndex = 1, numOfSprite = 8;
        path = (char *) "../data/textures/characters/Boss2/Run/Run_0";
        MOVE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    if(newWorld) {
        emptyTextureVector(ABILITY_TEXTURES);
        startIndex = 1, numOfSprite = 22;
        path = (char *) "../data/textures/characters/Boss2/Attack02/Attack02_";
        ABILITY_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    BossEnemy2::newWorld = false;
}

void BossEnemy2::collideAgainDecrement() {
    collideAgain--;
}