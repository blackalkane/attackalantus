//
// Created by Andy He on 2019-10-10.
//

#include <entities/theguy.hpp>
#include <global.hpp>
#include "blinkSlash.hpp"
#include <entities/abilityType.hpp>

BlinkSlash::BlinkSlash(){
    blinkEntity = nullptr;
    // set to 40 frame for this ability
    currentTime = 0;
    abilityDuration = 40;
    velocity = 15.0;
    vx = velocity;
    vy = 0;
    numCharges = 3;
    abilityType = AbilityType::BLINK_SLASH;
    init();
}

BlinkSlash::~BlinkSlash() {

}

void BlinkSlash::setBlinkEntity(Movable *entity) {
    blinkEntity = entity;
}

Movable* BlinkSlash::getBlinkEntity() {
    return blinkEntity;
}

void BlinkSlash::start() {
    if (numCharges <= 0) return;
    isActive = true;
    syss->getSoundSystem()->playBlinkSlashMusic();

    //set the guy for now, do entity type check later
    TheGuy* theGuy = dynamic_cast<TheGuy*>(blinkEntity);
    // set different animation
//    theGuy->setState(GameState::ABILITY);
    DrawComponent* guyDrawComp = theGuy->getDrawComponent();
    char* path = (char*)"../data/textures/characters/CartoonNinja/Attack02/Attack02_0";
    int frame = 40, spriteTime = 4, startIndex = 10, numberOfSprite = 10;
    theGuy->setAbilityAnimation(path, spriteTime, startIndex, numberOfSprite);
//    guyDrawComp->preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
//    guyDrawComp->init();

    // store original velocity
    originalVelocity = blinkEntity->getVelocityComponent()->getVelocity();

    vec2 entityPosition = blinkEntity->getPositionComponent()->getPosition();

    vec2 length = {mousePos.x - entityPosition.x, mousePos.y - entityPosition.y};

    vec2 ratio = {};

    float manhanttan_distance = abs(length.x) + abs(length.y);
    if (manhanttan_distance == 0.f){
        ratio = {0.5, 0.5};
    }
    else {
        ratio = {abs(length.x) / manhanttan_distance, abs(length.y) / manhanttan_distance};
    }

    if(length.x < 0){
        vx = ratio.x * -velocity;
    }else{
        vx = ratio.x * velocity;
    }

    if(length.y < 0){
        vy = ratio.y * -velocity;
    }else{
        vy = ratio.y * velocity;
    }
}

void BlinkSlash::finish() {
    isActive = false;

    bool* keyPress = syss->getControlSystem()->getKeyPress();
    vec2 afterSlashV = setReturnVelocity(keyPress, originalVelocity);
    blinkEntity->getVelocityComponent()->setVelocity(afterSlashV);

    currentTime = 0;

    //set the guy for now, do entity type check later
    TheGuy* theGuy = dynamic_cast<TheGuy*>(blinkEntity);
//    theGuy->setState(GameState::IDLE);
    // set different animation
    DrawComponent* guyDrawComp = theGuy->getDrawComponent();
    char* path = (char*)"../data/textures/characters/CartoonNinja/IdlePose02/IdlePose02_0";
    int frame = 8, spriteTime = 2, startIndex = 1, numberOfSprite = 4;
    guyDrawComp->preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    guyDrawComp->init();

    numCharges--;
}

void BlinkSlash::update() {
    if (!isActive) {
        return;
    }
    blinkEntity->getVelocityComponent()->setVelocity({vx, vy});
}

void BlinkSlash::setMousePos(vec2 pos) {
    mousePos = pos;
}

vec2 BlinkSlash::setReturnVelocity(const bool* keyPress, vec2 originV) {
    enum {UP, DOWN, LEFT, RIGHT};
    vec2 returnV = {originV.x, originV.y};
    if (originV.x > 0 && !keyPress[RIGHT]){
        returnV.x = 0;
    }
    else if (originV.x < 0 && !keyPress[LEFT]){
        returnV.x = 0;
    }

    if (originV.y > 0 && !keyPress[DOWN]){
        returnV.y = 0;
    }
    else if (originV.y < 0 && !keyPress[UP]){
        returnV.y = 0;
    }
    return returnV;
}