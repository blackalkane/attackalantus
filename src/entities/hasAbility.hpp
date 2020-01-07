#ifndef ATTACKATLANTIS_HASABILITY_HPP
#define ATTACKATLANTIS_HASABILITY_HPP

#include <components/abilityComponent.hpp>
#include "entity.hpp"

struct HasAbility: public virtual Entity{
    virtual AbilityComponent* getAbilityComponent() = 0;

    virtual AbilityComponent* getBasicAbilityComponent() {
        // no basic ability
        return nullptr;
    }

    virtual void loadAbility() {
    }
};

#endif //ATTACKATLANTIS_HASABILITY_HPP
