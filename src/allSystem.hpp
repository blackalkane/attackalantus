//
// Created by Andy He on 2019-10-27.
//

#ifndef ATTACKATLANTIS_ALLSYSTEM_HPP
#define ATTACKATLANTIS_ALLSYSTEM_HPP


#include <systems/system.hpp>
#include <systems/moveSystem.hpp>
#include <systems/drawSystem.hpp>
#include <systems/musicSystem.hpp>
#include <systems/collisionSystem.hpp>
#include <systems/simpleAISystem.hpp>
#include <systems/controlSystem.hpp>
#include <systems/abilitySystem.hpp>
#include <systems/deleteSystem.hpp>
#include <systems/scoreSystem.hpp>
#include <systems/spawnSystem.hpp>
#include <systems/shootingAISystem.hpp>
#include <systems/soundSystem.hpp>
#include <systems/bossAISystem.hpp>
#include <systems/bossAISystem2.hpp>
#include <systems/missileSystem.hpp>
#include <systems/icePickSystem.hpp>
#include <systems/dynamicEntityStoreSystem.hpp>
#include <systems/particleEffectSystem.hpp>
#include <systems/petRouteSystem.hpp>

class AllSystem {
public:

    std::vector<System *> getAllSystems();

    std::vector<Entity *> getDynamicEntityList();

    DrawSystem *getDrawSystem();

    DynamicEntityStoreSystem* getDynamicEnitityStoreSystem();

    AbilitySystem *getAbilitySystem();

    DeleteSystem *getDeleteSystem();

    ControlSystem *getControlSystem();

    CollisionSystem *getCollisionSystem();

    MoveSystem *getMoveSystem();

    SimpleAISystem *getSimpleAISystem();

    ShootingAISystem *getShootingAISystem();

    BossAISystem *getBossAISystem();

    BossAISystem2 *getBossAISystem2();

    MissileSystem *getMissileSystem();

    IcePickSystem *getIcePickSystem();

    MusicSystem *getMusicSystem();

    SpawnSystem *getSpawnSystem();

    ScoreSystem *getScoreSystem();

    SoundSystem *getSoundSystem();

    ParticleEffectSystem *getParticleEffectSystem();

    PetRouteSystem *getPetRouteSystem();

    void removeEntityFromSystems(Entity *toBeRemoved);

    bool init();

    void destroy();

    void reset();

private:

    // put here for now
    std::vector<Entity *> dynamicEntityList;

    std::vector<System *> all_systems;

    DrawSystem drawSystem;
    MoveSystem moveSystem;
    MusicSystem musicSystem;
    CollisionSystem collisionSystem;
    SimpleAISystem simpleAiSystem;
    ShootingAISystem shootingAiSystem;
    BossAISystem bossAiSystem;
    BossAISystem2 bossAiSystem2;
    MissileSystem missileSystem;
    IcePickSystem icePickSystem;
    ControlSystem controlSystem;
    AbilitySystem abilitySystem;
    SpawnSystem spawnSystem;
    DeleteSystem deleteSystem;
    DynamicEntityStoreSystem dynamicEntityStoreSystem;
    ScoreSystem scoreSystem;
    SoundSystem soundSystem;
    ParticleEffectSystem particleEffectSystem;
    PetRouteSystem petRouteSystem;
};


#endif //ATTACKATLANTIS_ALLSYSTEM_HPP
