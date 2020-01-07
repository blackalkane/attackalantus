#ifndef ATTACKATLANTIS_BOMBEXPLOSION_HPP
#define ATTACKATLANTIS_BOMBEXPLOSION_HPP

#include "drawable.hpp"
#include "collides.hpp"

class BombExplosion: public Drawable, public Collides
{
public:

    bool init() override;

    void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    static bool newWorld;
private:
    DrawComponent drawComp;
    PositionComponent positionComp;

    static std::vector<Texture*> EXPLOSION_TEXTURES;

};

#endif //ATTACKATLANTIS_BOMBEXPLOSION_HPP
