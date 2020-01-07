//
// Created by Andy He on 2019-12-05.
//

#ifndef ATTACKATLANTIS_METEOROID_HPP
#define ATTACKATLANTIS_METEOROID_HPP


#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"

class Meteoroid: public Drawable, Movable, Collides {
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
    static std::vector<Texture*> METEOROID_TEXTURES1;
    static std::vector<Texture*> METEOROID_TEXTURES2;
};


#endif //ATTACKATLANTIS_METEOROID_HPP
