#ifndef ATTACKATLANTIS_GUN_H
#define ATTACKATLANTIS_GUN_H

#include "drawable.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>

class Gun: public Drawable
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

#endif //ATTACKATLANTIS_GUN_H
