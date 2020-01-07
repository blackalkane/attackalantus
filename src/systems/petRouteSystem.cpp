//
// Created by Andy He on 2019-12-07.
//

#include <SDL_stdinc.h>
#include "petRouteSystem.hpp"
bool PetRouteSystem::init() {
    velocity = 0.0;
    center_p = {0.0, 0.0};
    radius = 70.0;
    step_counter = 0;
    total_step = 20;
    update_step = 0;
    return true;
}

void PetRouteSystem::destroy() {
    System::destroy();
}

void PetRouteSystem::update(float elapsedMs) {
    double rad = (step_counter * 2 * M_PI) / total_step;
    float off_x = cos(rad) * radius;
    float off_y = sin(rad) * radius;
    vec2 cir_pos = {center_p.x + off_x, center_p.y + off_y};
    setDestPoint(cir_pos);
    for(Entity* entity: entities){
        Movable* movableEntity = dynamic_cast<Movable*>(entity);
        setEntityVelocity(movableEntity);
        vec2 next_pos = movableEntity->getPositionComponent()->getPosition();
        vec2 new_v = movableEntity->getVelocityComponent()->getVelocity();
        next_pos = {next_pos.x - new_v.x, next_pos.y - new_v.y};
        setDestPoint(next_pos);
    }
    // counter update
    update_step++;
    if (update_step >= 5) {
        step_counter = (step_counter + 1) % total_step;
        update_step = 0;
    }
}

void PetRouteSystem::setEntityVelocity(Movable *entity) {
    VelocityComponent* entityVelocityObj = entity->getVelocityComponent();
    PositionComponent* entityPositionObj = entity->getPositionComponent();
    vec2 position = entityPositionObj->getPosition();

    vec2 length = {dest_p.x - position.x, dest_p.y - position.y};

    vec2 ratio = {};

    float manhanttan_distance = abs(length.x) + abs(length.y);

    // if distance is closer
    if (manhanttan_distance < velocity) {
        entityVelocityObj->setVelocity({length.x / 1000, length.y / 1000});
//        entityVelocityObj->setVelocity({0,0});
        return;
    }
    if (manhanttan_distance == 0.f){
        ratio = {1.0, 1.0};
    }
    else {
        ratio = {abs(length.x) / manhanttan_distance, abs(length.y) / manhanttan_distance};
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

bool PetRouteSystem::setCenterPoint(vec2 point) {
    center_p = point;
    return true;
}

bool PetRouteSystem::setVelocity(float v) {
    velocity = v;
    return true;
}

bool PetRouteSystem::setDestPoint(vec2 point) {
    dest_p = point;
    return true;
}
