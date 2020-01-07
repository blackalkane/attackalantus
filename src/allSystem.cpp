//
// Created by Andy He on 2019-10-27.
//

#include "allSystem.hpp"

std::vector<System *> AllSystem::getAllSystems() {
    return all_systems;
}

DrawSystem *AllSystem::getDrawSystem() {
    return &drawSystem;
}

AbilitySystem *AllSystem::getAbilitySystem() {
    return &abilitySystem;
}

DeleteSystem *AllSystem::getDeleteSystem() {
    return &deleteSystem;
}

ControlSystem *AllSystem::getControlSystem() {
    return &controlSystem;
}

CollisionSystem *AllSystem::getCollisionSystem() {
    return &collisionSystem;
}

MoveSystem *AllSystem::getMoveSystem() {
    return &moveSystem;
}
SoundSystem *AllSystem::getSoundSystem(){
    return &soundSystem;
}


bool AllSystem::init() {
    drawSystem.init();
    moveSystem.init();
    musicSystem.init();
    collisionSystem.init();
    simpleAiSystem.init();
    shootingAiSystem.init();
    bossAiSystem.init();
    bossAiSystem2.init();
    missileSystem.init();
    icePickSystem.init();
    controlSystem.init();
    abilitySystem.init();
    spawnSystem.init();
    deleteSystem.init();
    scoreSystem.init();
    soundSystem.init();
    particleEffectSystem.init();
    dynamicEntityStoreSystem.init();
    petRouteSystem.init();

    all_systems.push_back(&drawSystem);
    all_systems.push_back(&moveSystem);
    all_systems.push_back(&musicSystem);
    all_systems.push_back(&collisionSystem);
    all_systems.push_back(&simpleAiSystem);
    all_systems.push_back(&shootingAiSystem);
    all_systems.push_back(&bossAiSystem);
    all_systems.push_back(&bossAiSystem2);
    all_systems.push_back(&missileSystem);
    all_systems.push_back(&icePickSystem);
    all_systems.push_back(&controlSystem);
    all_systems.push_back(&abilitySystem);
    all_systems.push_back(&spawnSystem);
    all_systems.push_back(&scoreSystem);
    all_systems.push_back(&soundSystem);
    all_systems.push_back(&particleEffectSystem);
    all_systems.push_back(&petRouteSystem);

     // this is a special system, maybe just put it outside of the all systems list
     all_systems.push_back(&deleteSystem);

     //storage do it manually
     // all_systems.push_back(&dynamicEntityStoreSystem);
     return true;
}

void AllSystem::removeEntityFromSystems(Entity *toBeRemoved) {
    for (System *system : all_systems) {
        system->removeEntity(toBeRemoved);
    }
}

SimpleAISystem *AllSystem::getSimpleAISystem() {
    return &simpleAiSystem;
}

ShootingAISystem *AllSystem::getShootingAISystem() {
    return &shootingAiSystem;
}

BossAISystem *AllSystem::getBossAISystem() {
    return &bossAiSystem;
}

BossAISystem2 *AllSystem::getBossAISystem2() {
    return &bossAiSystem2;
}

MissileSystem *AllSystem::getMissileSystem() {
    return &missileSystem;
}

IcePickSystem *AllSystem::getIcePickSystem() {
    return &icePickSystem;
}

MusicSystem *AllSystem::getMusicSystem() {
    return &musicSystem;
}

SpawnSystem *AllSystem::getSpawnSystem() {
    return &spawnSystem;
}

ScoreSystem *AllSystem::getScoreSystem() {
    return &scoreSystem;
}

DynamicEntityStoreSystem *AllSystem::getDynamicEnitityStoreSystem() {
    return &dynamicEntityStoreSystem;
}

void AllSystem::destroy() {
    deleteSystem.update(0);
    deleteSystem.destroy();
    for (System* system : all_systems) {
        system->destroy();
    }

    dynamicEntityStoreSystem.destroy();

    for (Entity* entity : dynamicEntityList) {
        free(entity);
    }
    dynamicEntityList.clear();
}

void AllSystem::reset() {
    destroy();
    init();
}

std::vector<Entity *> AllSystem::getDynamicEntityList() {
    return dynamicEntityList;
}

ParticleEffectSystem *AllSystem::getParticleEffectSystem() {
    return &particleEffectSystem;
}

PetRouteSystem *AllSystem::getPetRouteSystem() {
    return &petRouteSystem;
}
