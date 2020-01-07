//
// Created by Andy He on 2019-10-10.
//

#ifndef ATTACKATLANTIS_ABILITYSYSTEM_HPP
#define ATTACKATLANTIS_ABILITYSYSTEM_HPP


#include <common.hpp>
#include <map>
#include "system.hpp"

class AbilitySystem: public System {
public:
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    bool removeEntity(Entity* entity) override;

    void setMousePos(vec2 pos);

    void setPos(vec2 pos);

private:
    vec2 mousePos;
    vec2 curpos;

};


#endif //ATTACKATLANTIS_ABILITYSYSTEM_HPP
