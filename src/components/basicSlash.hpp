//
// Created by Tim Guo on 2019-10-18.
//

#ifndef ATTACKATLANTIS_BASICSLASH_HPP
#define ATTACKATLANTIS_BASICSLASH_HPP


#include "abilityComponent.hpp"

class BasicSlash: public AbilityComponent {
public:
    BasicSlash();
    ~BasicSlash();

    void setBlinkEntity(Movable *entity);
    Movable *getBlinkEntity();

    void start() override;
    void finish() override;
    void update() override;

private:
    Movable* basicSlashEntity;
};


#endif //ATTACKATLANTIS_BASICSLASH_HPP
