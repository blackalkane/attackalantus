#ifndef ATTACKATLANTIS_MENUITEMS_H
#define ATTACKATLANTIS_MENUITEMS_H

#include "drawable.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>

class MenuItems: public Drawable
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    void preloadTexture() override;

    void setMenuTexture(std::string &path);

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* texture;
};

#endif //ATTACKATLANTIS_HEALTHBAR_H
