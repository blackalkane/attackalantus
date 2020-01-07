//
// Created by Tim Guo on 2019-10-18.
//

#include <entities/theguy.hpp>
#include <global.hpp>
#include "basicSlash.hpp"

BasicSlash::BasicSlash() {
    basicSlashEntity = nullptr;
    currentTime = 0;
    abilityDuration = 25;
    abilityType = AbilityType::BASIC_SLASH;
    init();
}

BasicSlash::~BasicSlash() = default;


void BasicSlash::setBlinkEntity(Movable *entity) {
    basicSlashEntity = entity;
}

Movable* BasicSlash::getBlinkEntity() {
    return basicSlashEntity;
}

void BasicSlash::start() {
    isActive = true;
    syss->getSoundSystem()->playHitMusic();
    TheGuy* theGuy = dynamic_cast<TheGuy*>(basicSlashEntity);
//    theGuy->setState(GameState::ABILITY);
    DrawComponent* guyDrawComp = theGuy->getDrawComponent();
    char* path = (char*)"../data/textures/characters/CartoonNinja/Attack01/Attack01_0";
    int frame = 32, spriteTime = 4, startIndex = 1, numberOfSprite = 8;
    theGuy->setAbilityAnimation(path, spriteTime, startIndex, numberOfSprite);
    // guyDrawComp->preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    // guyDrawComp->init();
}

void BasicSlash::finish() {
    isActive = false;
    currentTime = 0;

    TheGuy* theGuy = dynamic_cast<TheGuy*>(basicSlashEntity);
//    theGuy->setState(GameState::IDLE);
    DrawComponent* guyDrawComp = theGuy->getDrawComponent();
    char* path = (char*)"../data/textures/characters/CartoonNinja/IdleKatanaPose01/IdleKatanaPose01_0";
    int frame = 8, spriteTime = 2, startIndex = 1, numberOfSprite = 4;
    //theGuy->setAbilityAnimation(path, spriteTime, startIndex, numberOfSprite);
//    guyDrawComp->preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
//    guyDrawComp->init();
}

void BasicSlash::update() {
    if (!isActive){
        return;
    }
}
