//
// Created by Andy He on 2019-10-04.
//

#ifndef SIMPLEAISYSTEM_H
#define SIMPLEAISYSTEM_H

#include <common.hpp>
#include <entities/movable.hpp>
#include <entities/enemy.hpp>
#include "system.hpp"

class SimpleAISystem: public System{
    public:
        bool init()override;

        void destroy()override;

        void update(float elapsedMs) override;

        // bool removeEntity(Entity* entity)override;

        // bool addEntity(Movable* entity);

        bool setDestPoint(vec2 point);

        bool setVelocity(float v);

        void setEntityVelocity(Movable* entity);

    private:
        float velocity;
        // std::vector<Movable*> entities;
        vec2 destination;
};

#endif //SIMPLEAISYSTEM_H
