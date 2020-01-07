#include "dropBomb.hpp"

DropBomb::DropBomb() {
    oneBomb = nullptr;
    currentTime = 0;
    abilityDuration = 1;
    numCharges = 3;
    abilityType = AbilityType::DROP_BOMB;
    init();
}

DropBomb::~DropBomb() {

}

void DropBomb::update() {
    if (numCharges < 1) return;

    oneBomb = new Bomb();
    oneBomb->getPositionComponent()->setPosition(curPos);
    oneBomb->init();

//    DrawSystem* drawSystem = world.getDrawSystem();
//    AbilitySystem* abilitySystem = world.getAbilitySystem();
//    AllSystem* syss = AllSystem::get_instance();
    DrawSystem* drawSystem = syss->getDrawSystem();
    AbilitySystem* abilitySystem = syss->getAbilitySystem();
    drawSystem->addEntity(oneBomb);
    abilitySystem->addEntity(oneBomb);

    numCharges--;
}

void DropBomb::setMousePos(vec2 pos)
{

}