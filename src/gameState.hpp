//
// Created by Andy He on 2019-10-18.
//

#ifndef ATTACKATLANTIS_GAMESTATE_HPP
#define ATTACKATLANTIS_GAMESTATE_HPP


#include "common.hpp"

class GameState {
    public:
        enum {IDLE, MOVE, ABILITY, DEATH};
        GameState();
        ~GameState();
        void setState(int nextState);
        int getState();
        int getPreFrameState();
        void frameUpdate();
        void setType(int type);
//        void updateState(); // this is the decision tree
    private:
        int state;
        int previousFrameState;
        int entityType;

//        void theGuyDecisionTree();
};


#endif //ATTACKATLANTIS_GAMESTATE_HPP
