//
// Created by Andy He on 2019-12-05.
//

#include "meteoroid.hpp"
bool Meteoroid::newWorld = true;
std::vector<Texture*> Meteoroid::METEOROID_TEXTURES1 = {};
std::vector<Texture*> Meteoroid::METEOROID_TEXTURES2 = {};

bool Meteoroid::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.5, scaleY = 1.5;
    int randNum = (rand() % 2) + 1;

    int frame , spriteTime = 3;


    preloadTexture();
    drawComp.physics.scale = {scaleX, scaleY};
    switch(randNum){
        default:
        case 1:
            frame = spriteTime * METEOROID_TEXTURES1.size();
            drawComp.setNewAnimation(METEOROID_TEXTURES1, frame, spriteTime);
            break;
        case 2:
            frame = spriteTime * METEOROID_TEXTURES2.size();
            drawComp.setNewAnimation(METEOROID_TEXTURES2, frame, spriteTime);
            break;
    }
//    drawComp.setNewAnimation(METEOROID_TEXTURES1, frame, spriteTime);
    drawComp.init();

    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);
    type = EntityType::PROJECTILE;

    velocityComp.init();

    return true;
}

void Meteoroid::destroy()
{
    drawComp.destroy();
    positionComp.destroy();
    velocityComp.destroy();
}

DrawComponent *Meteoroid::getDrawComponent() {
    return &drawComp;
}

PositionComponent *Meteoroid::getPositionComponent() {
    return &positionComp;
}

bool Meteoroid::handleCollision(Collides *collidedWith) {
    // should never die
    return false;
}

void Meteoroid::preloadTexture() {
    if(newWorld) {
        char* path;
        int startIndex, numOfSprite;
        path = (char *) "../data/textures/effects/hit_animations_3/impact01/impact01-";
        startIndex = 1, numOfSprite = 11;
        METEOROID_TEXTURES1 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        path = (char *) "../data/textures/effects/hit_animations_3/impact02/impact02-";
        startIndex = 1, numOfSprite = 11;
        METEOROID_TEXTURES2 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    newWorld = false;
}

VelocityComponent *Meteoroid::getVelocityComponent() {
    return &velocityComp;
}