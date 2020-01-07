//
// Created by Peter Han on 2019-10-20.
//

#ifndef ATTACKATLANTIS_SHOOT_HPP
#define ATTACKATLANTIS_SHOOT_HPP


#include <common.hpp>
#include <entities/projectile.hpp>
#include "abilityComponent.hpp"

class Shoot : public AbilityComponent {
public:
    Shoot();
    ~Shoot();

    void update() override;

    void setMousePos(vec2 pos) override;

    void setShootingObject(Drawable* d);

private:
    Projectile *projectile;
    Drawable* shootingObject;
};


#endif //ATTACKATLANTIS_SHOOT_HPP
