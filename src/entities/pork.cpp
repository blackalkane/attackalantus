//
// Created by Andy He on 2019-12-05.
//

#include "pork.hpp"

std::vector<Texture*> Pork::PORK_TEXTURES = {};
Texture* Pork::PORK_TEXTURE = nullptr;
bool Pork::newWorld = true;

bool Pork::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 1.5, scaleY = 1.5;

    int frame , spriteTime = 5;

    preloadTexture();
    frame = spriteTime * PORK_TEXTURES.size();
//    drawComp.setNewAnimation(PORK_TEXTURES, frame, spriteTime);
    drawComp.setStaticTexture(PORK_TEXTURE);

    drawComp.physics.scale = {scaleX, scaleY};

    drawComp.init();
    Texture *texture = drawComp.texture;
    // TODO FIX HACK
    positionComp.init();
    positionComp.setWidth((texture->width) * scaleX * 0.75);
    positionComp.setHeight((texture->height) * scaleY * 0.75);

    type = EntityType::FOOD;

    return true;
}

void Pork::destroy() {
    drawComp.destroy();
    positionComp.destroy();

}

DrawComponent *Pork::getDrawComponent() {
    return &drawComp;
}

PositionComponent *Pork::getPositionComponent() {
    return &positionComp;
}

void Pork::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char *) "../data/textures/environment/props_items/torch_anim_f";
        startIndex = 0, numOfSprite = 6;
        PORK_TEXTURES = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);

        std::string porkPath = "../data/textures/environment/foodImage/Pepperoni.png";
        PORK_TEXTURE = setTexture(porkPath);
    }

    newWorld = false;
}

bool Pork::handleCollision(Collides *collidedWith) {
    EntityType typeCollidedWith = collidedWith->type;

    switch (typeCollidedWith) {
        case EntityType::ENVIRONMENT:
        case EntityType::ENEMY:
        case EntityType::ENEMY_PROJECTILE:
        case EntityType::ROCK:
        case EntityType::PROJECTILE:
            break;
        case EntityType::THEGUY:
            return true;

        default:;
    }
    return false;
}
