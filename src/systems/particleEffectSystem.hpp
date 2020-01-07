//
// Created by Andy He on 2019-12-06.
//

#ifndef ATTACKATLANTIS_PARTICLEEFFECTSYSTEM_HPP
#define ATTACKATLANTIS_PARTICLEEFFECTSYSTEM_HPP


#include "system.hpp"
#include <entities/particle.hpp>
#include <entities/fireLittleParticle.hpp>

class ParticleEffectSystem: public System {
public:
    void update(float elapsedMs) override;

private:

};


#endif //ATTACKATLANTIS_PARTICLEEFFECTSYSTEM_HPP
