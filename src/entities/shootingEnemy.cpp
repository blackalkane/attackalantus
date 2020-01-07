#include <global.hpp>
#include "shootingEnemy.hpp"


std::vector<Texture*> ShootingEnemy::S_IDLE_TEXTURES = {};

std::vector<Texture*> ShootingEnemy::S_DEATH_TEXTURES = {};

std::vector<Texture*> ShootingEnemy::S_MOVE_TEXTURES = {};

bool ShootingEnemy::newWorld = true;

bool ShootingEnemy::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");
//    drawComp.PNGPath = "../data/textures/characters/enemies/devil/devil_idle_00.png";

    drawComp.physics.scale = {2, 2};
    preloadTexture();
    int frame, spriteTime = 4, startIndex = 0, numOfSprite = 7;
    char* path = (char *) "../data/textures/characters/enemies/devil/devil_idle_0";
//    idleTextures = setTexture(path, (char*) "png", startIndex, numOfSprite);
    frame = spriteTime * numOfSprite;
    drawComp.setNewAnimation(S_IDLE_TEXTURES,frame, spriteTime);
//    drawComp.preInit(frame, spriteTime, path, (char *) "png", startIndex, numOfSprite);
    drawComp.init();

//    spriteTime = 4, startIndex = 1, numOfSprite = 9;
//    path = (char *) "../data/textures/characters/enemies/boss_shooter/die/die_0";
//    deathTextures = setTexture(path, (char*) "png", startIndex, numOfSprite);
//    drawComp.setTextures(idleTextures);


    Texture *texture = drawComp.texture;
  
    positionComp.setWidth((texture->width) * 2);
    positionComp.setHeight((texture->height) * 2);

    healthComp.init();

    type = EntityType::ENEMY;
    enemyType = EnemyType::SHOOTING;
    return true;
}


void ShootingEnemy::destroy() {
    positionComp.destroy();
    drawComp.destroy();
    velocityComp.destroy();
}

PositionComponent *ShootingEnemy::getPositionComponent() {
    return &positionComp;
}

DrawComponent *ShootingEnemy::getDrawComponent() {
    return &drawComp;
}

VelocityComponent *ShootingEnemy::getVelocityComponent() {
    return &velocityComp;
}

bool ShootingEnemy::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::THEGUY:
        case EntityType::PET:
        case EntityType::PROJECTILE:
        case EntityType::BOOMERANG_PROJECTILE:
            healthComp.dead();
            syss->getSoundSystem()->playMinionDamageMusic();
            return true;
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        case EntityType::ROCK:
            resetPosition(collidedWith);
            break;
        default:;
    }
    return false;
}

void ShootingEnemy::killSelf() {
    syss->removeEntityFromSystems(this);
//    world.killEntity(this);
    destroy();
}

void ShootingEnemy::resetPosition(Collides* collidedWith) {
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

HealthComponent *ShootingEnemy::getHealthComponent() {
    return &healthComp;
}

void ShootingEnemy::loadStateSprite() {
    int currentState = entityState.getState();
    if (currentState == entityState.getPreFrameState() || currentState == GameState::ABILITY) {
        // do nothing
        return;
    }
    int frame, spriteTime;
    switch(currentState) {
        case GameState::MOVE:
            spriteTime = 4;
            frame = spriteTime * S_MOVE_TEXTURES.size();
            drawComp.setNewAnimation(S_MOVE_TEXTURES,frame, spriteTime);
            break;
        case GameState::IDLE:
            spriteTime = 4;
            frame = spriteTime * S_IDLE_TEXTURES.size();
            drawComp.setNewAnimation(S_IDLE_TEXTURES,frame, spriteTime);
            break;
        case GameState::DEATH:
            spriteTime = 4;
            //path = (char *) "../data/textures/characters/enemies/boss_shooter/die/die_0";
            frame = spriteTime * S_DEATH_TEXTURES.size();
            drawComp.setNewAnimation(S_DEATH_TEXTURES,frame, spriteTime);
            //drawComp.preInit(frame, spriteTime, path, (char *) "png", startIndex, numOfSprite);
            //drawComp.init();
            return;
    }
}

void ShootingEnemy::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        emptyTextureVector(S_IDLE_TEXTURES);
        path = (char *) "../data/textures/characters/enemies/devil/devil_idle_0";
        startIndex = 0, numOfSprite = 7;
        S_IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

    }
    if(newWorld) {
        emptyTextureVector(S_DEATH_TEXTURES);
        startIndex = 0, numOfSprite = 6;
        path = (char *) "../data/textures/characters/enemies/devil/devil_death_0";
        S_DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    if(newWorld) {
        emptyTextureVector(S_MOVE_TEXTURES);
        startIndex = 0, numOfSprite = 8;
        path = (char *) "../data/textures/characters/enemies/devil/devil_move_0";
        S_MOVE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    ShootingEnemy::newWorld = false;

}



