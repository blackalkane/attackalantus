//
// Created by Andy He on 2019-10-31.
//

#ifndef ATTACKATLANTIS_HASHEALTH_HPP
#define ATTACKATLANTIS_HASHEALTH_HPP


#include <components/healthComponent.hpp>
#include "entity.hpp"

struct HasHealth: public virtual Entity {
virtual HealthComponent* getHealthComponent() = 0;

};


#endif //ATTACKATLANTIS_HASHEALTH_HPP
