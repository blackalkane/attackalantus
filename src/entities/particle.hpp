//
// Created by Andy He on 2019-12-01.
//

#ifndef ATTACKATLANTIS_PARTICLE_HPP
#define ATTACKATLANTIS_PARTICLE_HPP


#include "drawable.hpp"
#include "movable.hpp"

class Particle: public Drawable, Movable
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

//    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    void setStartPosition(vec2 position);

    vec2 getStartPosition();

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    static std::vector<Texture*> PARTICLE_TEXTURES1;
    static std::vector<Texture*> PARTICLE_TEXTURES2;
    vec2 startPosition;
};


#endif //ATTACKATLANTIS_PARTICLE_HPP
