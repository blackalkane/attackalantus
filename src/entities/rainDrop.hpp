//
// Created by Andy He on 2019-12-05.
//

#ifndef ATTACKATLANTIS_RAINDROP_HPP
#define ATTACKATLANTIS_RAINDROP_HPP

#include "drawable.hpp"
#include "movable.hpp"

class RainDrop: public Drawable, Movable
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

//    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    static std::vector<Texture*> RAINDROP_TEXTURES1;
    static std::vector<Texture*> RAINDROP_TEXTURES2;
};


#endif //ATTACKATLANTIS_RAINDROP_HPP
