//
// Created by Peter Han on 2019-11-28.
//

#ifndef ATTACKATLANTIS_CASTLE_HPP
#define ATTACKATLANTIS_CASTLE_HPP


#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include "collides.hpp"

class Castle :public Collides{
public:

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;


private:
    PositionComponent positionComp;
    Texture* rockTexture;
    Texture* rock2Texture;
};


#endif //ATTACKATLANTIS_CASTLE_HPP
