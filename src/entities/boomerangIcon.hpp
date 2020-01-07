#ifndef ATTACKATLANTIS_BOOMERANGICON_H
#define ATTACKATLANTIS_BOOMERANGICON_H

#include "drawable.hpp"

class BoomerangIcon: public Drawable
{
public:

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    void preloadTexture() override;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* texture;

};

#endif