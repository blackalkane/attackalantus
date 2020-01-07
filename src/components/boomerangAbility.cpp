#include <global.hpp>
#include "boomerangAbility.hpp"

Boomerang::Boomerang() {
    currentTime = 0;
    abilityDuration = 1;
    abilityType = AbilityType::BOOMERANG;
    numCharges = 3;
    syss->getSoundSystem()->playBoomerangMusic();
    init();
}

void Boomerang::update() {
    float velocity = 15.f;
    if (numCharges < 1) return;

    auto *proj = new BoomerangProjectile();
    proj->init();
    proj->getPositionComponent()->setPosition(curPos);

    if (originEntity != nullptr) {
        curRotation = originEntity->getPositionComponent()->getRotation();
        proj->setInitialDirection({ cos(curRotation), sin(curRotation) });
        proj->getVelocityComponent()->setVelocity({velocity * cos(curRotation),
                                                   velocity * sin(curRotation) });
    } else {
        proj->getVelocityComponent()->setVelocity({velocity, 0});
    }
    syss->getDrawSystem()->addEntity((Drawable *) proj);
    syss->getMoveSystem()->addEntity((Movable *) proj);
    syss->getCollisionSystem()->addEntity((Collides *) proj);
    syss->getSoundSystem()->playProjectileMusic();

    numCharges--;
}

void Boomerang::setDrawableOrigin(Drawable *origin) {
    originEntity = origin;
}

Boomerang::~Boomerang() = default;


