//
// Created by Andy He on 2019-12-06.
//

#ifndef ATTACKATLANTIS_FIRELITTLEPARTICLE_HPP
#define ATTACKATLANTIS_FIRELITTLEPARTICLE_HPP


#include "drawable.hpp"
#include "movable.hpp"

class FireLittleParticle: public Drawable, Movable {
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

    void setDirection(int dir);

    int getDirection();

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    static std::vector<Texture*> FIRE_PARTICLE_TEXTURES;
    vec2 startPosition;
    int direction;
};


#endif //ATTACKATLANTIS_FIRELITTLEPARTICLE_HPP
