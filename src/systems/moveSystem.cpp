#include <entities/movable.hpp>
#include <global.hpp>
#include <entities/boomerangProjectile.hpp>
#include "moveSystem.hpp"
#include "common.hpp"

MoveSystem::MoveSystem() {

}

MoveSystem::~MoveSystem() {

}

bool MoveSystem::init() {
//    glfwGetFramebufferSize(world.m_window, &windowWidth, &windowHeight);
    return true;
}

void MoveSystem::destroy() {
    System::destroy();
}

//bool MoveSystem::addEntity(Movable* object){
//	entities.push_back(object);
//	return true;
//}
//
//bool MoveSystem::removeEntity(Entity* object){
//    int elementIndex = -1;
//    for (int i = 0; i < entities.size(); i++){
//        if (entities[i] == object){
//            elementIndex = i;
//            break;
//            // free(entities[i]);
//        }
//    }
//    if (elementIndex == -1){
//        return false;
//    }
//    entities.erase(entities.begin() + elementIndex);
//    return true;
//}

void MoveSystem::update(float elapsedMs) {
    for (int i = 0; i < entities.size(); i++) {
        Movable *moveEntity = dynamic_cast<Movable *>(entities[i]);
        move(moveEntity);
    }
}

void MoveSystem::move(Movable *movingEntity) {
    // set previous pos
    VelocityComponent *velocity = movingEntity->getVelocityComponent();
    PositionComponent *position = movingEntity->getPositionComponent();
    EntityType type = movingEntity->type;

//    position->setPrePosition(position->getPosition());
    // actual
    position->setPosition({position->getPosX() + velocity->getVX(),
                           position->getPosY() + velocity->getVY()});
    switch (type) {
        case EntityType::THEGUY: // FALL THROUGH
        case EntityType::ENEMY:
            if ((position->getPosX() <= 0.f + position->getWidth() * 0.4) &&
                     (position->getPosY() <= 0.f + position->getHeight() * 0.4)) {
                position->resetPosX();
                position->resetPosY();
            } else if ((position->getPosX() <= 0.f + position->getWidth() * 0.4) &&
                    (position->getPosY() + position->getHeight() >= (float) windowHeight)) {
                position->resetPosX();
                position->resetPosY();
            } else if ((position->getPosX() + position->getWidth() * 0.6 >= (float) windowWidth) &&
                   (position->getPosY() <= 0.f + position->getHeight() * 0.4)) {
                position->resetPosX();
                position->resetPosY();
            } else if ((position->getPosX() + position->getWidth() * 0.6 >= (float) windowWidth) &&
                   (position->getPosY() + position->getHeight() >= (float) windowHeight)) {
                position->resetPosX();
                position->resetPosY();
            } else if (position->getPosX() <= 0.f + position->getWidth() * 0.4) {
//                resetPosition(position,velocity);
                position->resetPosX();
            } else if (position->getPosX() + position->getWidth() * 0.6 >= (float) windowWidth) {
//                resetPosition(position,velocity);
                position->resetPosX();
            } else if (position->getPosY() <= 0.f + position->getHeight() * 0.4) {
//                resetPosition(position,velocity);
                position->resetPosY();
            } else if (position->getPosY() + position->getHeight() >= (float) windowHeight) {
//                resetPosition(position,velocity);
                position->resetPosY();
            }
            break;
        case EntityType::BOOMERANG_PROJECTILE: {
            auto boomerang = dynamic_cast<BoomerangProjectile *>(movingEntity);
            vec2 updatedVelocity = boomerang->getUpdatedVelocity();
            velocity->setVelocity(updatedVelocity);
            break;
        }
        case EntityType::PROJECTILE: // FALL THROUGH
        case EntityType::ENEMY_PROJECTILE:break;
        default:;
    }
}

bool MoveSystem::shouldReverseDirection(const vec2 &currVelocity, const vec2 &originalDir) const {
    float epsilon = 0.05f;
    return (currVelocity.x / originalDir.x <= epsilon) || (currVelocity.y / originalDir.y <= epsilon);
}

void MoveSystem::resetPosition(PositionComponent *position, VelocityComponent *velocity) {
    position->setPosition({position->getPosX() - velocity->getVX(),
                           position->getPosY() - velocity->getVY()});
}

void MoveSystem::setBoundary(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}
