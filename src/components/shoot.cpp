//
// Created by Peter Han on 2019-10-20.
//

#include "shoot.hpp"
#include "dropBomb.hpp"
#include <global.hpp>

Shoot::Shoot() {
    projectile = nullptr;
    currentTime = 0;
    abilityDuration = 1;
    abilityType = AbilityType::SHOOT;
    numCharges = 10;
    init();
}

Shoot::~Shoot() {

}

void Shoot::update() {
    float velocity = 10.f;
    if (numCharges < 1) return;

    Projectile *proj = new Projectile();
    proj->init();
    proj->getPositionComponent()->setPosition(curPos);

    if (shootingObject != nullptr) {
        curRotation = shootingObject->getPositionComponent()->getRotation();
        proj->getVelocityComponent()->setVelocity({velocity * cos(curRotation), velocity * sin(curRotation)});
    } else {
        proj->getVelocityComponent()->setVelocity({velocity, 0});
    }
    // TODO add back later
    // world.getProjectiles()->push_back(proj);
//    world.getDrawSystem()->addEntity((Drawable *) proj);
//    world.getMoveSystem()->addEntity((Movable *) proj);
//    world.getCollisionSystem()->addEntity((Collides *) proj);
    syss->getDrawSystem()->addEntity((Drawable *) proj);
    syss->getMoveSystem()->addEntity((Movable *) proj);
    syss->getCollisionSystem()->addEntity((Collides *) proj);
    syss->getSoundSystem()->playProjectileMusic();

    numCharges--;
}

void Shoot::setMousePos(vec2 pos)
{

}

void Shoot::setShootingObject(Drawable *d) {
    shootingObject = d;
}
