//
// Created by Tim Guo on 2019-11-05.
//

#ifndef ATTACKATLANTIS_BOSSAISYSTEM_HPP
#define ATTACKATLANTIS_BOSSAISYSTEM_HPP


#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/enemyProjectile.hpp>
#include "system.hpp"
#include "entities/bossEnemy.hpp"

class BossAISystem: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    void setDestPoint(vec2 point);

    void setVelocity(float v);

    void setEntityVelocity(Movable *entity, float elapsedMs);

    void setSpawnLimits(SpawnLimits *limits);

    BossEnemy* getBossTracker();

private:
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

    int framesUntilSpray;
    int framesUntilMachineGun;
    int framesUntilHoming;
    int shotsFired;
    int animationDuration;
    int nextBullet;
    int framesUntilUpdateVelocity;
    float velocity;
    vec2 destination;
    float const scale = 2.0f;
    float const numBullets = 7; // must be odd
    int close;
    BossEnemy* bossTracker;

    void shootSpray();

    void shootMachineGun();

    void shootHoming();

    void shootProjectileMachineGun(vec2 pos, float radian);

    void shootProjectileSpray(vec2 pos, float radian, int amount);
};


#endif //ATTACKATLANTIS_BOSSAISYSTEM_HPP
