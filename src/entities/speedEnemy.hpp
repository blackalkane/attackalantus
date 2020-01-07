#ifndef ATTACKATLANTIS_SPEEDENEMY_H
#define ATTACKATLANTIS_SPEEDENEMY_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>

class SpeedEnemy: public Enemy//, public Movable, public Drawable, public Collides
{
public:

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    VelocityComponent* getVelocityComponent() override;

    HealthComponent* getHealthComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void loadStateSprite() override;

    void preloadTexture() override;

    static std::vector<Texture*> IDLE_TEXTURES;

    static std::vector<Texture*> DEATH_TEXTURES;

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    HealthComponent healthComp;

    void killSelf() override;

    void resetPosition(Collides* collidedWith) override;


};

#endif //ATTACKATLANTIS_SPEEDENEMY_H
