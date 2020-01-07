//
// Created by Tim Guo on 2019-11-05.
//

#include <thread>
#include <chrono>

#include <global.hpp>
#include "bossAISystem.hpp"

bool BossAISystem::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    if (currLimits == nullptr) {
        currLimits = &initialLimits;
    }
    framesUntilSpray = currLimits->MAX_FRAMES_UNTIL_SHOOT;
    framesUntilMachineGun = currLimits->MAX_FRAMES_UNTIL_SHOOT/5;
    framesUntilHoming = currLimits->MAX_FRAMES_UNTIL_SHOOT*2;
    shotsFired = 0;
    animationDuration = 50;
    nextBullet = 100;
    framesUntilUpdateVelocity = 60;
    close = 0;
    return true;
}

void BossAISystem::destroy() {
    System::destroy();
}

void BossAISystem::update(float elapsedMs) {
    for(Entity* entity: entities){
        auto* movableEntity = dynamic_cast<Movable*>(entity);
        auto* bossEnemy = dynamic_cast<BossEnemy*>(entity);
        bossEnemy->collideAgainDecrement();
        bossTracker = bossEnemy;

        int framesToDecrement = rand() % currLimits->MAX_FRAMES_TO_DECREMENT;
        framesUntilSpray -= framesToDecrement;
        framesUntilMachineGun -= framesToDecrement;
        framesUntilHoming -= framesToDecrement;
        animationDuration -= framesToDecrement;
        framesUntilUpdateVelocity -= framesToDecrement;

        if (framesUntilUpdateVelocity <= 0) {
            setEntityVelocity(movableEntity, elapsedMs);
            framesUntilUpdateVelocity = 60;
        }

        if (close == 0) {
            if (framesUntilSpray <= 0 ) {
                shootSpray();
                framesUntilSpray = currLimits->MAX_FRAMES_UNTIL_SHOOT;
                animationDuration = 50;
            }
        } else if (close == 1) {
            if (framesUntilMachineGun <= 0 ) {
                shootMachineGun();
                if (shotsFired > 10) {
                    framesUntilMachineGun = currLimits->MAX_FRAMES_UNTIL_SHOOT*2;
                    shotsFired = 0;
                } else {
                    framesUntilMachineGun = currLimits->MAX_FRAMES_UNTIL_SHOOT/5;
                }
                animationDuration = 50;
            }
        } else if (close == 2) {
            if (framesUntilHoming <= 0 ) {
                shootHoming();
                framesUntilHoming = currLimits->MAX_FRAMES_UNTIL_SHOOT*2;
                animationDuration = 50;
            }
        }
    }
}

void BossAISystem::setDestPoint(vec2 point) {
    destination = point;
}

void BossAISystem::setVelocity(float v) {
    velocity = v;
}

void BossAISystem::setEntityVelocity(Movable *entity, float elapsedMs) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 position = entityPositionObj->getPosition();

    vec2 length = {destination.x - position.x, destination.y - position.y};
    float radian = atan2(length.y, length.x);
    float vx = 0,vy = 0;

    if (abs(length.x) > 600 || abs(length.y) > 400) {
        close = 2;
        if (animationDuration <= 0) {
            auto* drawableEntity = dynamic_cast<Drawable*>(entity);
            drawableEntity->setState(GameState::IDLE);
        }
        vx = 0.f;
        vy = 0.f;
    } else if (abs(length.x) <= 300 && abs(length.y) <= 200) {
        close = 0;
        if (animationDuration <= 0) {
            auto* drawableEntity = dynamic_cast<Drawable*>(entity);
            drawableEntity->setState(GameState::MOVE);
        }
        vx = velocity * cos(radian);
        vy = velocity * sin(radian);
    } else {
        close = 1;
        if (animationDuration <= 0) {
            auto* drawableEntity = dynamic_cast<Drawable*>(entity);
            drawableEntity->setState(GameState::MOVE);
        }
        vx = velocity * cos(radian);
        vy = velocity * sin(radian);
    }

    entityVelocityObj->setVelocity({vx, vy});
}

void BossAISystem::shootSpray() {
    if (entities.size() > 0) {
        auto theOneToShoot = rand() % entities.size();
        Entity* entity = entities.at(theOneToShoot);

        auto *movableEntity = dynamic_cast<Movable *>(entity);
        auto *drawableEntity = dynamic_cast<Drawable *>(entity);
        drawableEntity->setState(GameState::ABILITY);

        vec2 position = movableEntity->getPositionComponent()->getPosition();
        vec2 length = {destination.x - position.x, destination.y - position.y};
        float radian = atan2(length.y, length.x);

        shootProjectileSpray(position, radian, numBullets);
    }
}

