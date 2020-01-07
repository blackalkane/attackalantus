//
// Created by Andy He on 2019-12-05.
//

#ifndef ATTACKATLANTIS_ONFIRE_HPP
#define ATTACKATLANTIS_ONFIRE_HPP


#include <entities/drawable.hpp>
#include <entities/particle.hpp>
#include <entities/pork.hpp>
#include "abilityComponent.hpp"
//#include "common.hpp"

class OnFire: public AbilityComponent {
public:
    OnFire();
    ~OnFire();
    void setFireEntity(Drawable* fEntity);

    void finish() override;

    void update() override;
private:
    Drawable* onFireEntity;
};


#endif //ONFIRE_HPP
