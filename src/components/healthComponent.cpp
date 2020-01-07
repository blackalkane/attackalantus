#include "healthComponent.hpp"

HealthComponent::HealthComponent(){

}

HealthComponent::~HealthComponent(){

}

bool HealthComponent::init() {
    //health = 0;
    isLive = true;
    return true;
}

void HealthComponent::destroy() {}

void HealthComponent::setHealth(int h) {
    health = h;
}

int HealthComponent::getHealth() {
    return health;
}

void HealthComponent::decrementHealth() {
    health--;
}

void HealthComponent::alive() {
    isLive = true;
}

void HealthComponent::dead() {
    isLive = false;
}

bool HealthComponent::isAlive() {
    return isLive;
}

