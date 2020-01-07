//
// Created by Andy He on 2019-12-01.
//

#include "dynamicEntityStoreSystem.hpp"

bool DynamicEntityStoreSystem::removeEntity(Entity *entity) {
    if(System::removeEntity(entity)) {
//        free(entity);
//        delete entity;
        return true;
    } else {
        return false;
    }
}

bool DynamicEntityStoreSystem::init() {
    return true;
}

void DynamicEntityStoreSystem::destroy() {
    for(Entity* entity : entities) {
//        delete entity;
    }
    entities.clear();
}

void DynamicEntityStoreSystem::update(float elapsedMs) {
    // do nothing, just a storage room
}
