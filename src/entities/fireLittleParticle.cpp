//
// Created by Andy He on 2019-12-06.
//

#include "fireLittleParticle.hpp"

bool FireLittleParticle::newWorld = true;
std::vector<Texture*> FireLittleParticle::FIRE_PARTICLE_TEXTURES = {};

bool FireLittleParticle::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 0.5, scaleY = 0.5;
//    int randNum = (rand() % 2) + 1;

    int frame , spriteTime = 3;

    preloadTexture();

    frame = spriteTime * FIRE_PARTICLE_TEXTURES.size();



    drawComp.physics.scale = {scaleX, scaleY};
//    switch(randNum){
//        default:
//        case 1:
//            drawComp.setNewAnimation(PARTICLE_TEXTURES1, frame, spriteTime);
//            break;
//        case 2:
//            drawComp.setNewAnimation(PARTICLE_TEXTURES2, frame, spriteTime);
//            break;
//    }
    drawComp.setNewAnimation(FIRE_PARTICLE_TEXTURES, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.init();
    startPosition = {-100.0, -100.0};
    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);
    type = EntityType::PARTICLE;

    velocityComp.init();

    direction = 0;

    return true;
}

void FireLittleParticle::setDirection(int dir) {
    direction = dir;
}

void FireLittleParticle::destroy()
{
    drawComp.destroy();
    positionComp.destroy();
    velocityComp.destroy();
}

DrawComponent *FireLittleParticle::getDrawComponent() {
    return &drawComp;
}

PositionComponent *FireLittleParticle::getPositionComponent() {
    return &positionComp;
}

//bool FireLittleParticle::handleCollision(Collides *collidedWith) {
//    // should never die
//    return false;
//}

void FireLittleParticle::preloadTexture() {
    if(newWorld) {
        char* path;
        int startIndex, numOfSprite;
        path = (char *) "../data/textures/effects/GameFX/PngSpritesheet_x64/FireBurst_64x64/FireBurst_64x64-";
        startIndex = 1, numOfSprite = 29;
        FIRE_PARTICLE_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    newWorld = false;
}

VelocityComponent *FireLittleParticle::getVelocityComponent() {
    return &velocityComp;
}

void FireLittleParticle::setStartPosition(vec2 position) {
    startPosition = position;
    positionComp.setPosition(position);
}

vec2 FireLittleParticle::getStartPosition() {
    return startPosition;
}

int FireLittleParticle::getDirection() {
    return direction;
}
