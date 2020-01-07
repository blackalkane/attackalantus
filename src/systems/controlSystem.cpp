
#include <entities/hasAbility.hpp>
#include <entities/drawable.hpp>
#include <decisionTree.hpp>
#include "controlSystem.hpp"

ControlSystem::ControlSystem() {
    init();
}

ControlSystem::~ControlSystem() {
    destroy();
}

bool ControlSystem::init() {
    destroy();
    velocity = 5.f;
    isKeyPressed = new bool[4];
    stopMoving();
    return true;
}

void ControlSystem::destroy() {
    System::destroy();
    if (isKeyPressed == nullptr){
        return;
    }
    delete[](isKeyPressed);
    isKeyPressed = nullptr;
}

void ControlSystem::setMousePos(vec2 pos){
    mousePos = pos;
}

void ControlSystem::setPos(vec2 pos) {
    curpos = pos;
}

void ControlSystem::update(float elapsedMs) {

}

void ControlSystem::setKeyEffect(int key, int action){

    for (Entity* controlObj : entities) {

        Movable *movableControlObj = dynamic_cast<Movable *>(controlObj);
        // assume moveable is also drawable, but not the other way around
        Drawable* drawControlObj = dynamic_cast<Drawable *>(movableControlObj);

        if (action == GLFW_RELEASE && key == GLFW_KEY_W) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            float y = movableControlObj->getVelocityComponent()->getVY();
            isKeyPressed[UP] = false;
            if (isKeyPressed[DOWN]) {
                movableControlObj->getVelocityComponent()->setVelocity({x, velocity});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::MOVE);
//                }
            } else {
                movableControlObj->getVelocityComponent()->setVelocity({x, 0.0});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::IDLE);
//                }
            }
        }
        if (action == GLFW_RELEASE && key == GLFW_KEY_S) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            float y = movableControlObj->getVelocityComponent()->getVY();
            isKeyPressed[DOWN] = false;
            if (isKeyPressed[UP]) {
                movableControlObj->getVelocityComponent()->setVelocity({x, -velocity});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::MOVE);
//                }
            } else {
                movableControlObj->getVelocityComponent()->setVelocity({x, 0.0});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::IDLE);
//                }
            }
        }
        if (action == GLFW_RELEASE && key == GLFW_KEY_A) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            float y = movableControlObj->getVelocityComponent()->getVY();
            isKeyPressed[LEFT] = false;
            if (isKeyPressed[RIGHT]) {
                movableControlObj->getVelocityComponent()->setVelocity({velocity, y});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::MOVE);
//                }
            } else {
                movableControlObj->getVelocityComponent()->setVelocity({0.0, y});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::IDLE);
//                }
            }


        }
        if (action == GLFW_RELEASE && key == GLFW_KEY_D) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            float y = movableControlObj->getVelocityComponent()->getVY();
            isKeyPressed[RIGHT] = false;
            if (isKeyPressed[LEFT]) {
                movableControlObj->getVelocityComponent()->setVelocity({-velocity, y});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::MOVE);
//                }
            } else {
                movableControlObj->getVelocityComponent()->setVelocity({0, y});
//                if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                    drawControlObj->setState(GameState::IDLE);
//                }
            }
        }

        if (action == GLFW_PRESS && key == GLFW_KEY_W) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            movableControlObj->getVelocityComponent()->setVelocity({x, -velocity});
            isKeyPressed[UP] = true;
//            if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                drawControlObj->setState(GameState::MOVE);
//            }
        }
        if (action == GLFW_PRESS && key == GLFW_KEY_S) {
            float x = movableControlObj->getVelocityComponent()->getVX();
            movableControlObj->getVelocityComponent()->setVelocity({x, velocity});
            isKeyPressed[DOWN] = true;
//            if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                drawControlObj->setState(GameState::MOVE);
//            }
        }
        if (action == GLFW_PRESS && key == GLFW_KEY_A) {
            float y = movableControlObj->getVelocityComponent()->getVY();
            movableControlObj->getVelocityComponent()->setVelocity({-velocity, y});
            isKeyPressed[LEFT] = true;
//            if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                drawControlObj->setState(GameState::MOVE);
//            }
        }
        if (action == GLFW_PRESS && key == GLFW_KEY_D) {
            float y = movableControlObj->getVelocityComponent()->getVY();
            movableControlObj->getVelocityComponent()->setVelocity({velocity, y});
            isKeyPressed[RIGHT] = true;
//            if(drawControlObj->getCurrentState() != GameState::ABILITY){
//                drawControlObj->setState(GameState::MOVE);
//            }
        }

        if (action == GLFW_PRESS && key == GLFW_KEY_Q) {
//            HasAbility* abilityEntity = dynamic_cast<HasAbility*>(controlObj);
//            if(!isAbilitiesActive(abilityEntity)) {
//                abilityEntity->getAbilityComponent()->setMousePos(mousePos);
//                abilityEntity->getAbilityComponent()->setPos(curpos);
//                abilityEntity->getAbilityComponent()->start();
//            }
        }
        if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) {
//            HasAbility* abilityEntity = dynamic_cast<HasAbility*>(controlObj);
//            if(!isAbilitiesActive(abilityEntity)) {
//                abilityEntity->getBasicAbilityComponent()->setMousePos(mousePos);
//                abilityEntity->getBasicAbilityComponent()->setPos(curpos);
//                abilityEntity->getBasicAbilityComponent()->start();
//            }
        }
    }
}

void ControlSystem::setMouseButtonEffect(int button, int action) {
    for (Entity* controlObj : entities) {
        if (action ==  GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
            HasAbility* abilityEntity = dynamic_cast<HasAbility*>(controlObj);
            if(!isAbilitiesActive(abilityEntity)) {
                abilityEntity->getAbilityComponent()->setMousePos(mousePos);
                abilityEntity->getAbilityComponent()->setPos(curpos);
                abilityEntity->getAbilityComponent()->start();
            }
        }
        if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
            HasAbility* abilityEntity = dynamic_cast<HasAbility*>(controlObj);
            if(!isAbilitiesActive(abilityEntity)) {
                abilityEntity->getBasicAbilityComponent()->setMousePos(mousePos);
                abilityEntity->getBasicAbilityComponent()->setPos(curpos);
                abilityEntity->getBasicAbilityComponent()->start();
            }
        }
    }
}

void ControlSystem::setVelocity(float v) {
    velocity = v;
}

bool ControlSystem::checkIsControl(Entity *controlObj) {
    for(Entity* entity : entities){
        if(entity == controlObj) {
            return true;
        }
    }
    return false;
}

bool* ControlSystem::getKeyPress() {
    return isKeyPressed;
}

bool ControlSystem::isAbilitiesActive(HasAbility* abilityEntity) {
    AbilityComponent* basic = abilityEntity->getBasicAbilityComponent();
    AbilityComponent* ability = abilityEntity->getAbilityComponent();
    if(basic == nullptr){
        return ability->isAbilityActive();
    }
    else { // baisc is true
        return basic->isAbilityActive() || ability->isAbilityActive();
    }
}

void ControlSystem::stopMoving() {
    for (int i = 0; i < 4; i++) {
        isKeyPressed[i] = false;
    }
    for (Entity* controlObj : entities) {
        Movable *movableControlObj = dynamic_cast<Movable *>(controlObj);

        movableControlObj->getVelocityComponent()->setVelocity({ 0, 0 });
    }
}


