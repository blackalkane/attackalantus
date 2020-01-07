#ifndef ATTACKATLANTIS_COLLIDES_HPP
#define ATTACKATLANTIS_COLLIDES_HPP

#include <components/positionComponent.hpp>
#include "entity.hpp"

struct Collides : public virtual Entity {
    // TODO
    virtual PositionComponent* getPositionComponent() = 0;

    vec4 getBoundingBox(){
        vec2 curPos = getPositionComponent()->getPosition();
        vec2 size = getPositionComponent()->getSize();
        vec2 positionOffset = getPositionComponent()->getPositionOffset();

        return {curPos.x + positionOffset.x, curPos.y + positionOffset.y, size.x, size.y};
    }

    /**
     * This is to be implemented when a class inherits collides.
     * It will be called for both entities in the pair,
     * so the class should only make changes relevant to itself, without other side effects.
     * Because each entity needs to be active while the other is being checked,
     * returns true if it should
     * @param collidedWith the other entity
     */
    virtual bool handleCollision(Collides* collidedWith) = 0;

    void setPosition(vec2 position) {
        getPositionComponent()->setPosX(position.x);
        getPositionComponent()->setPosY(position.y);
    };

    void setSize(vec2 size) {
        getPositionComponent()->setWidth(size.x);
        getPositionComponent()->setHeight(size.y);
    };
};

#endif //ATTACKATLANTIS_COLLIDES_HPP
