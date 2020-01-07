//
// Created by Tim Guo on 2019-11-06.
//


#include <global.hpp>
#include "bossAISystem2.hpp"

bool BossAISystem2::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    if (currLimits == nullptr) {
        currLimits = &initialLimits;
    }
    framesUntilSpray = currLimits->MAX_FRAMES_UNTIL_SHOOT*3;
    animationDuration = 30;
    return true;
}

void BossAISystem2::destroy() {
    System::destroy();
}

void BossAISystem2::update(float elapsedMs) {
    for(Entity* entity: entities){
        auto* movableEntity = dynamic_cast<Movable*>(entity);
        auto* bossEnemy2 = dynamic_cast<BossEnemy2*>(entity);
        bossEnemy2->collideAgainDecrement();
        bossTracker = bossEnemy2;
        setEntityVelocity(movableEntity, elapsedMs);

        int framesToDecrement = rand() % currLimits->MAX_FRAMES_TO_DECREMENT;
        framesUntilSpray -= framesToDecrement;
        animationDuration -= framesToDecrement;

        if (framesUntilSpray <= 60) {
            auto *drawableEntity = dynamic_cast<Drawable *>(entity);
            drawableEntity->setState(GameState::ABILITY);
            animationDuration = 30;
        }

        if (framesUntilSpray <= 0) {
            shootSpray();
            framesUntilSpray = currLimits->MAX_FRAMES_UNTIL_SHOOT*3;
        }
    }
}

void BossAISystem2::setDestPoint(vec2 point) {
    destination = point;
}

void BossAISystem2::setVelocity(float v) {
    velocity = v;
}

void BossAISystem2::setEntityVelocity(Movable *entity, float elapsedMs) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 position = entityPositionObj->getPosition();

    vec2 length = {destination.x - position.x, destination.y - position.y};
    float radian = atan2(length.y, length.x);
    float vx = 0,vy = 0;

    if (animationDuration <= 0) {
        auto* drawableEntity = dynamic_cast<Drawable*>(entity);
        drawableEntity->setState(GameState::MOVE);
    }

    vx = velocity * cos(radian);
    vy = velocity * sin(radian);

    entityVelocityObj->setVelocity({vx, vy});
}

void BossAISystem2::shootSpray() {
    if (entities.size() > 0) {
        auto theOneToShoot = rand() % entities.size();
        Entity* entity = entities.at(theOneToShoot);

        auto *movableEntity = dynamic_cast<Movable *>(entity);

        vec2 position = movableEntity->getPositionComponent()->getPosition();
        position.y += 50.0f;
        float radian = 0.0f;
        shootProjectileSpray(position, radian);
    }
}

void BossAISystem2::shootProjectileSpray(vec2 pos, float radian) {
    for (int i = 0; i <= 12; i++) {
        radian = (float) i * 3.1416 / 6;
        float vx = velocity * cos(radian) * scale;
        float vy = velocity * sin(radian) * scale;

        auto *proj = new BossProjectile();
        proj->init();
        proj->getPositionComponent()->setPosition(pos);
        proj->getVelocityComponent()->setVelocity({vx,vy});
        float drawingRadian;
        if (vx >= 0) {
            drawingRadian = radian;
        } else {
            drawingRadian = radian + 3.1415;
        }
        proj->getDrawComponent()->setRadian(drawingRadian);
        // TODO add back later
        // world.getEnemyProjectiles()->push_back(proj);
        syss->getDrawSystem()->addEntity((Drawable *) proj);
        syss->getIcePickSystem()->addEntity(proj);
        syss->getCollisionSystem()->addEntity((Collides *) proj);
    }

    syss->getIcePickSystem()->setHoming(false);
}

void BossAISystem2::setSpawnLimits(SpawnLimits *limits) {
    currLimits = limits;
}

BossEnemy2 *BossAISystem2::getBossTracker() {
    return bossTracker;
}