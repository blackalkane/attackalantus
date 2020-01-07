#ifndef ENEMY_H
#define ENEMY_H
#include "movable.hpp"
#include "drawable.hpp"
#include "collides.hpp"
#include "hasHealth.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include "enemyType.hpp"


struct Enemy: public virtual Entity, public virtual Movable, public virtual Drawable, public virtual Collides, public virtual HasHealth
{
public:

    virtual PositionComponent* getPositionComponent() = 0;

    virtual DrawComponent* getDrawComponent() = 0;

    virtual VelocityComponent* getVelocityComponent() = 0;

    virtual HealthComponent* getHealthComponent() = 0;

    virtual bool handleCollision(Collides* collidedWith) = 0;

    virtual void killSelf() = 0;

    virtual void resetPosition(Collides* collidedWith) = 0;

    EnemyType getEnemyType() {
        return enemyType;
    }

protected:
    EnemyType enemyType;
};

#endif