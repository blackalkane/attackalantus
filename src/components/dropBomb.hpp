#ifndef ATTACKATLANTIS_DROPBOMB_H
#define ATTACKATLANTIS_DROPBOMB_H

#include <entities/entity.hpp>
#include "abilityComponent.hpp"
#include "global.hpp"
#include <entities/bomb.hpp>
#include <systems/abilitySystem.hpp>
#include <systems/drawSystem.hpp>

class DropBomb: public AbilityComponent {
public:
    DropBomb();
    ~DropBomb();

    void update() override;

    void setMousePos(vec2 pos) override;

private:
    Bomb* oneBomb;
};

#endif //ATTACKATLANTIS_DROPBOMB_H
