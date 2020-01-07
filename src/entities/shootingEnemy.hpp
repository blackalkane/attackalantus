#ifndef ATTACKATLANTIS_SHOOTINGENEMY_H
#define ATTACKATLANTIS_SHOOTINGENEMY_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>

class ShootingEnemy: public Enemy//, public Movable, public Drawable, public Collides
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

    static std::vector<Texture*> S_IDLE_TEXTURES;
    static std::vector<Texture*> S_DEATH_TEXTURES;
    static std::vector<Texture*> S_MOVE_TEXTURES;
    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    HealthComponent healthComp;

    void killSelf() override;

    void resetPosition(Collides* collidedWith) override;

    void preloadTexture() override;
};

#endif //ATTACKATLANTIS_SHOOTINGENEMY_H
