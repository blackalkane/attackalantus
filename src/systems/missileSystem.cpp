//
// Created by Tim Guo on 2019-11-09.
//dd
#define _USE_MATH_DEFINES
#include "missileSystem.hpp"
#include <cmath>


bool MissileSystem::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    return true;
}

void MissileSystem::destroy() {
    System::destroy();
}

void MissileSystem::update(float elapsedMs) {
    for(Entity* entity: entities){
        Movable* movableEntity = dynamic_cast<Movable*>(entity);
        setEntityVelocity(movableEntity, elapsedMs);
    }
}

void MissileSystem::setDestPoint(vec2 point) {
    destination = point;
}

void MissileSystem::setVelocity(float v) {
    velocity = v;
}

void MissileSystem::setEntityVelocity(Movable *entity, float elapsedMs) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 pos = entityPositionObj->getPosition();
    float rot = entityPositionObj->getRotation();
    vec2 vel = entityVelocityObj->getVelocity();

    vec2 direction = {destination.x - pos.x, destination.y - pos.y};
    float radian = atan2(direction.y, direction.x);
    if (abs(radian - entityPositionObj->getRotation()) > M_PI) {
        if (radian < 0 && entityPositionObj->getRotation() > 0) {
            entityPositionObj->setRotation(rot + (radian - rot)/10000.0f);
        } else if (radian > 0 && entityPositionObj->getRotation() < 0) {
            entityPositionObj->setRotation(rot - (-radian + rot)/10000.0f);
        }
    } else if (radian > entityPositionObj->getRotation()) {
        entityPositionObj->setRotation(rot + abs(radian - rot)/10000.0f);
    } else {
        entityPositionObj->setRotation(rot - abs(rot - radian)/10000.0f);
    }
    entityPositionObj->setRotation(radian);

    float vx, vy;
    float norm = sqrt(direction.x*direction.x+direction.y*direction.y);
    direction = {direction.x/norm, direction.y/norm};

    float rotate = direction.x * vel.y - direction.y * vel.x;

    //    float norm = sqrt(direction.x*direction.x+direction.y*direction.y);
//    direction = {direction.x/norm, direction.y/norm};
//
//    float rotate = direction.x * vel.y - direction.y * vel.x;
//    float vx = vel.x, vy = vel.y;
//
//    if (rotate < 0) {
//        vx = velocity * cos(-rotate) * 1.5;
//        vy = velocity * sin(-rotate) * 1.5;
//    } else if (rotate > 0) {
//        vx = velocity * cos(-rotate) * 1.5;
//        vy = velocity * sin(-rotate) * 1.5;
//    } else {
//        rotate = direction.x * vel.x + direction.y * vel.y;
//        if (rotate > 0) {
//            vx = velocity * cos(-rotate) * 1.5;
//            vy = velocity * sin(-rotate) * 1.5;
//        }
//    }

    vx = velocity * ((float) M_PI_2 - abs(entityPositionObj->getRotation())) / (float) M_PI_2;
    entityPositionObj->getRotation() < 0 ? vy = -velocity + abs(vx) : vy = velocity - abs(vx);

    entityPositionObj->setPosition({pos.x+vx, pos.y+vy});
}
