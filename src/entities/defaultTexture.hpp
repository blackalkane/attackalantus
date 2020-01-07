#ifndef ATTACKATLANTIS_LEVEL1_H
#define ATTACKATLANTIS_LEVEL1_H

#include "drawable.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>

class DefaultTexture : public Drawable {
public:

    bool init() override;

    void destroy() override;

    DrawComponent *getDrawComponent() override;

    PositionComponent *getPositionComponent() override;

    void preloadTexture() override;

    void setLevelTexture(const std::string &path);

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture *texture;
};

#endif //ATTACKATLANTIS_LEVEL1_H
