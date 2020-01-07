//
// Created by Andy He on 2019-10-16.
//

#include <global.hpp>
#include "deleteSystem.hpp"

DeleteSystem::DeleteSystem() {

}

DeleteSystem::~DeleteSystem() {

}

bool DeleteSystem::init() {
    winningDeleteCounter = 0;
    return true;
}

void DeleteSystem::destroy() {
    entities.clear();
}

void DeleteSystem::update(float elapsedMs) {
    for(Entity* entity : entities){
        if(entity == nullptr){
            continue;
        }
        Drawable* dentity = dynamic_cast<Drawable*>(entity);
        if(dentity->getDrawComponent()->cycleFinish()) {
//            syss->removeEntityFromSystems(entity);
            syss->getDrawSystem()->removeEntity(entity);
            this->removeEntity(entity);
            if (entity->type == EntityType::PARTICLE) {
                syss->getParticleEffectSystem()->removeEntity(entity);
                syss->getDynamicEnitityStoreSystem()->removeEntity(entity);
            }
            if (entity->type == EntityType::PROJECTILE) {
                syss->getCollisionSystem()->removeEntity(entity);
                syss->getDynamicEnitityStoreSystem()->removeEntity(entity);
            }
            if (entity->type == EntityType::THEGUY) {
                defeatDeleteCounter--;
            }
            if (entity->type == EntityType::ENEMY) {
                winningDeleteCounter--;
                syss->getSpawnSystem()->onEnemyDespawn(dynamic_cast<Enemy *>(entity));
            }
        }
//        if(entity->type != EntityType::THEGUY) {
//            free(entity);
//            entity = nullptr;
//
//        }
    }
//    entities.clear();
}

int DeleteSystem::getWinningDeleteCounter() {
    return winningDeleteCounter;
}

void DeleteSystem::setWinningDeleteCounter(int v) {
    winningDeleteCounter = v;
}

int DeleteSystem::getDefeatDeleteCounter() {
    return defeatDeleteCounter;
}

void DeleteSystem::setDefeatDeleteCounter(int v) {
    defeatDeleteCounter = v;
}
