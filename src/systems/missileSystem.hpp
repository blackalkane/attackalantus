//
// Created by Tim Guo on 2019-11-09.
//

#ifndef ATTACKATLANTIS_MISSILESYSTEM_HPP
#define ATTACKATLANTIS_MISSILESYSTEM_HPP


#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/enemyProjectile.hpp>
#include "system.hpp"

class MissileSystem: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    void setDestPoint(vec2 point);

    void setVelocity(float v);

    void setEntityVelocity(Movable *entity, float elapsedMs);

private:
    float velocity;
    vec2 destination;
    float const scale = 2.0f;
};


#endif //ATTACKATLANTIS_MISSILESYSTEM_HPP
