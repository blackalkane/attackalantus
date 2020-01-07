//
// Created by Tim Guo on 2019-10-20.
//

#ifndef ATTACKATLANTIS_SHOOTINGAISYSTEM_HPP
#define ATTACKATLANTIS_SHOOTINGAISYSTEM_HPP


#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/enemyProjectile.hpp>
#include "system.hpp"

class ShootingAISystem: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    bool setDestPoint(vec2 point);

    bool setVelocity(float v);

    void setEntityVelocity(Movable *entity);

    void shoot();

    void setSpawnLimits(SpawnLimits *limits);

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

    int framesUntilShoot;
    float velocity{};
    vec2 destination{};
};


#endif //ATTACKATLANTIS_SHOOTINGAISYSTEM_HPP
