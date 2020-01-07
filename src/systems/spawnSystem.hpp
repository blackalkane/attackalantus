#ifndef ATTACKATLANTIS_SPAWNSYSTEM_HPP
#define ATTACKATLANTIS_SPAWNSYSTEM_HPP

#include "system.hpp"
#include <entities/rock.hpp>
#include <entities/entityType.hpp>
#include <entities/enemyType.hpp>
#include <entities/abilityContainer.hpp>
#include <entities/enemy.hpp>
#include <entities/particle.hpp>
#include <entities/rainDrop.hpp>
#include <entities/basicEnemy.hpp>
#include <entities/speedEnemy.hpp>
#include <entities/shootingEnemy.hpp>
#include "common.hpp"

class SpawnSystem : public System {
public:
    // constructor with default vals
    SpawnSystem();

//    explicit SpawnSystem(struct SpawnLimits initialLimit) {
//        currLimits = initialLimit;
//    }

    bool init() override;

    void destroy() override;

    void spawnEnemies();

    void update(float elapsed_Ms) override;

    bool addEntity(Entity *entity) override;

    bool removeEntity(Entity *entity) override;

    void setSpawnLimits(SpawnLimits *limits);

    // Set to true to spawn enemies on update.
    bool shouldSpawnEnemies;

    void resetLimits();

    void onEnemyDespawn(Enemy *enemyDespawning);

    void initAbilityContainer();

    void spawnParticle();

    bool spawnEnemy(EnemyType type);

    void spawnAbility();

    AbilityContainer *getCurrAbilityContainer();

protected:
    // Default values set here for lack of a better place; tweakable
    SpawnLimits initialLimits = {
            10, // Basic
            5, // Shooting
            10, // Speed
            60, // Frames until spawn
            3, // Max frames to decrement each update
            300, // Frames until the spawn rate increases
            20, // The highest speed allowed
            3, // How much faster, in frames, we should increase the spawn rate by
            10000.f, // Milliseconds until respawning the ability container
            60, // Frames until shoot
            1, // Boss
            1, // Boss2
            std::vector<AbilityType>() = {},
            std::vector<EnemyType>() = {},
    };

    SpawnLimits *currLimits;
    AbilityContainer *currContainer;
    std::vector<AbilityType> spawnableAbilityTypes;
    std::vector<EnemyType> spawnableEnemyTypes;

    // Current state.
    int framesUntilSpawn;
    int framesUntilSpeedup;
    int numBasicEnemies;
    int numShootingEnemies;
    int numSpeedEnemies;
    int numBossEnemies;
    int numBoss2Enemies;
    float timeUntilAbilitySpawn;

    bool updateBasic(int i);

    bool updateShooting(int i);

    bool updateSpeed(int i);

    bool updateBoss(int i);

    bool updateBoss2(int i);

    EnemyType chooseEnemyTypeToSpawn();

    bool typeIsAtLimit(EnemyType type);

    void destroyAbilityContainer(AbilityContainer *container);

    AbilityType chooseAbilityType();

    void deleteCurContainer();

    vec2 getValidSpawnPosition();

    Enemy *createEnemy(EnemyType type);
};

#endif //ATTACKATLANTIS_SPAWNSYSTEM_HPP
