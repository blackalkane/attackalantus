#include <global.hpp>
#include <components/blinkSlash.hpp>
#include <components/dropBomb.hpp>
#include <components/basicSlash.hpp>
#include <components/shoot.hpp>
#include <components/boomerangAbility.hpp>
#include <components/meteoroidAbility.hpp>
#include "theguy.hpp"

bool TheGuy::newWorld = true;

bool TheGuy::init() {
    // init draw component
    drawComp.fragmentShaderPath = shader_path("theguy.fs.glsl");
    drawComp.vertexShaderPath = shader_path("theguy.vs.glsl");
    int frame, startIndex = 1, numOfSprite = 4;
    spriteTime = 4;
    frame = spriteTime * numOfSprite;
    preloadTexture();
    drawComp.setStaticTexture(nullptr);
    drawComp.setNewAnimation(idle_textures, frame, spriteTime);
    drawComp.init();
    vec2 scale = {2.0, 2.0};
    drawComp.setScale(scale);

    // init health component
    healthComp.init();
    healthComp.setHealth(max_health);

    //init velocity and position component
    velocityComp.init();
    positionComp.init();
    positionComp.setPosition({100.f, 100.f});

    Texture *texture = drawComp.texture;
    // the guy is smaller than the texture, so manually set the scale of the hit box
    positionComp.setWidth(texture->width * 0.6);
    positionComp.setHeight(texture->height * 0.6);

    type = EntityType::THEGUY;

    BlinkSlash *ability = new BlinkSlash();
    ability->setBlinkEntity((Movable *) this);

    BasicSlash *basicAbility = new BasicSlash();
    basicAbility->setBlinkEntity((Movable *) this);

    abilityComp = ability;
    basicAbilityComp = basicAbility;
    nextAbility = nullptr;

    is_alive = true;

    collideAgain = 0;

    //set to the idle state
    entityState.setState(GameState::IDLE);

    return true;
}


void TheGuy::destroy() {
    drawComp.destroy();
    positionComp.destroy();
    velocityComp.destroy();
    healthComp.destroy();
    free(abilityComp);
    abilityComp = nullptr;

    for (Texture *t : idle_textures) {
        free(t);
    }
    idle_textures.clear();
    for (Texture *t : move_textures) {
        free(t);
    }
    move_textures.clear();
    for (Texture *t : death_textures) {
        free(t);
    }
    death_textures.clear();
    for (Texture *t : basic_attack_textures) {
        free(t);
    }
    basic_attack_textures.clear();
    for (Texture *t : ability_textures) {
        free(t);
    }
    ability_textures.clear();
//    for(Texture* t : idle_textures) {
//        free(t);
//    }
//    idle_textures.clear();
}

DrawComponent *TheGuy::getDrawComponent() {
    return &drawComp;
}

PositionComponent *TheGuy::getPositionComponent() {
    return &positionComp;
}

VelocityComponent *TheGuy::getVelocityComponent() {
    return &velocityComp;
}

HealthComponent *TheGuy::getHealthComponent() {
    return &healthComp;
}

AbilityComponent *TheGuy::getAbilityComponent() {
    return abilityComp;
}

AbilityComponent *TheGuy::getBasicAbilityComponent() {
    return basicAbilityComp;
}

AbilityComponent *TheGuy::setAbilityComponent(AbilityType type) {
    //BasicSlash *ability = new BasicSlash();
    //ability->setBlinkEntity((Movable *) this);
    switch (type) {
        case AbilityType::BASIC_SLASH: {
            BasicSlash *abilityBS = new BasicSlash();
            abilityBS->setBlinkEntity((Movable *) this);
            nextAbility = abilityBS;
            return nextAbility;
        }
        case AbilityType::BLINK_SLASH: {
            BlinkSlash *abilityBKS = new BlinkSlash();
            //ability = reinterpret_cast<BasicSlash *>(new BlinkSlash());
            abilityBKS->setBlinkEntity((Movable *) this);
            nextAbility = abilityBKS;
            return nextAbility;
//            printf("Blink \n");
            break;
        }
        case AbilityType::DROP_BOMB: {
            DropBomb *abilityDB = new DropBomb();
            //ability = reinterpret_cast<BasicSlash *>(new DropBomb());
            nextAbility = abilityDB;
            return nextAbility;
//            printf("Slash \n");
            break;
        }
        case AbilityType::METEOROID: {
            MeteoroidAbility *abilityM = new MeteoroidAbility();
            //ability = reinterpret_cast<BasicSlash *>(new DropBomb());
            abilityM->setCaster(this);
            nextAbility = abilityM;
            return nextAbility;
//            printf("Slash \n");
            break;
        }
        case AbilityType::SHOOT: {
            Shoot *abilityS = new Shoot();
            abilityS->setShootingObject(this);
            //ability = reinterpret_cast<BasicSlash *>(new Shoot());
            nextAbility = abilityS;
            return nextAbility;
        }
        case AbilityType::BOOMERANG: {
            auto *boomerangAbility = new Boomerang();
            boomerangAbility->setDrawableOrigin(this);
            nextAbility = boomerangAbility;
            return nextAbility;
        }
        default:
            break;
    }
    return nextAbility;
}

