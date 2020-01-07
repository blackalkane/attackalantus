//
// Created by Andy He on 2019-10-04.
//

#include "simpleAISystem.hpp"

bool SimpleAISystem::init() {
    velocity = 0.0;
    destination = {0.0, 0.0};
    return true;
}

void SimpleAISystem::destroy() {
    System::destroy();
}

//bool SimpleAISystem::addEntity(Movable* object){
//    entities.push_back(object);
//    return true;
//}
//
//bool SimpleAISystem::removeEntity(Entity* entity_ptr) {
//    int elementIndex = -1;
//    for (int i = 0; i < entities.size(); i++){
//        if (entities[i] == entity_ptr){
//            elementIndex = i;
//            break;
//            // free(entities[i]);
//        }
//    }
//    if (elementIndex == -1){
//        return false;
//    }
//    entities.erase(entities.begin() + elementIndex);
//    return true;
//}

void SimpleAISystem::update(float elapsedMs) {
    for(Entity* entity: entities){
        Movable* movableEntity = dynamic_cast<Movable*>(entity);
        setEntityVelocity(movableEntity);
    }
}

void SimpleAISystem::setEntityVelocity(Movable *entity) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 position = entityPositionObj->getPosition();

    vec2 length = {destination.x - position.x, destination.y - position.y};

    vec2 ratio = {};

    float manhanttan_distance = abs(length.x) + abs(length.y);
    if (manhanttan_distance == 0.f){
        ratio = {1.0, 1.0};
    }
    else {
        ratio = {abs(length.x) / manhanttan_distance, abs(length.y) / manhanttan_distance};
    }

    // for speed enemy
    if (entity->type == EntityType::ENEMY && dynamic_cast<Enemy*>(entity)->getEnemyType() == EnemyType::SPEED) {
        ratio = {ratio.x * 2, ratio.y * 2};
    }

    float vx , vy;
    if(length.x < 0){
        vx = ratio.x * -velocity;
    }else{
        vx = ratio.x * velocity;
    }

    if(length.y < 0){
        vy = ratio.y * -velocity;
    }else{
        vy = ratio.y * velocity;
    }
    // printf("%f,%f\n", ratio.x, ratio.y);
    entityVelocityObj->setVelocity({vx, vy});


}

bool SimpleAISystem::setDestPoint(vec2 point) {
    destination = point;
    return true;
}

bool SimpleAISystem::setVelocity(float v) {
    velocity = v;
    return true;
}

