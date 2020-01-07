#ifndef ATTACKATLANTIS_SLASH_H
#define ATTACKATLANTIS_SLASH_H

#include "drawable.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>

class Slash: public Drawable
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

#endif //ATTACKATLANTIS_SLASH_H
