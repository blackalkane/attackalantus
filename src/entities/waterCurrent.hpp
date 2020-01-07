#ifndef WATERCURRENT_H
#define WATERCURRENT_H

#include "drawable.hpp"
#include "collides.hpp"

class WaterCurrent: public Drawable, public Collides
{
public:

	bool init() override;

	void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    static bool newWorld;

protected:
    DrawComponent drawComp;
    PositionComponent positionComp;
    static std::vector<Texture*> currentTexture;
};

#endif
