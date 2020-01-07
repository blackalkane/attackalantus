//
// Created by Tim Guo on 2019-11-08.
//

#include "icePickSystem.hpp"

bool IcePickSystem::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    homing = false;
    framesUntilHoming = 250;
    return true;
}

void IcePickSystem::destroy() {
    System::destroy();
}

void IcePickSystem::update(float elapsedMs) {
    for(Entity* entity: entities){
        Movable* movableEntity = dynamic_cast<Movable*>(entity);
        framesUntilHoming -= 1;

        setEntityVelocity(movableEntity, elapsedMs);

        if (framesUntilHoming <= 0) {
            setEntityVelocityHoming(movableEntity, elapsedMs);
            framesUntilHoming = 250;
        }
    }
}

void IcePickSystem::setDestPoint(vec2 point) {
    destination = point;
}

void IcePickSystem::setVelocity(float v) {
    velocity = v;
}

void IcePickSystem::setHoming(bool home) {
    homing = home;
}

void IcePickSystem::setEntityVelocity(Movable *entity, float elapsedMs) {
    VelocityComponent *entityVelocityObj = entity->getVelocityComponent();
    PositionComponent *entityPositionObj = entity->getPositionComponent();

    entityPositionObj->setPosition({entityPositionObj->getPosX() + entityVelocityObj->getVX(),
                           entityPositionObj->getPosY() + entityVelocityObj->getVY()});
}

void IcePickSystem::setEntityVelocityHoming(Movable *entity, float elapsedMs) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 pos = entityPositionObj->getPosition();

    vec2 direction = {destination.x - pos.x, destination.y - pos.y};
    float radian = atan2(direction.y, direction.x);

    float vx = velocity * cos(radian);
    float vy = velocity * sin(radian);

    entityVelocityObj->setVelocity({vx, vy});
    float drawingRadian;
    if (vx >= 0){
        drawingRadian = radian;
    } else {
        drawingRadian = radian + 3.1415;
    }

    auto *bossProjectileEntity = dynamic_cast<BossProjectile *>(entity);
    bossProjectileEntity->getDrawComponent()->setRadian(drawingRadian);
}