void BossAISystem::shootProjectileSpray(vec2 pos, float radian, int amount) {
    float offset = 1.0f/amount;
    for (int i = 0; i <= floor(amount/2); i++) {
        float vx = velocity * cos(radian + offset*(float)i) * scale * 2;
        float vy = velocity * sin(radian + offset*(float)i) * scale * 2;

        auto *proj = new EnemyProjectile();
        proj->init();
        proj->getPositionComponent()->setPosition(pos);
        proj->getVelocityComponent()->setVelocity({vx,vy});
        // TODO add back later
        // world.getEnemyProjectiles()->push_back(proj);
        syss->getDrawSystem()->addEntity((Drawable *) proj);
        syss->getMoveSystem()->addEntity((Movable *) proj);
        syss->getCollisionSystem()->addEntity((Collides *) proj);
    }

    for (int i = 1; i <= floor(amount/2); i++) {
        float vx = velocity * cos(radian + -offset*(float)i) * scale * 2;
        float vy = velocity * sin(radian + -offset*(float)i) * scale * 2;

        auto *proj = new EnemyProjectile();
        proj->init();
        proj->getPositionComponent()->setPosition(pos);
        proj->getVelocityComponent()->setVelocity({vx,vy});
        // TODO add back later
        // world.getEnemyProjectiles()->push_back(proj);
        syss->getDrawSystem()->addEntity((Drawable *) proj);
        syss->getMoveSystem()->addEntity((Movable *) proj);
        syss->getCollisionSystem()->addEntity((Collides *) proj);

        // for angle in drawing
//        not working!!! need tim help
//        float drawingRadian;
//        if (vx > 0 && vy > 0){
//            drawingRadian = (radian + -offset*(float)i);
//        } else {
//            drawingRadian = (radian + -offset*(float)i) + 3.1415;
//        }
//        proj->getDrawComponent()->setRadian(radian + -offset*(float)i);
    }
}

void BossAISystem::shootMachineGun() {
    if (entities.size() > 0) {
        auto theOneToShoot = rand() % entities.size();
        Entity* entity = entities.at(theOneToShoot);

        auto *movableEntity = dynamic_cast<Movable *>(entity);
        auto *drawableEntity = dynamic_cast<Drawable *>(entity);
        drawableEntity->setState(GameState::ABILITY);
        vec2 position = movableEntity->getPositionComponent()->getPosition();
        vec2 length = {destination.x - position.x, destination.y - position.y};
        float radian = atan2(length.y, length.x);

        shootProjectileMachineGun(position, radian);
    }
}

void BossAISystem::shootProjectileMachineGun(vec2 pos, float radian) {
    float rad = -0.2f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.2f-(-0.2f))));
    float vx = velocity * cos(radian + rad) * scale;
    float vy = velocity * sin(radian + rad) * scale;

    auto *proj = new EnemyProjectile();
    proj->init();
    proj->getPositionComponent()->setPosition(pos);
    proj->getVelocityComponent()->setVelocity({vx,vy});
    float drawingRadian;
    if (vx > 0){
        drawingRadian = radian + rad;
    } else {
        drawingRadian = radian + rad + 3.1415;
    }
    proj->getDrawComponent()->setRadian(drawingRadian);
    // TODO add back later
    // world.getEnemyProjectiles()->push_back(proj);
    syss->getDrawSystem()->addEntity((Drawable *) proj);
    syss->getMoveSystem()->addEntity((Movable *) proj);
    syss->getCollisionSystem()->addEntity((Collides *) proj);

    shotsFired++;
}

void BossAISystem::shootHoming() {
    if (entities.size() > 0) {
        auto theOneToShoot = rand() % entities.size();
        Entity* entity = entities.at(theOneToShoot);

        auto *movableEntity = dynamic_cast<Movable *>(entity);
        auto *drawableEntity = dynamic_cast<Drawable *>(entity);
        drawableEntity->setState(GameState::ABILITY);
        vec2 position = movableEntity->getPositionComponent()->getPosition();
        vec2 length = {destination.x - position.x, destination.y - position.y};
        float radian = atan2(length.y, length.x);

        float rad = -0.2f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.2f-(-0.2f))));
        float vx = velocity * cos(radian + rad) * scale;
        float vy = velocity * sin(radian + rad) * scale;

        auto *proj = new EnemyProjectile();
        proj->init();
        proj->getPositionComponent()->setPosition(position);
        proj->getVelocityComponent()->setVelocity({vx,vy});
        // TODO add back later
        // world.getEnemyProjectiles()->push_back(proj);
        syss->getDrawSystem()->addEntity((Drawable *) proj);
        syss->getMissileSystem()->addEntity(proj);
        syss->getCollisionSystem()->addEntity((Collides *) proj);

        shotsFired++;
    }
}

void BossAISystem::setSpawnLimits(SpawnLimits *limits) {
    currLimits = limits;
}

BossEnemy *BossAISystem::getBossTracker() {
    return bossTracker;
}


