#include "explosion.hpp"

Explosion::Explosion() {
    currentTime = 0;
    abilityDuration = 70;
    timeExplode = 25;
    init();
}

Explosion::~Explosion() {

}

void Explosion::update() {
    if (!isActive){
        return;
    }
    //printf("duration: %d\n", abilityDuration);
//    DrawSystem* drawSystem = world.getDrawSystem();
//    AbilitySystem* abilitySystem = world.getAbilitySystem();
//    DeleteSystem* deleteSystem = world.getDeleteSystem();
//    CollisionSystem* collisionSystem = world.getCollisionSystem();
    DrawSystem* drawSystem = syss->getDrawSystem();
    AbilitySystem* abilitySystem = syss->getAbilitySystem();
    DeleteSystem* deleteSystem = syss->getDeleteSystem();
    CollisionSystem* collisionSystem = syss->getCollisionSystem();
    if (currentTime < timeExplode) {
        //do nothing
    }
    else if (currentTime == timeExplode) {
        syss->getSoundSystem()->playExplosionMusic();
        for(int i = 0; i < 2; i++) {
            BombExplosion* be = new BombExplosion();
            be->init();
            be->getPositionComponent()->setPosition(curPos);
            bombExplosions.push_back(be);
            drawSystem->addEntity(be);
            collisionSystem->addEntity(be);
        }
        //printf("haha");
    }
    else if (currentTime <= 55) {
        //printf("wawa");
        float increaseScale = 0.002;
        for (int i = 0; i < 2; i++) {
            if(i == 0) {
                int originWidth = bombExplosions[i]->getDrawComponent()->texture->width;
                vec2 curScale = bombExplosions[i]->getDrawComponent()->physics.scale;
                bombExplosions[i]->getDrawComponent()->physics.scale = {curScale.x + ((float)currentTime * curScale.x * increaseScale), curScale.y};
                bombExplosions[i]->getPositionComponent()->setWidth((float)originWidth * (curScale.x + ((float)currentTime * curScale.x * increaseScale * 0.7)));
            }
            else {
                int originHeight = bombExplosions[i]->getDrawComponent()->texture->height;
                vec2 curScale = bombExplosions[i]->getDrawComponent()->physics.scale;
                bombExplosions[i]->getDrawComponent()->physics.scale = {curScale.x, curScale.y + ((float)currentTime * curScale.y * increaseScale)};
                bombExplosions[i]->getPositionComponent()->setHeight((float)originHeight * (curScale.y + ((float)currentTime * curScale.y * increaseScale * 0.7)));
            }
        }
        //printf("hahahaha");
    }
    else{
        // do nothing
    }
}

void Explosion::finish() {
    AbilityComponent::finish();
//    DrawSystem* drawSystem = world.getDrawSystem();
//    AbilitySystem* abilitySystem = world.getAbilitySystem();
//    DeleteSystem* deleteSystem = world.getDeleteSystem();
    DrawSystem* drawSystem = syss->getDrawSystem();
    AbilitySystem* abilitySystem = syss->getAbilitySystem();
    DeleteSystem* deleteSystem = syss->getDeleteSystem();
    for(Entity* explosionEntity: bombExplosions) {
//        world.killEntity(explosionEntity);
        syss->removeEntityFromSystems(explosionEntity);
        // explosion Entity will be free automatically, don't need to be added in the deleteSystem
    }
    bombExplosions.clear();
//    world.killEntity(theBomb);
    syss->removeEntityFromSystems(theBomb);
//    deleteSystem->addEntity(theBomb);
    // the bomb will free right here right now
//    free(theBomb);
//    theBomb = nullptr;

}

void Explosion::setBomb(Bomb* bomb) {
    theBomb = bomb;
}

