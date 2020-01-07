//
// Created by Andy He on 2019-12-05.
//

#ifndef ATTACKATLANTIS_PORK_HPP
#define ATTACKATLANTIS_PORK_HPP

#include "drawable.hpp"
#include "collides.hpp"

class Pork: public Drawable, public Collides
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    static std::vector<Texture*> PORK_TEXTURES;
    static Texture* PORK_TEXTURE;
};

#endif //ATTACKATLANTIS_PORK_HPP
