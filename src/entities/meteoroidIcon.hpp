//
// Created by Peter Han on 2019-12-06.
//

#ifndef ATTACKATLANTIS_METEOROIDICON_HPP
#define ATTACKATLANTIS_METEOROIDICON_HPP


#include <components/positionComponent.hpp>
#include <components/drawComponent.hpp>
#include "drawable.hpp"

class MeteoroidIcon: public Drawable {
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


#endif //ATTACKATLANTIS_METEOROIDICON_HPP
