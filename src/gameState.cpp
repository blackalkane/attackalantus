//
// Created by Andy He on 2019-10-18.
//

#include "gameState.hpp"


GameState::GameState() {
    previousFrameState = IDLE;
    state = IDLE;
    entityType = -1;
}

GameState::~GameState() {

}

void GameState::setState(int nextState) {
    state = nextState;
}

int GameState::getState() {
    return state;
}

int GameState::getPreFrameState() {
    return previousFrameState;
}

void GameState::frameUpdate() {
    previousFrameState = state;
}

void GameState::setType(int type) {
    entityType = type;
}

////// this is essentially the decision tree method
//void GameState::updateState() {
//    if(entity == nullptr){
//        printf("entity is a nullptr, not doing any decision making");
//        return;
//    }
//    switch(entity->type){
//        case EntityType::THEGUY:
//            break;
//        default:
//            break;
//    }
//}
//
//void GameState::theGuyDecisionTree() {
//    TheGuy* theGuy = dynamic_cast<TheGuy*>(entity);
//    vec2 currentVelocity = theGuy->getVelocityComponent()->getVelocity();
//    switch(state) {
//        case ABILITY:
//            break;
//        case MOVE:
//            if(currentVelocity.x == 0 && currentVelocity.y == 0){
//                state = IDLE;
//            }
//            break;
//        case IDLE:
//            if(currentVelocity.x != 0 || currentVelocity.y != 0){
//                state = MOVE;
//            }
//            break;
//    }
//}
