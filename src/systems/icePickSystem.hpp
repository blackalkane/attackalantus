//
// Created by Tim Guo on 2019-11-08.
//

#ifndef ATTACKATLANTIS_ICEPICKSYSTEM_HPP
#define ATTACKATLANTIS_ICEPICKSYSTEM_HPP

#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/bossProjectile.hpp>
#include "system.hpp"

class IcePickSystem: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    void setDestPoint(vec2 point);

    void setVelocity(float v);

    void setHoming(bool home);

    void setEntityVelocity(Movable *entity, float elapsedMs);

    void setEntityVelocityHoming(Movable *entity, float elapsedMs);

private:
    float velocity;
    vec2 destination;
    float const scale = 2.0f;
    int framesUntilHoming;
    bool homing;
};


#endif //ATTACKATLANTIS_ICEPICKSYSTEM_HPP
