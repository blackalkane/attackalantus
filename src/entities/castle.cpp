//
// Created by Peter Han on 2019-11-28.
//

#include "castle.hpp"

bool Castle::init()
{
    //drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    //drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.0, scaleY = 1.0;
    //int randNum = (rand() % 2) + 1;

    //preloadTexture();

/*    drawComp.physics.scale = {scaleX, scaleY};
    switch(randNum){
        default:
        case 1:
            drawComp.setStaticTexture(rockTexture);
            break;
        case 2:
            drawComp.setStaticTexture(rock2Texture);
            break;
    }
    drawComp.init();*//*
    positionComp.setPosition({100.f, 100.f});
    Texture *texture = drawComp.texture;*/
    // TODO FIX HACK
/*    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);*/
    type = EntityType::ROCK;
    return true;
}

void Castle::destroy()
{
    positionComp.destroy();
}

/*DrawComponent *Castle::getDrawComponent() {
    return &drawComp;
}*/

PositionComponent *Castle::getPositionComponent() {
    return &positionComp;
}

bool Castle::handleCollision(Collides *collidedWith) {
    // should never die
    return false;
}
/*

void Rock::preloadTexture() {
    std::string rockPath = "../data/textures/environment/environment_objects/rock.png";
    rockTexture = setTexture(rockPath);

    std::string rock2Path = "../data/textures/environment/environment_objects/rock2.png";
    rock2Texture = setTexture(rock2Path);
}
*/

