#ifndef ATTACKATLANTIS_HEALTHBAR_H
#define ATTACKATLANTIS_HEALTHBAR_H

#include "drawable.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>

class HealthBar: public Drawable
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    void preloadTexture() override;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* texture;
};

#endif //ATTACKATLANTIS_HEALTHBAR_H
