//
// Created by Andy He on 2019-12-01.
//

#ifndef ATTACKATLANTIS_DYNAMICENTITYSTORESYSTEM_HPP
#define ATTACKATLANTIS_DYNAMICENTITYSTORESYSTEM_HPP


#include "system.hpp"

class DynamicEntityStoreSystem: public System {
public:

    // init a System
    bool init() override;

    void destroy() override;

    void update(float elapsedMs) override;

    bool removeEntity(Entity* entity) override;

};


#endif //ATTACKATLANTIS_DYNAMICENTITYSTORESYSTEM_HPP
