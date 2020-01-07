//
// Created by Andy He on 2019-12-01.
//

#include "rainDrop.hpp"

bool RainDrop::newWorld = true;
std::vector<Texture*> RainDrop::RAINDROP_TEXTURES1 = {};
std::vector<Texture*> RainDrop::RAINDROP_TEXTURES2 = {};

bool RainDrop::init()
{
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.0, scaleY = 1.0;
    int randNum = (rand() % 2) + 1;

    int frame , spriteTime = 4;

    preloadTexture();



    drawComp.physics.scale = {scaleX, scaleY};
    switch(randNum){
        default:
        case 1:
            frame = spriteTime * RAINDROP_TEXTURES1.size();
            drawComp.setNewAnimation(RAINDROP_TEXTURES1, frame, spriteTime);
            break;
        case 2:
            frame = spriteTime * RAINDROP_TEXTURES2.size();
            drawComp.setNewAnimation(RAINDROP_TEXTURES2, frame, spriteTime);
            break;
    }
    drawComp.init();

    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);
    type = EntityType::PARTICLE;

    velocityComp.init();

    return true;
}

void RainDrop::destroy()
{
    drawComp.destroy();
}

DrawComponent *RainDrop::getDrawComponent() {
    return &drawComp;
}

PositionComponent *RainDrop::getPositionComponent() {
    return &positionComp;
}

//bool RainDrop::handleCollision(Collides *collidedWith) {
//    // should never die
//    return false;
//}

void RainDrop::preloadTexture() {
    if(newWorld) {
        char* path;
        int startIndex, numOfSprite;
        path = (char *) "../data/textures/environment/EnviroPack02/ShootingStar/ShootingStar_0";
        startIndex = 1, numOfSprite = 8;
        RAINDROP_TEXTURES1 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        path = (char *) "../data/textures/environment/EnviroPack02/ShootingStar/ShootingStar_0";
        startIndex = 1, numOfSprite = 8;
        RAINDROP_TEXTURES2 = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }
    newWorld = false;
}

VelocityComponent *RainDrop::getVelocityComponent() {
    return &velocityComp;
}


