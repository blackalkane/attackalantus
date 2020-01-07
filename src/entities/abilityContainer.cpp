#include "abilityContainer.hpp"

std::vector<Texture*> AbilityContainer::CONTAINER_TEXTURE = {};
bool AbilityContainer::newWorld = true;

AbilityContainer::AbilityContainer(AbilityType ability) {
    abilityContained = ability;
}

void AbilityContainer::destroy() {
    drawComp.destroy();
    positionComp.destroy();
}

bool AbilityContainer::init() {
    drawComp.fragmentShaderPath = shader_path("rock.fs.glsl");
    drawComp.vertexShaderPath = shader_path("rock.vs.glsl");
    float scaleX = 2.0, scaleY = 2.0;

//    drawComp.PNGPath = "../data/textures/environment/props_items/chest_closed_anim_f0.png";
//    char *path = (char *) "../data/textures/environment/props_items/chest_closed_anim_f";
    int frame = 0, spriteTime = 7, startIndex = 0, numberOfSprite = 85;
    frame = spriteTime * numberOfSprite;
//    drawComp.preInit(frame, spriteTime, path, (char*)"png", startIndex, numberOfSprite);
    preloadTexture();
    drawComp.setStaticTexture(nullptr);
    drawComp.setNewAnimation(CONTAINER_TEXTURE, frame, spriteTime);
    drawComp.physics.scale = {scaleX, scaleY};
    drawComp.init();

    Texture *texture = drawComp.texture;
    positionComp.init();
    positionComp.setWidth((texture->width) * scaleX);
    positionComp.setHeight((texture->height) * scaleY);

    type = EntityType::ABILITY_CONTAINER;
    return true;
}

PositionComponent *AbilityContainer::getPositionComponent() {
    return &positionComp;
}

DrawComponent *AbilityContainer::getDrawComponent() {
    return &drawComp;
}

bool AbilityContainer::handleCollision(Collides *collidedWith) {
    EntityType type = collidedWith->type;
    switch (type) {
        case EntityType::THEGUY: // If colliding with the guy, disappear
            return true;
        case EntityType::ENVIRONMENT:break;
        case EntityType::ENEMY:break;
        case EntityType::ROCK:break;
        case EntityType::PROJECTILE:break;
        case EntityType::ABILITY_CONTAINER:break;
        default: break;
    }
    return false;
}

void AbilityContainer::preloadTexture() {
    int startIndex, numOfSprite;
    char* path;

    if(newWorld) {
        path = (char*)"../data/textures/environment/props_items/chest_closed_anim_f";
        startIndex = 0, numOfSprite = 85;
        CONTAINER_TEXTURE = setSpriteTextures(path, (char*)"png", startIndex, numOfSprite);
    }

    newWorld = false;
}

void AbilityContainer::setAbilityContain(AbilityType ability) {
    abilityContained = ability;
}
