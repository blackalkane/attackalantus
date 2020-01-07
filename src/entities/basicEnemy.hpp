#ifndef ATTACKATLANTIS_BASICENEMY_H
#define ATTACKATLANTIS_BASICENEMY_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include "enemy.hpp"
#include "hasAbility.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include <components/onFire.hpp>

class BasicEnemy: public Enemy, public HasAbility //, public Movable, public Drawable, public Collides
{
public:
    static bool newWorld;

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    VelocityComponent* getVelocityComponent() override;

    HealthComponent* getHealthComponent() override;

    AbilityComponent* getAbilityComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void loadStateSprite() override;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    HealthComponent healthComp;
    AbilityComponent* abilityComp;

    static std::vector<Texture*> IDLE_TEXTURES;
    static std::vector<Texture*> DEATH_TEXTURES;
    static std::vector<Texture*> MOVE_TEXTURES;


    void killSelf() override;

    void resetPosition(Collides* collidedWith) override;

    void preloadTexture() override;
};

#endif //ATTACKATLANTIS_BASICENEMY_H
