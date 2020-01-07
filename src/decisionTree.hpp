//
// Created by Andy He on 2019-10-29.
//

#ifndef ATTACKATLANTIS_DECISIONTREE_HPP
#define ATTACKATLANTIS_DECISIONTREE_HPP


#include <entities/entity.hpp>
#include <entities/theguy.hpp>
#include <entities/enemy.hpp>
#include <entities/speedEnemy.hpp>
#include <entities/firePet.hpp>

class DecisionTree {
public:
    static void updateState(GameState* currentState, Entity* entity); // this is the decision tree
private:
    static void theGuyDecisionTree(GameState* currentState, TheGuy* theGuy);
    static void enemyDecisionTree(GameState* currentState, Enemy* enemy);
    static void petDecisionTree(GameState* currentState, FirePet* pet);
};


#endif //ATTACKATLANTIS_DECISIONTREE_HPP
