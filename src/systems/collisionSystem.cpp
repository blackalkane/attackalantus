#include <global.hpp>
#include <allSystem.hpp>
#include "collisionSystem.hpp"

bool CollisionSystem::init() {
    return true;
}

void CollisionSystem::destroy() {
    System::destroy();
}

void CollisionSystem::update(float elapsedMs) {
    auto collisions = getCollidingEntities();
    // put entities that need to die as a result of collision in here
    std::unordered_set<Collides *> toBeKilled;
    for (auto collision : collisions) {
        handleCollision(collision, toBeKilled);
    }
    toBeKilledForChecking = toBeKilled;
     killEntities(toBeKilled);
}

std::vector<std::pair<Collides *, Collides *>> CollisionSystem::getCollidingEntities() {
    auto collisions = std::vector<std::pair<Collides *, Collides *>>();
    for (unsigned int i = 0; i < entities.size(); i++) {
        for (unsigned int j = i + 1; j < entities.size(); j++) {
            Collides *c1 = dynamic_cast<Collides*>(entities[i]);
            Collides *c2 = dynamic_cast<Collides*>(entities[j]);
            if (didCollide(c1, c2) && c1->type != c2->type) {
                collisions.emplace_back(c1, c2);
            }
        }
    }
    return collisions;
}

bool CollisionSystem::didCollide(Collides *c1, Collides *c2) {
    vec4 box1 = c1->getBoundingBox();
    vec4 box2 = c2->getBoundingBox();

    vec2 c1pos = {box1.x1, box1.y1};
    float c1width = box1.x2;
    float c1height = box1.y2;

    vec2 c2pos = {box2.x1, box2.y1};
    float c2width = box2.x2;
    float c2height = box2.y2;

    auto box1posx1 = c1pos.x - (c1width / 2);
    auto box1posy1 = c1pos.y - (c1height / 2);
    auto box1posx2 = c1pos.x + (c1width / 2);
    auto box1posy2 = c1pos.y + (c1height / 2);

    auto box2posx1 = c2pos.x - (c2width / 2);
    auto box2posy1 = c2pos.y - (c2height / 2);
    auto box2posx2 = c2pos.x + (c2width / 2);
    auto box2posy2 = c2pos.y + (c2height / 2);

    return box1posx1 < box2posx2
           && box1posx2 > box2posx1
           && box1posy1 < box2posy2
           && box1posy2 > box2posy1;
}

void CollisionSystem::handleCollision(std::pair<Collides *, Collides *> collideObjs,
                                      std::unordered_set<Collides *>& toBeKilled) {
    // TODO
    Collides *collideObj1 = collideObjs.first;
    Collides *collideObj2 = collideObjs.second;
    // Collision logic will be handled at the class level, returns true if it should be killed
    if (toBeKilled.find(collideObj1) == toBeKilled.end()) { // first object isn't in set
        bool firstShouldBeKilled = collideObj1->handleCollision(collideObj2);
        if (firstShouldBeKilled){
            toBeKilled.insert(collideObj1);
//            syss->getDeleteSystem()->addEntity(collideObj1);
        }
    }
    if (toBeKilled.find(collideObj2) == toBeKilled.end()) { // second object isn't in set
        bool secondShouldBeKilled = collideObj2->handleCollision(collideObj1);
        if (secondShouldBeKilled) {
            toBeKilled.insert(collideObj2);
//            syss->getDeleteSystem()->addEntity(collideObj2);
        }
    }
}

void CollisionSystem::killEntities(const std::unordered_set<Collides *>& set) {
//    AllSystem* syss = AllSystem::get_instance();
    for (Collides* entity : set) {
//        world.killEntity(entity);
        syss->removeEntityFromSystems(entity);
        if(entity->type == EntityType::ENEMY || entity->type == EntityType::THEGUY || entity->type == EntityType::PET) {
            if(entity->type == EntityType::THEGUY) {
                syss->getSoundSystem()->playtheguyDeathMusic();
            }
            syss->getDrawSystem()->addEntity(entity);
            syss->getDeleteSystem()->addEntity(entity);
        }
    }
}
/**
 *
 * @param point
 * @return true if this coordinate will collide with any current collidable entities.
 */
bool CollisionSystem::pointWillCollide(vec2 point) {
    for (auto* entt : entities) {
        auto* collidable = dynamic_cast<Collides*>(entt);
        auto box = collidable->getBoundingBox();
        if (pointIsInBox(point, box)) {
            return true;
        }
    }
    return false;
}

/**
 *
 * @param point
 * @param box
 * @return true if the given point collides with the given box.
 */
bool CollisionSystem::pointIsInBox(vec2 point, vec4 box) {
    vec2 boxPos = {box.x1, box.y1};
    float boxWidth = box.x2;
    float boxHeight = box.y2;

    auto left = boxPos.x - (boxWidth / 2);
    auto bottom = boxPos.y - (boxHeight / 2);
    auto right = boxPos.x + (boxWidth / 2);
    auto top = boxPos.y + (boxHeight / 2);

    return point.x <= right
            && point.x >= left
            && point.y <= top
            && point.y >= bottom;
}
/**
 *
 * @param p1 first point
 * @param p2 second point
 * @param d minimum distance the points should be apart
 * @return true if the points are more than d apart
 */
bool CollisionSystem::isTooClose(vec2 p1, vec2 p2, float d) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return std::sqrt((dx * dx) + (dy * dy)) < d;
}

bool CollisionSystem::pointWillCollide(vec2 point, Rock* rock) {
//    for (auto & rock : rocks) {
    auto box = rock->getBoundingBox();
    if (pointIsInBox(point, box)) {
        return true;
    }
//    }
    return false;
}

std::unordered_set<Collides *> CollisionSystem::getToBeKilledForChecking() {
    return toBeKilledForChecking;
}
