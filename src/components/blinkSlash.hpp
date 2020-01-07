//
// Created by Andy He on 2019-10-10.
//

#ifndef ATTACKATLANTIS_BLINKSLASH_HPP
#define ATTACKATLANTIS_BLINKSLASH_HPP


#include <entities/entity.hpp>
#include <entities/movable.hpp>
#include "abilityComponent.hpp"
#include <common.hpp>

class BlinkSlash: public AbilityComponent {
    public:
        BlinkSlash();
        ~BlinkSlash();
        void setBlinkEntity(Movable* entity);

        Movable* getBlinkEntity();

        void start() override;

        void finish() override;

        void update() override;

        void setMousePos(vec2 pos) override;

        bool withinBoundary();

    private:
        Movable* blinkEntity;
        float velocity;
        float vx, vy;
        vec2 originalVelocity;

        vec2 setReturnVelocity(const bool* keyPress, vec2 originV);
};


#endif //ATTACKATLANTIS_BLINKSLASH_HPP
