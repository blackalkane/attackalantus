#ifndef ATTACKATLANTIS_ABILITYCONTAINER_H
#define ATTACKATLANTIS_ABILITYCONTAINER_H

#include "drawable.hpp"
#include "collides.hpp"
#include "abilityType.hpp"

class AbilityContainer: public Drawable, public Collides {
public:
    explicit AbilityContainer(AbilityType ability);

    void destroy() override;

    bool init() override;

    PositionComponent* getPositionComponent() override;

    DrawComponent* getDrawComponent() override;

    bool handleCollision(Collides* collidedWith) override;

    void preloadTexture() override;

    void setAbilityContain(AbilityType ability);


    AbilityType abilityContained;
    static bool newWorld;
protected:
    DrawComponent drawComp;
    PositionComponent positionComp;

    static std::vector<Texture*> CONTAINER_TEXTURE;
};

#endif