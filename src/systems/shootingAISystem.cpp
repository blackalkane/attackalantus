//
// Created by Tim Guo on 2019-10-20.
//

#include <global.hpp>
#include "shootingAISystem.hpp"

bool ShootingAISystem::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    if (currLimits == nullptr) {
        currLimits = &initialLimits;
    }
    framesUntilShoot = currLimits->MAX_FRAMES_UNTIL_SHOOT;
    return true;
}

void ShootingAISystem::destroy() {
    System::destroy();
}

void ShootingAISystem::update(float elapsedMs) {
    for(Entity* entity: entities){
        Movable* movableEntity = dynamic_cast<Movable*>(entity);
        setEntityVelocity(movableEntity);

        int framesToDecrement = rand() % currLimits->MAX_FRAMES_TO_DECREMENT;;
        framesUntilShoot -= framesToDecrement;
        if (framesUntilShoot <= 0 ) {
            shoot();
            framesUntilShoot = currLimits->MAX_FRAMES_UNTIL_SHOOT;
        }
    }
}

bool ShootingAISystem::setDestPoint(vec2 point) {
    destination = point;
    return true;
}

void ShootingAISystem::setEntityVelocity(Movable *entity) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 position = entityPositionObj->getPosition();

    vec2 length = {destination.x - position.x, destination.y - position.y};

    vec2 ratio = {};

    float manhanttan_distance = abs(length.x) + abs(length.y);
    if (manhanttan_distance == 0.f) {
        ratio = {1.0, 1.0};
    } else {
        ratio = {abs(length.x) / manhanttan_distance, abs(length.y) / manhanttan_distance};
    }

    float vx , vy;
    if (length.x < 200 && length.x > 100) {
        vx = ratio.x * -velocity;
    } else if (length.x > -200 && length.x < -100) {
        vx = ratio.x * velocity;
    } else {
        vx = 0.f;
    }

    if (length.y < 200 && length.y > 100) {
        vy = ratio.y * -velocity;
    } else if (length.y > -200 && length.y < -100) {
        vy = ratio.y * velocity;
    } else {
        vy = 0.f;
    }

    entityVelocityObj->setVelocity({vx, vy});
}


bool ShootingAISystem::setVelocity(float v) {
    velocity = v;
    return true;
}

void ShootingAISystem::shoot() {
    if (entities.size() > 0) {
        auto theOneToShoot = rand() % entities.size();

        Entity* entity = entities.at(theOneToShoot);
        auto *proj = new EnemyProjectile();
        proj->init();

        auto *movableEntity = dynamic_cast<Movable *>(entity);
        vec2 position = movableEntity->getPositionComponent()->getPosition();

        proj->getPositionComponent()->setPosition(position);

        vec2 length = {destination.x - position.x, destination.y - position.y};
        float radian = atan2(length.y, length.x);
        float vx = velocity * cos(radian) * 1.5;
        float vy = velocity * sin(radian) * 1.5;

        proj->getVelocityComponent()->setVelocity({vx, vy});

        float drawingRadian;
        if (length.x > 0){
            drawingRadian = radian;
        } else {
            drawingRadian = radian + 3.1415;
        }
        proj->getDrawComponent()->setRadian(drawingRadian);

        // TODO, understand what this do and added back later
        // world.getEnemyProjectiles()->push_back(proj);
        syss->getDrawSystem()->addEntity((Drawable *) proj);
        syss->getMoveSystem()->addEntity((Movable *) proj);
        syss->getCollisionSystem()->addEntity((Collides *) proj);
    }
}

void ShootingAISystem::setSpawnLimits(SpawnLimits *limits) {
    currLimits = limits;
}
