#ifndef THEGUY_H
#define THEGUY_H

#include "drawable.hpp"
#include "movable.hpp"
#include "collides.hpp"
#include "hasAbility.hpp"
#include "abilityType.hpp"
#include "abilityContainer.hpp"
#include "hasHealth.hpp"
#include "boomerangProjectile.hpp"
#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include <components/healthComponent.hpp>
#include <components/abilityComponent.hpp>
#include <gameState.hpp>


class TheGuy: public Drawable, public Movable, public Collides, public HasAbility, public HasHealth
{
public:

	bool init() override;

	void destroy() override;

    DrawComponent* getDrawComponent() override;

    PositionComponent* getPositionComponent() override;

    VelocityComponent* getVelocityComponent() override;

    HealthComponent* getHealthComponent() override;

    AbilityComponent* getAbilityComponent() override;

    AbilityComponent* setAbilityComponent(AbilityType type);

    AbilityComponent* getBasicAbilityComponent() override;

    bool checkIfAlive();

    void Alive();

    void loadStateSprite()override;

    void setMaxHealth(int h);

    void setMaxCharges(int c);

    void loadAbility() override;

    void setAbilityAnimation(char* path,int spriteT,int startIndex,int numberOfSprite);

    void collideAgainDecrement();

    void speedUp();

    static bool newWorld;

//    vec4 getBoundingBox();

private:
    DrawComponent drawComp;
    PositionComponent positionComp;
    VelocityComponent velocityComp;
    HealthComponent healthComp;
    AbilityComponent* abilityComp;
    AbilityComponent* nextAbility;
    AbilityComponent* basicAbilityComp;
    bool is_alive;
    int max_health;
    int max_charges;

    bool handleCollision(Collides* collidedWith) override;

/*private:
    DrawComponent draw;
    PositionComponent position;
    VelocityComponent velocity;*/

    void resetPosition(Collides* CollidedWith);

    void killTheGuy();

    void obtainAbility(AbilityContainer *pContainer);

    // texture pack
    std::vector<Texture*> idle_textures;
    std::vector<Texture*> move_textures;
    std::vector<Texture*> death_textures;
    std::vector<Texture*> basic_attack_textures;
    std::vector<Texture*> ability_textures;

    int spriteTime;
    int collideAgain;

    void preloadTexture() override;

    void handleBoomerangCollision(BoomerangProjectile *boomerang);
};

#endif
