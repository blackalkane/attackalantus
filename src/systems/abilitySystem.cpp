//
// Created by Andy He on 2019-10-10.
//

#include <entities/hasAbility.hpp>
#include "abilitySystem.hpp"

bool AbilitySystem::init() {
    // assume only have one ability now
    mousePos = {0.f, 0.f};
    curpos = {0.f, 0.f};
    return true;
}

void AbilitySystem::destroy() {
    System::destroy();
}

void AbilitySystem::update(float elapsedMs) {
    for (int i = 0; i < entities.size(); i++) {
        HasAbility *abEntity = dynamic_cast<HasAbility *>(entities[i]);
        AbilityComponent *abilityComp = abEntity->getAbilityComponent();

        if (abilityComp != nullptr && abilityComp->isAbilityActive()) {
            int abilityCurrentTime = abilityComp->getCurrentTime();
            if (abilityCurrentTime < abilityComp->getDuration()) {
                abilityComp->update();
                abilityComp->setCurrentTime(abilityCurrentTime + 1);
            } else {
                abilityComp->finish();
                abEntity->loadAbility();
            }
        }

        //basic ability
        AbilityComponent *basicAbilityComp = abEntity->getBasicAbilityComponent();

        if (basicAbilityComp != nullptr && basicAbilityComp->isAbilityActive()) {
            int abilityCurrentTime = basicAbilityComp->getCurrentTime();
            if (abilityCurrentTime < basicAbilityComp->getDuration()) {
                basicAbilityComp->update();
                basicAbilityComp->setCurrentTime(abilityCurrentTime + 1);
            } else {
                basicAbilityComp->finish();
                abEntity->loadAbility();
            }
        }
    }
}

bool AbilitySystem::removeEntity(Entity *entity) {
    if (System::removeEntity(entity)) {
        HasAbility *abEntity = dynamic_cast<HasAbility *>(entity);
        abEntity->getAbilityComponent()->finish();
        return true;
    } else {
        return false;
    }
}

void AbilitySystem::setMousePos(vec2 pos) {
    mousePos = pos;
}

void AbilitySystem::setPos(vec2 pos) {
    curpos = pos;
}