//
// Created by Andy He on 2019-12-01.
//

#include "particle.hpp"

bool Particle::newWorld = true;
std::vector<Texture*> Particle::PARTICLE_TEXTURES1 = {};
std::vector<Texture*> Particle::PARTICLE_TEXTURES2 = {};

bool Particle::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.0, scaleY = 1.0;
//    int randNum = (rand() % 2) + 1;

    int frame , spriteTime = 3, numberOfSprite = 29;
    frame = spriteTime * numberOfSprite;

    preloadTexture();



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
    drawComp.setNewAnimation(PARTICLE_TEXTURES1, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.init();
    startPosition = {-100.0, -100.0};
    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);
    type = EntityType::PARTICLE;

    velocityComp.init();

    return true;
}

void Particle::destroy()
{
    drawComp.destroy();
    positionComp.destroy();
    velocityComp.destroy();
}

DrawComponent *Particle::getDrawComponent() {
    return &drawComp;
}

PositionComponent *Particle::getPositionComponent() {
    return &positionComp;
}

//bool Particle::handleCollision(Collides *collidedWith) {
//    // should never die
//    return false;
//}

void Particle::preloadTexture() {
    if(newWorld) {
        char* path;
        int startIndex, numOfSprite;
        path = (char *) "../data/textures/effects/GameFX/PngSpritesheet_x64/FireBurst_64x64/FireBurst_64x64-";
        startIndex = 1, numOfSprite = 29;
        PARTICLE_TEXTURES1 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        path = (char *) "../data/textures/effects/hit_animations_3/impact02/impact02-";
        startIndex = 1, numOfSprite = 11;
        PARTICLE_TEXTURES2 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    newWorld = false;
}

VelocityComponent *Particle::getVelocityComponent() {
    return &velocityComp;
}

void Particle::setStartPosition(vec2 position) {
    startPosition = position;
    positionComp.setPosition(position);
}

vec2 Particle::getStartPosition() {
    return startPosition;
}


