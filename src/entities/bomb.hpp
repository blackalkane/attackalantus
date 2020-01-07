#ifndef ATTACKATLANTIS_BOMB_H
#define ATTACKATLANTIS_BOMB_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/abilityComponent.hpp>

class Bomb: public Drawable, public HasAbility
{
public:

    bool init() override;

    void destroy() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    AbilityComponent* getAbilityComponent() override;

    void preloadTexture() override;

    static std::vector<Texture*> BOMB_TEXTURES;

    static bool newWorld;

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    AbilityComponent* abilityComp;



    void killSelf();
};

#endif //ATTACKATLANTIS_BOMB_H
