#pragma once

#include "common.hpp"
#include "entities/drawable.hpp"
#include "collides.hpp"


class Menu: public Drawable, public Collides
{
public:
    // Creates all the associated render resources and default transform
    bool init() override;

    // Releases all associated resources
    void destroy() override;

    // Renders the water
    //void draw(const mat3& projection);

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;

//    vec2 getBoundingBox() override;

    void preloadTexture() override;

private:
    Texture*  texture;
    DrawComponent drawComponent;
    PositionComponent positionComponent;
    int max_x;
    int max_y;
};