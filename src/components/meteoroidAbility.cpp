//
// Created by Andy He on 2019-12-05.
//

#include <global.hpp>
#include <entities/fireLittleParticle.hpp>
#include <entities/firePet.hpp>
#include "meteoroidAbility.hpp"

MeteoroidAbility::MeteoroidAbility() {
    caster = nullptr;
    currentTime = 0;
    abilityDuration = 160;
    impact_radius = 30.0;
    cast_position = {-100.0, -100.0};
    numCharges = 1;
    abilityType = AbilityType::METEOROID;
    init();
}

MeteoroidAbility::~MeteoroidAbility() {

}

void MeteoroidAbility::update() {
    if (currentTime % 8 != 0) {
        return;
    }
    vec2 position = cast_position;
    float off_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / impact_radius));
    float off_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / impact_radius));
    int position_choice = rand() % 3;
    int x_sign = rand() % 2;
    int y_sign = rand() % 2;
    if (!inImpactRange(off_x, off_y)) {
        if (position_choice == 0) {
            off_x = 0;
            off_y = 0;
        } else if (position_choice == 1) {
            off_y = sqrt((impact_radius * impact_radius) - (off_x * off_x));
        } else { // position_choice == 2
            off_x = sqrt((impact_radius * impact_radius) - (off_y * off_y));
        }
    }
    if (x_sign) {
        off_x = -off_x;
    }
    if (y_sign) {
        off_y = -off_y;
    }

    position = {position.x + off_x, position.y + off_y};

    if (currentTime > 10) {
        generateFireParticle(position);
    }
    generateMeteoroid(position);

    if (currentTime % 16 == 0) {
        FirePet* firePet = new FirePet();
        firePet->init();
        firePet->getPositionComponent()->setPosition(position);
        syss->getDrawSystem()->addEntity(firePet);
        syss->getPetRouteSystem()->addEntity(firePet);
        syss->getMoveSystem()->addEntity(firePet);
        syss->getCollisionSystem()->addEntity(firePet);
//        syss->getDeleteSystem()->addEntity(firePet);
        syss->getDynamicEnitityStoreSystem()->addEntity(firePet);
    }
}

void MeteoroidAbility::setCaster(Drawable* dentity) {
    caster = dentity;
}

void MeteoroidAbility::start() {
    if (numCharges <= 0){
        return;
    }
    syss->getSoundSystem()->playMeteorMusic();
    AbilityComponent::start();
    cast_position = caster->getPositionComponent()->getPosition();
}

bool MeteoroidAbility::inImpactRange(float x, float y) {
    return (x * x) + (y * y) <= impact_radius * impact_radius;
}

void MeteoroidAbility::generateMeteoroid(vec2 position) {
    Meteoroid* meteoroid = new Meteoroid();
    meteoroid->init();
    meteoroid->getPositionComponent()->setPosition(position);
    syss->getDrawSystem()->addEntity(meteoroid);
    syss->getCollisionSystem()->addEntity(meteoroid);
    syss->getDeleteSystem()->addEntity(meteoroid);
    syss->getDynamicEnitityStoreSystem()->addEntity(meteoroid);

}

void MeteoroidAbility::generateFireParticle(vec2 position) {
    FireLittleParticle* fireParticle = new FireLittleParticle();
    fireParticle->init();
    fireParticle->setStartPosition(position);
    fireParticle->setDirection(0);
    syss->getParticleEffectSystem()->addEntity(fireParticle);
    syss->getDrawSystem()->addEntity(fireParticle);
    syss->getDeleteSystem()->addEntity(fireParticle);
    syss->getDynamicEnitityStoreSystem()->addEntity(fireParticle);

    FireLittleParticle* fireParticle2 = new FireLittleParticle();
    fireParticle2->init();
    fireParticle2->setStartPosition(position);
    fireParticle2->setDirection(1);
    syss->getParticleEffectSystem()->addEntity(fireParticle2);
    syss->getDrawSystem()->addEntity(fireParticle2);
    syss->getDeleteSystem()->addEntity(fireParticle2);
    syss->getDynamicEnitityStoreSystem()->addEntity(fireParticle2);
}

void MeteoroidAbility::finish() {
    AbilityComponent::finish();
    numCharges--;
}
