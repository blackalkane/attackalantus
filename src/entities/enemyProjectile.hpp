//
// Created by Tim Guo on 2019-10-20.
//

#ifndef ATTACKATLANTIS_ENEMYPROJECTILE_HPP
#define ATTACKATLANTIS_ENEMYPROJECTILE_HPP


#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"

class EnemyProjectile: public Drawable, public Movable, public Collides {
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
};


#endif //ATTACKATLANTIS_ENEMYPROJECTILE_HPP
