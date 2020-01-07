#ifndef ROCK_H
#define ROCK_H

#include "drawable.hpp"
#include "collides.hpp"

class Rock: public Drawable, public Collides
{
public:

	bool init() override;

	void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    Texture* rockTexture;
    Texture* rock2Texture;
};

#endif
