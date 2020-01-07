#ifndef ATTACKATLANTIS_COLLISIONSYSTEM_HPP
#define ATTACKATLANTIS_COLLISIONSYSTEM_HPP

#include "system.hpp"
#include <entities/collides.hpp>
#include <entities/theguy.hpp>
#include <entities/enemy.hpp>
#include <entities/projectile.hpp>
#include <entities/rock.hpp>

class CollisionSystem : public System {
public:
    bool init() override;

    void destroy() override;

    // bool addEntity(Collides* object);

    // bool removeEntity(Entity* object)override;

    void update(float elapsedMs) override;

    std::vector<std::pair<Collides*, Collides*>> getCollidingEntities();

    static bool didCollide(Collides* c1, Collides* c2);

    void setSystems(std::vector<System *> allSys);

    bool pointWillCollide(vec2 point);

    bool isTooClose(vec2 p1, vec2 p2, float d);

//    bool pointWillCollide(vec2 vec2, std::vector<Rock *> vector);

    bool pointWillCollide(vec2 vec2, Rock* rock);

    std::unordered_set<Collides *> getToBeKilledForChecking();

    void killEntities(const std::unordered_set<Collides *>& set);

private:
    // std::vector<Collides*> entities;

    void handleCollision(std::pair<Collides *, Collides *>, std::unordered_set<Collides*>& toBeKilled);

    void theGuyCollisionHandler(TheGuy *theGuy, Collides *collideObj2);

    void theEnemyCollisionHandler(Enemy *enemy, Collides *collideObj2);

    void theGuyEnemyHandler(TheGuy *theGuy, Enemy *enemy);

    void theProjEnemyHandler(Projectile *proj, Enemy *enemy);

    bool pointIsInBox(vec2 point, vec4 box);

    std::unordered_set<Collides *> toBeKilledForChecking;
};

#endif //ATTACKATLANTIS_COLLISIONSYSTEM_HPP
