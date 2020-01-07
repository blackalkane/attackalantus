#pragma once

#include "common.hpp"
#include "entities/drawable.hpp"
#include "collides.hpp"


class Environment: public Drawable, public Collides
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

    void preloadTexture() override;

    void setTexturePath(char* path);

//    vec2 getBoundingBox() override;

private:
    Texture*  environment_texture;
    DrawComponent drawComponent;
    PositionComponent positionComponent;
    int max_x;
    int max_y;
    std::string backgroundPath;
};