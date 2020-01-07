//
// Created by Andy He on 2019-12-07.
//

#ifndef ATTACKATLANTIS_PETROUTESYSTEM_HPP
#define ATTACKATLANTIS_PETROUTESYSTEM_HPP


#include <common.hpp>
#include <entities/movable.hpp>
#include "system.hpp"
#include <math.h>

class PetRouteSystem: public System {
public:
    bool init()override;

    void destroy()override;

    void update(float elapsedMs) override;

    bool setCenterPoint(vec2 point);

    bool setDestPoint(vec2 point);

    bool setVelocity(float v);

    void setEntityVelocity(Movable* entity);

private:
    float velocity;
    vec2 center_p;
    vec2 dest_p;
    float radius;
    int step_counter;
    int total_step;
    int update_step;
};


#endif //ATTACKATLANTIS_PETROUTESYSTEM_HPP