bool TheGuy::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    AbilityComponent *abilityComponent = getAbilityComponent();

    if (getStateObj()->getState() == GameState::ABILITY && abilityComponent->getAbilityType() != AbilityType::METEOROID) {
        switch (typeCollidedWith) {
            case EntityType::ABILITY_CONTAINER:
                // TODO MEMORY LEAK?
                obtainAbility((AbilityContainer *) collidedWith);
                syss->getSoundSystem()->playLootMusic();
                break;
            case EntityType::BOOMERANG_PROJECTILE:
                handleBoomerangCollision((BoomerangProjectile *) collidedWith);
                break;
            case EntityType::ENEMY:
                break;
            case EntityType::ENVIRONMENT:
                break;
            case EntityType::ROCK:
                //if((!abilityComponent->isAbilityActive()) || abilityComponent->getAbilityType() != AbilityType::BLINK_SLASH) {
                    resetPosition(collidedWith);
                //}
                break;
            case EntityType::WATERCURRENT:
                if((!abilityComponent->isAbilityActive()) || abilityComponent->getAbilityType() != AbilityType::BLINK_SLASH) {
                    speedUp();
                }
                break;
            case EntityType::FOOD:
                healthComp.setHealth(healthComp.getHealth() + 1);
                syss->getSoundSystem()->playGainHealthMusic();
            case EntityType::THEGUY:
            case EntityType::PROJECTILE:
            default:;
        }
    } else {
        switch (typeCollidedWith) {
            case EntityType::ENEMY:
                if (collideAgain > 0) return false;
                healthComp.decrementHealth();
                if (healthComp.getHealth() < 1) {
                    syss->getSoundSystem()->playtheguyDeathMusic();
                    healthComp.dead();
                }else{
                    syss->getSoundSystem()->playTheGuyDamageMusic();
                }
                collideAgain = 30;
                return !healthComp.isAlive();
            case EntityType::ENEMY_PROJECTILE:
                if (collideAgain > 0) return false;
                healthComp.decrementHealth();
                if (healthComp.getHealth() < 1) {
                    syss->getSoundSystem()->playtheguyDeathMusic();
                    healthComp.dead();
                }else{
                    syss->getSoundSystem()->playTheGuyDamageMusic();
                }
                collideAgain = 30;
                return !healthComp.isAlive();
            case EntityType::ENVIRONMENT:
                resetPosition(collidedWith);
                break;
            case EntityType::ROCK:
                resetPosition(collidedWith);
                break;
            case EntityType::ABILITY_CONTAINER:
                syss->getSoundSystem()->playLootMusic();
                obtainAbility((AbilityContainer *) collidedWith);
                loadAbility();
                break;
            case EntityType::BOOMERANG_PROJECTILE:
                handleBoomerangCollision((BoomerangProjectile *) collidedWith);
                break;
            case EntityType::WATERCURRENT:
                speedUp();
                break;
            case EntityType::FOOD:
                healthComp.setHealth(healthComp.getHealth() + 1);
                syss->getSoundSystem()->playGainHealthMusic();
            case EntityType::THEGUY:
            case EntityType::PROJECTILE:
            default:;
        }
    }
    return false;
}

void TheGuy::resetPosition(Collides *collidedWith) {
    // check x position
    vec2 current_pos = positionComp.getPosition();
    positionComp.resetPosX();
    if (!syss->getCollisionSystem()->didCollide((Collides *) this, collidedWith)) {
        return;
    }

    positionComp.setPosX(current_pos.x);
    // check y position
    positionComp.resetPosY();
    if (!syss->getCollisionSystem()->didCollide((Collides *) this, collidedWith)) {
        return;

    }
    positionComp.setPosY(current_pos.y);

    // check if it still are colliding after both attempt on x and y
    positionComp.resetPosition();
}

