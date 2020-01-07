//
// Created by Andy He on 2019-12-05.
//

#ifndef ATTACKATLANTIS_METEOROIDABILITY_HPP
#define ATTACKATLANTIS_METEOROIDABILITY_HPP


#include <entities/drawable.hpp>
#include <entities/meteoroid.hpp>
#include "abilityComponent.hpp"
#include <math.h>

class MeteoroidAbility: public AbilityComponent {
public:
    MeteoroidAbility();
    ~MeteoroidAbility();

    void update() override;

    void start() override;

    void finish() override;

    void setCaster(Drawable* dentity);

private:
    Drawable* caster;
    vec2 cast_position;
    float impact_radius;

    void generateMeteoroid(vec2 position);

    void generateFireParticle(vec2 position);

    bool inImpactRange(float x, float y);
};


#endif //ATTACKATLANTIS_METEOROIDABILITY_HPP
