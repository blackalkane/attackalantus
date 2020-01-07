//
// Created by Andy He on 2019-12-06.
//

#ifndef ATTACKATLANTIS_FIREPET_HPP
#define ATTACKATLANTIS_FIREPET_HPP


#include "movable.hpp"
#include "drawable.hpp"
#include "collides.hpp"
#include "hasHealth.hpp"

class FirePet: public Movable, public Drawable, public Collides, public HasHealth {
public:
    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

    HealthComponent* getHealthComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void loadStateSprite() override;

    static bool newWorld;
private:
    DrawComponent drawComp;

    void preloadTexture() override;

    static std::vector<Texture*> IDLE_TEXTURES;
    static std::vector<Texture *> DEATH_TEXTURES;
    static std::vector<Texture *> MOVE_TEXTURES;
    VelocityComponent velocityComp;
    PositionComponent positionComp;
    HealthComponent healthComp;
};


#endif //ATTACKATLANTIS_FIREPET_HPP
