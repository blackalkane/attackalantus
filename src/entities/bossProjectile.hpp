//
// Created by Tim Guo on 2019-11-08.
//

#ifndef ATTACKATLANTIS_BOSSPROJECTILE_HPP
#define ATTACKATLANTIS_BOSSPROJECTILE_HPP

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"

class BossProjectile: public Drawable, public Movable, public Collides {
public:
    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    static bool newWorld;
private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;

    static std::vector<Texture*> PROJECTILE_TEXTURES;

    void killSelf();

    void stuck();

    float rad;
};


#endif //ATTACKATLANTIS_BOSSPROJECTILE_HPP
