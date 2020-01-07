//
// Created by Tim Guo on 2019-11-06.
//

#ifndef ATTACKATLANTIS_BOSSAISYSTEM2_HPP
#define ATTACKATLANTIS_BOSSAISYSTEM2_HPP


#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/bossProjectile.hpp>
#include "system.hpp"
#include <entities/bossEnemy2.hpp>


class BossAISystem2: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    void setDestPoint(vec2 point);

    void setVelocity(float v);

    void setEntityVelocity(Movable *entity, float elapsedMs);

    void setSpawnLimits(SpawnLimits *limits);

    BossEnemy2* getBossTracker();

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
    int animationDuration;
    float velocity;
    vec2 destination;
    float const scale = 3.0f;

    BossEnemy2* bossTracker;

    void shootSpray();

    void shootProjectileSpray(vec2 pos, float radian);
};


#endif //ATTACKATLANTIS_BOSSAISYSTEM2_HPP
