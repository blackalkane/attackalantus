#ifndef ATTACKATLANTIS_EXPLOSION_H
#define ATTACKATLANTIS_EXPLOSION_H

#include <entities/entity.hpp>
#include "abilityComponent.hpp"
#include "global.hpp"
#include <entities/bomb.hpp>
#include <systems/abilitySystem.hpp>
#include <systems/drawSystem.hpp>
#include <entities/bombExplosion.hpp>

class Explosion: public AbilityComponent {
public:
    Explosion();
    ~Explosion();

    void update() override;

    void finish() override;

    void setBomb(Bomb* bomb);

private:
    std::vector<BombExplosion*> bombExplosions;
    Bomb* theBomb;
    int timeExplode;
};

#endif //ATTACKATLANTIS_EXPLOSION_H
