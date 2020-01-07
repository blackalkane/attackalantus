//
// Created by Andy He on 2019-10-29.
//


#include "decisionTree.hpp"

void DecisionTree::updateState(GameState* currentState, Entity *entity) {
    if(entity == nullptr){
        printf("entity is a nullptr, not doing any decision making");
        return;
    }
    if(currentState == nullptr){
        return;
    }
    switch(entity->type){
        case EntityType::THEGUY:
            theGuyDecisionTree(currentState, dynamic_cast<TheGuy*>(entity));
            break;
        case EntityType::ENEMY:
            enemyDecisionTree(currentState, dynamic_cast<Enemy*>(entity));
            break;
        case EntityType::PET:
            petDecisionTree(currentState, dynamic_cast<FirePet*>(entity));
            break;
        default:
            break;
    }
}

void DecisionTree::theGuyDecisionTree(GameState* currentState, TheGuy *theGuy) {
    if(theGuy == NULL){
        return;
    }
    vec2 currentVelocity = theGuy->getVelocityComponent()->getVelocity();
    bool abilityActive = theGuy->getAbilityComponent()->isAbilityActive() || theGuy->getBasicAbilityComponent()->isAbilityActive();
    if(theGuy->getAbilityComponent()->isAbilityActive() && theGuy->getAbilityComponent()->getAbilityType() == AbilityType::METEOROID) {
        abilityActive = false;
    }
    bool alive = theGuy->getHealthComponent()->isAlive();
    if(!alive) {
        currentState->setState(GameState::DEATH);
        return;
    }
    if(abilityActive){
        currentState->setState(GameState::ABILITY);
        return;
    }
    switch(currentState->getState()) {
        case GameState::ABILITY:
            if (!abilityActive) {
                if(currentVelocity.x == 0 && currentVelocity.y == 0){
                    currentState->setState(GameState::IDLE);
                }
                else {
                    currentState->setState(GameState::MOVE);
                }
            }
            break;
        case GameState::MOVE:
            if(currentVelocity.x == 0 && currentVelocity.y == 0){
                currentState->setState(GameState::IDLE);
            }
            break;
        case GameState::IDLE:
            if(currentVelocity.x != 0 || currentVelocity.y != 0){
                currentState->setState(GameState::MOVE);
            }
            break;
    }
}

void DecisionTree::enemyDecisionTree(GameState *currentState, Enemy *enemy) {
//////// maybe it is useful for the future
//    if(enemy->getEnemyType() == EnemyType::SPEED) {
//        SpeedEnemy* senemy = dynamic_cast<SpeedEnemy*>(enemy);
//        bool alive = senemy->getHealthComponent()->isAlive();
//        if(!alive) {
//            currentState->setState(GameState::DEATH);
//            return;
//        }
//
//        switch(currentState->getState()){
//            case GameState::IDLE:
//            case GameState::MOVE:
//            case GameState::DEATH:
//                break;
//            default:
//                break;
//        }
//    }

    bool alive = enemy->getHealthComponent()->isAlive();
    bool abilityActive = enemy->getCurrentState() == GameState::ABILITY;
    if(!alive) {
        currentState->setState(GameState::DEATH);
        return;
    }
    if(abilityActive){
        currentState->setState(GameState::ABILITY);
        return;
    }

    vec2 currentVelocity = enemy->getVelocityComponent()->getVelocity();

    switch(currentState->getState()){
        case GameState::ABILITY:
            if (!abilityActive) {
                if(currentVelocity.x == 0 && currentVelocity.y == 0){
                    currentState->setState(GameState::IDLE);
                }
                else {
                    currentState->setState(GameState::MOVE);
                }
            }
            break;
        case GameState::IDLE:
            if(currentVelocity.x != 0 || currentVelocity.y != 0){
                currentState->setState(GameState::MOVE);
            }
            break;
        case GameState::MOVE:
            if(currentVelocity.x == 0 && currentVelocity.y == 0){
                currentState->setState(GameState::IDLE);
            }
            break;
        case GameState::DEATH:
            break;
        default:
            break;
    }

}

void DecisionTree::petDecisionTree(GameState *currentState, FirePet *pet) {
    bool alive = pet->getHealthComponent()->isAlive();
    bool abilityActive = pet->getCurrentState() == GameState::ABILITY;
    if(!alive) {
        currentState->setState(GameState::DEATH);
        return;
    }
    if(abilityActive){
        currentState->setState(GameState::ABILITY);
        return;
    }

    vec2 currentVelocity = pet->getVelocityComponent()->getVelocity();

    switch(currentState->getState()){
        case GameState::ABILITY:
            if (!abilityActive) {
                if(currentVelocity.x == 0 && currentVelocity.y == 0){
                    currentState->setState(GameState::IDLE);
                }
                else {
                    currentState->setState(GameState::MOVE);
                }
            }
            break;
        case GameState::IDLE:
            if(currentVelocity.x != 0 || currentVelocity.y != 0){
                currentState->setState(GameState::MOVE);
            }
            break;
        case GameState::MOVE:
            if(currentVelocity.x == 0 && currentVelocity.y == 0){
                currentState->setState(GameState::IDLE);
            }
            break;
        case GameState::DEATH:
            break;
        default:
            break;
    }


}


