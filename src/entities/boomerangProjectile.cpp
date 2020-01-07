
#include <components/shoot.hpp>
#include "boomerangProjectile.hpp"

std::vector<Texture*> BoomerangProjectile::BOOMER_IDLE_TEXTURES = {};
bool BoomerangProjectile::newWorldBoomerang = true;

bool BoomerangProjectile::init() {
    drawComp.fragmentShaderPath = shader_path("projectile.fs.glsl");
    drawComp.vertexShaderPath = shader_path("projectile.vs.glsl");
    drawComp.physics.scale = {1.f, 1.f};
//    std::string path = "../data/textures/others/boomerang/bullet006.000";
    int spriteTime = 5, numberOfSprite = 8;
    int frame = spriteTime * numberOfSprite;
    preloadTexture();
    drawComp.setNewAnimation(BOOMER_IDLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    velocityComp.init();
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;
    positionComp.setWidth((texture->width) * 1.f);
    positionComp.setHeight((texture->height) * 1.f);
    initialDirection = {1.f, 1.f};

    type = EntityType::BOOMERANG_PROJECTILE;
    return true;
}

void BoomerangProjectile::preloadTexture() {
    if(newWorldBoomerang) {
        char *path = (char *) "../data/textures/others/boomerang/bullet006.000";
        int startIndex = 0, numberOfSprite = 8;
        BOOMER_IDLE_TEXTURES = setSpriteTextures(path, (char *) "png", startIndex, numberOfSprite);
    }
    newWorldBoomerang = false;
}

void BoomerangProjectile::destroy() {
    Projectile::destroy();
}

void BoomerangProjectile::setInitialDirection(vec2 initialDir) {
    initialDirection = initialDir;
}

bool BoomerangProjectile::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        // SHOULD DISAPPEAR
        case EntityType::ENVIRONMENT:
        case EntityType::ROCK:
            return true;
            // SHOULD PASS THROUGH
        case EntityType::ENEMY: break;
        case EntityType::ENEMY_PROJECTILE: break;
        case EntityType::THEGUY: {
            if (goingBackwards) return true; // Get picked up when returning to the guy
            break;
        }
        case EntityType::PROJECTILE: break;
        default:;
    }
    return false;
}

/**
 * @return an updated velocity vector based on whether it should be going forward but slowing down,
 *  reversing direction, or going backwards and speeding up
 */
vec2 BoomerangProjectile::getUpdatedVelocity() {
    vec2 currVelocity = velocityComp.getVelocity();
    if (goingBackwards) {
        return { currVelocity.x - (initialDirection.x * VELOCITY_INCREASE_FACTOR),
                 currVelocity.y - (initialDirection.y * VELOCITY_INCREASE_FACTOR) };
    } else if (shouldReverse(currVelocity)) {
        goingBackwards = true;
        return { -currVelocity.x, -currVelocity.y };
    } else {
        return { currVelocity.x * VELOCITY_DECREASE_FACTOR,
                 currVelocity.y * VELOCITY_DECREASE_FACTOR };
    }
}

/**
 * @param currVelocity
 * @return true if this boomerang should start to accelerate backwards instead of slowing down
 */
bool BoomerangProjectile::shouldReverse(const vec2 &currVelocity) {
    float magnitude = computeMagnitude(currVelocity);
    return magnitude < REVERSAL_THRESHOLD;
}

bool BoomerangProjectile::isGoingBackwards() {
    return goingBackwards;
}