void TheGuy::speedUp() {
    positionComp.setPosition({positionComp.getPosX() + (float)0.5 * velocityComp.getVX(),
                              positionComp.getPosY() + (float)0.5 * velocityComp.getVY()});
}

void TheGuy::killTheGuy() {
    syss->removeEntityFromSystems(this);
//    world.killEntity(this);
    destroy();
}

bool TheGuy::checkIfAlive() {
    return is_alive;
}

void TheGuy::Alive() {
    is_alive = true;
    healthComp.setHealth(3);
    healthComp.alive();
}

void TheGuy::loadStateSprite() {
    int currentState = entityState.getState();
//    if (currentState == entityState.getPreFrameState() || currentState == GameState::ABILITY) {
    if (currentState == entityState.getPreFrameState()) {
        // do nothing
        return;
    }

    // clear ability textures
    if (entityState.getPreFrameState() == GameState::ABILITY) {
        for (Texture *texture: ability_textures) {
            free(texture);
        }
        ability_textures.clear();
    }

    if (currentState == GameState::IDLE) {
        int frame, startIndex = 1, numOfSprite = 4;
        spriteTime = 4;
        char *path = (char *) "../data/textures/characters/CartoonNinja/IdlePose02/IdlePose02_0";
        frame = spriteTime * numOfSprite;
        drawComp.setNewAnimation(idle_textures, frame, spriteTime);
    } else if (currentState == GameState::MOVE) {
        int frame, startIndex = 1, numOfSprite = 8;
        spriteTime = 4;
        char *path = (char *) "../data/textures/characters/CartoonNinja/RunPose02/RunPose02_0";
        frame = spriteTime * numOfSprite;
        drawComp.setNewAnimation(move_textures, frame, spriteTime);
    } else if (currentState == GameState::DEATH) {
        int frame, startIndex = 1, numOfSprite = 23;
        spriteTime = 4;
        char *path = (char *) "../data/textures/characters/CartoonNinja/Death/Death_0";
        frame = spriteTime * numOfSprite;
        drawComp.setNewAnimation(death_textures, frame, spriteTime);
    } else if (currentState == GameState::ABILITY) {
        int frame;
        frame = spriteTime * ability_textures.size();
        drawComp.setNewAnimation(ability_textures, frame, spriteTime);
    }
}

void TheGuy::obtainAbility(AbilityContainer *container) {
    setAbilityComponent(container->abilityContained);
}

void TheGuy::setMaxHealth(int h) {
    max_health = h;
}

void TheGuy::setMaxCharges(int c) {
    max_charges = c;
}

void TheGuy::loadAbility() {
    if (nextAbility == nullptr) {
        return;
    }
    abilityComp = nextAbility;
    nextAbility = nullptr;
}

void TheGuy::preloadTexture() {
    int startIndex, numOfSprite;
    char *path;

    if (newWorld) {
        // idle
        emptyTextureVector(idle_textures);
        path = (char *) "../data/textures/characters/CartoonNinja/IdlePose02/IdlePose02_0";
        startIndex = 1, numOfSprite = 4;
        idle_textures = setSpriteTextures(path, (char *) "png", startIndex, numOfSprite);

        // move
        emptyTextureVector(move_textures);
        path = (char *) "../data/textures/characters/CartoonNinja/RunPose02/RunPose02_0";
        startIndex = 1, numOfSprite = 8;
        move_textures = setSpriteTextures(path, (char *) "png", startIndex, numOfSprite);

        // death
        emptyTextureVector(death_textures);
        path = (char *) "../data/textures/characters/CartoonNinja/Death/Death_0";
        startIndex = 1, numOfSprite = 23;
        death_textures = setSpriteTextures(path, (char *) "png", startIndex, numOfSprite);

        //clear ability texture at the start
        ability_textures.clear();
    }

    newWorld = false;

}

void TheGuy::setAbilityAnimation(char *path, int spriteT, int startIndex, int numberOfSprite) {
    if (!ability_textures.empty()) {
        for (Texture *t: ability_textures) {
            free(t);
        }
        ability_textures.clear();
    }
    ability_textures = setSpriteTextures(path, (char *) "png", startIndex, numberOfSprite);
    spriteTime = spriteT;
}

void TheGuy::collideAgainDecrement() {
    collideAgain--;
}

void TheGuy::handleBoomerangCollision(BoomerangProjectile *boomerang) {
    if (abilityComp->getAbilityType() == AbilityType::BOOMERANG && boomerang->isGoingBackwards()) {
        // pick up boomerang
        abilityComp->addCharge();
    }
}


