//
// Created by Andy He on 2019-10-16.
//

#ifndef ATTACKATLANTIS_DELETESYSTEM_HPP
#define ATTACKATLANTIS_DELETESYSTEM_HPP


#include "system.hpp"

class DeleteSystem: public System {
public:
    DeleteSystem();
    ~DeleteSystem();

    // init a System
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    void setWinningDeleteCounter(int v);

    void setDefeatDeleteCounter(int v);

    int getWinningDeleteCounter();

    int getDefeatDeleteCounter();

private:
    int winningDeleteCounter;
    int defeatDeleteCounter;
};


#endif //ATTACKATLANTIS_DELETESYSTEM_HPP
