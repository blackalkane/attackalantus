//
// Created by Tim Guo on 2019-11-12.
//

#ifndef ATTACKATLANTIS_BOSSENEMY2_HPP
#define ATTACKATLANTIS_BOSSENEMY2_HPP

#include "enemy.hpp"

class BossEnemy2 : public Enemy {
public:

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

    DrawComponent* getDrawComponent() override;

    HealthComponent* getHealthComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void collideAgainDecrement();

    void loadStateSprite() override;

    static std::vector<Texture*> IDLE_TEXTURES;
    static std::vector<Texture*> DEATH_TEXTURES;
    static std::vector<Texture*> MOVE_TEXTURES;
    static std::vector<Texture*> ABILITY_TEXTURES;
    static bool newWorld;

private:
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    DrawComponent drawComp;
    HealthComponent healthComp;

    void killSelf() override;

    void resetPosition(Collides* collidedWith) override;

    void preloadTexture() override;

    int collideAgain;
};

#endif //ATTACKATLANTIS_BOSSENEMY2_HPP
