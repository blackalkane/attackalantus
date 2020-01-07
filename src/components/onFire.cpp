//
// Created by Andy He on 2019-12-05.
//
 #include <global.hpp>
#include "onFire.hpp"

OnFire::OnFire() {
    onFireEntity = nullptr;
    currentTime = 0;
    abilityDuration = 50;
    init();
}

OnFire::~OnFire() {

}

void OnFire::setFireEntity(Drawable *fEntity) {
    onFireEntity = fEntity;
}

void OnFire::update() {
    if (currentTime % 10 != 0) {
        return;
    }
    if(onFireEntity == nullptr) {
        return;
    }
    Particle* p = new Particle();
    p->init();
    vec2 position = onFireEntity->getPositionComponent()->getPosition();
    position.y -= 20.f; // magic number hack
    // position set twice for random direction
//    p->getPositionComponent()->setPosition(position);
    p->getPositionComponent()->setPosition(position);
    syss->getDrawSystem()->addEntity(p);
    syss->getDeleteSystem()->addEntity(p);
    syss->getDynamicEnitityStoreSystem()->addEntity(p);
}

void OnFire::finish() {
    if(isActive) {
        AbilityComponent::finish();
        Enemy *enemy = dynamic_cast<Enemy *>(onFireEntity);
        vec2 death_pos = enemy->getPositionComponent()->getPosition();
        syss->removeEntityFromSystems(enemy);
        enemy->getHealthComponent()->dead();
        syss->getDeleteSystem()->addEntity(enemy);
        syss->getDrawSystem()->addEntity(enemy);

        Pork *pork = new Pork;
        pork->init();
        pork->getPositionComponent()->setPosition(death_pos);
        syss->getDrawSystem()->addEntity(pork);
        syss->getCollisionSystem()->addEntity(pork);
//        syss->getDynamicEnitityStoreSystem()->addEntity(pork);
    }

}
