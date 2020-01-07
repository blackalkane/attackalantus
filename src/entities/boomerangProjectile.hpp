#ifndef ATTACKALANTIS_BOOMERANG_PROJECTILE_H
#define ATTACKALANTIS_BOOMERANG_PROJECTILE_H

#include "projectile.hpp"

class BoomerangProjectile: public Projectile
{
public:
    bool init() override;

    void destroy() override;

    void setInitialDirection(vec2 initialDir);

    bool handleCollision(Collides* collidedWith) override;

    vec2 getUpdatedVelocity();

    bool isGoingBackwards();

    static bool newWorldBoomerang;

private:
    void preloadTexture() override;
    const float VELOCITY_DECREASE_FACTOR = 0.98f;
    const float VELOCITY_INCREASE_FACTOR = 0.02f;
    const float REVERSAL_THRESHOLD = 1.f;
    vec2 initialDirection;
    bool goingBackwards = false;

    bool shouldReverse(const vec2 &currVelocity);

    static std::vector<Texture *> BOOMER_IDLE_TEXTURES;
};

#endif