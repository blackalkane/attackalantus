#include <global.hpp>
#include "speedEnemy.hpp"

std::vector<Texture*> SpeedEnemy::IDLE_TEXTURES = {};

std::vector<Texture*> SpeedEnemy::DEATH_TEXTURES = {};

bool SpeedEnemy::newWorld = true;

bool SpeedEnemy::init() {
    drawComp.fragmentShaderPath = shader_path("enemy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("enemy.vs.glsl");
    vec2 scale = {2, 2};
    drawComp.physics.scale = {scale.x, scale.y};
    int frame, spriteTime = 4;
    preloadTexture();
    frame = spriteTime * IDLE_TEXTURES.size();
    drawComp.setNewAnimation(IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;

    positionComp.setWidth((texture->width) * scale.x * 0.6);
    positionComp.setHeight((texture->height) * scale.y * 0.5);

    healthComp.init();
    healthComp.setHealth(1);

    type = EntityType::ENEMY;
    enemyType = EnemyType::SPEED;
    return true;
}


void SpeedEnemy::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

PositionComponent *SpeedEnemy::getPositionComponent() {
    return &positionComp;
}

DrawComponent *SpeedEnemy::getDrawComponent() {
    return &drawComp;
}

VelocityComponent *SpeedEnemy::getVelocityComponent() {
    return &velocityComp;
}

bool SpeedEnemy::handleCollision(Collides *collidedWith) {
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

void SpeedEnemy::killSelf() {
    syss->removeEntityFromSystems(this);
//    world.killEntity(this);
    destroy();
}

void SpeedEnemy::resetPosition(Collides* collidedWith) {
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

void SpeedEnemy::loadStateSprite() {
    int currentState = entityState.getState();
    if (currentState == entityState.getPreFrameState() || currentState == GameState::ABILITY) {
        // do nothing
        return;
    }
    int frame, spriteTime;
    switch(currentState) {
        case GameState::MOVE:
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

HealthComponent *SpeedEnemy::getHealthComponent() {
    return &healthComp;
}

void SpeedEnemy::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/characters/enemies/Golem/Golem_move_0";
        startIndex = 0, numOfSprite = 8;
        IDLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        startIndex = 0, numOfSprite = 5;
        path = (char *) "../data/textures/characters/enemies/Golem/Golem_death_0";
        DEATH_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;

}





