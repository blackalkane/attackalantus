#ifndef PROJECTLE_H
#define PROJECTLE_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include <components/abilityComponent.hpp>


class Projectile: public Drawable, public Movable, public Collides
{
public:
    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

    AbilityComponent* getAbilityComponent();

    bool handleCollision(Collides* collidedWith) override;

    static bool newWorld;
private:

    void killSelf();

protected:
    DrawComponent drawComp;

    void preloadTexture() override;

    static std::vector<Texture*> IDLE_TEXTURES;
    VelocityComponent velocityComp;
    PositionComponent positionComp;
    AbilityComponent* abilityComp;
};

#endif
