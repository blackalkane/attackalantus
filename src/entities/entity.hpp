#ifndef ENTITY_H
#define ENTITY_H

#include <components/gcomponent.hpp>
#include <components/componentType.hpp>
#include <cstdint>
#include <unordered_set>
#include <gameState.hpp>
#include "entityType.hpp"

struct Entity {

    virtual bool init() = 0;

    // Releases all associated resources
    virtual void destroy() = 0;

    std::uint32_t getId() const {
        return m_id;
    }

    bool isActivated() const {
        return m_is_active;
    }

    // Activate this entity
    // returns true if successfully activated
    bool activate() {
        m_is_active = true;
        return true;
    }

    // Deactivate this entity
    // returns true if successfully deactivated
    bool deactivate() {
        m_is_active = false;
        return false;
    };

    // Get the component of the given type attached to this entity.
    // Returns a pointer to that component.
    GComponent* getComponent(ComponentType type) {
        // TODO
        return nullptr;
    }

    // Returns true if there is a component of type T attached to this entity.
    bool hasComponent() {
        // TODO
        return false;
    };

    void setType(EntityType t) {
        type = t;
    }

    std::uint32_t m_id;
    bool m_is_active;
    EntityType type;
};

#endif