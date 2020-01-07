#ifndef ATTACKATLANTIS_BOOMERANGABILITY_HPP
#define ATTACKATLANTIS_BOOMERANGABILITY_HPP


#include <common.hpp>
#include <entities/boomerangProjectile.hpp>
#include "abilityComponent.hpp"

class Boomerang : public AbilityComponent {
public:
    Boomerang();
    ~Boomerang();

    void update() override;

    void setDrawableOrigin(Drawable *origin);
private:
    Drawable *originEntity;
};


#endif
