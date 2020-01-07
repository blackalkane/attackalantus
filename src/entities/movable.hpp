#ifndef MOVABLE_H
#define MOVABLE_H

#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include <components/drawComponent.hpp>
#include "entity.hpp"

struct Movable: public virtual Entity
{
    virtual PositionComponent* getPositionComponent() = 0;

    virtual VelocityComponent* getVelocityComponent() = 0;
};

#endif