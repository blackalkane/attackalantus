#include "spawnSystem.hpp"
#include <global.hpp>


SpawnSystem::SpawnSystem() {
}

bool SpawnSystem::init() {
    if (currLimits == nullptr) {
        currLimits = &initialLimits;
    }
    spawnableAbilityTypes = currLimits->SPAWNABLE_ABILITIES;
    spawnableEnemyTypes = currLimits->SPAWNABLE_ENEMIES;
    shouldSpawnEnemies = true;
    framesUntilSpawn = currLimits->MAX_FRAMES_UNTIL_SPAWN;
    framesUntilSpeedup = currLimits->DEFAULT_FRAMES_UNTIL_SPEEDUP;
    numBasicEnemies = 0;
    numShootingEnemies = 0;
    numSpeedEnemies = 0;
    numBossEnemies = 0;
    numBoss2Enemies = 0;

    currContainer = new AbilityContainer(AbilityType::NO_ABILITY);
    return true;
}

/**
 * Since this system currently has no need to personally interact with the entities,
 * removing entities will do nothing.
 * @param entity
 * @return true
 */
bool SpawnSystem::removeEntity(Entity *entity) {
    return true;
}

/**
 * Since this system currently has no need to personally interact with the entities,
 * adding entities will just increment a counter.
 * @param entity
 * @return true if adding the given entity type would be within the limits for that type.
 */
bool SpawnSystem::addEntity(Entity *entity) {
    EntityType type = entity->type;
    switch (type) {
        case EntityType::ENEMY: {
            auto *enemy = dynamic_cast<Enemy *> (entity);
            switch (enemy->getEnemyType()) {
                case EnemyType::BASIC: return updateBasic(1);
                case EnemyType::SHOOTING: return updateShooting(1);
                case EnemyType::SPEED: return updateSpeed(1);
                case EnemyType::BOSS: return updateBoss(1);
                case EnemyType::BOSS2: return updateBoss2(1);
                default: return false;
            }
        }
        case EntityType::ROCK:break;
        case EntityType::THEGUY:break;
        case EntityType::ENVIRONMENT:break;
        case EntityType::PROJECTILE:break;
        default: break;
    }
    return true;
}

void SpawnSystem::resetLimits() {
//    currLimits = initialLimits;
}

void SpawnSystem::destroy() {
    destroyAbilityContainer(currContainer);
    currContainer = nullptr;
}

/**
 * If the system is set to currently spawn enemies,
 * this will decrement the framesUntilSpawn counter by a pseudo-random amount.
 * If the counter reaches 0, an enemy will be spawned as long as there are enemy types
 * below their spawn capacity. After, the counter will be reset.
 */
void SpawnSystem::spawnEnemies() {
    if (!shouldSpawnEnemies) return;

    int framesToDecrement = rand() % currLimits->MAX_FRAMES_TO_DECREMENT;
    framesUntilSpawn -= framesToDecrement;
    framesUntilSpeedup -= framesToDecrement;

    // Progress spawn rate speed until at limit
    if (framesUntilSpeedup <= 0 && currLimits->MAX_FRAMES_UNTIL_SPAWN > currLimits->MIN_FRAMES_UNTIL_SPAWN) {
        std::cout << "Speeding up...\n";
        currLimits->MAX_FRAMES_UNTIL_SPAWN -= currLimits->FRAMES_TO_SPEEDUP_BY;
        framesUntilSpeedup = currLimits->DEFAULT_FRAMES_UNTIL_SPEEDUP;
    }

    if (framesUntilSpawn > 0) return;

    EnemyType chosenType = chooseEnemyTypeToSpawn();
    framesUntilSpawn = currLimits->MAX_FRAMES_UNTIL_SPAWN;
    spawnEnemy(chosenType);
}

bool SpawnSystem::spawnEnemy(EnemyType type) {
    // TOFIX think of more elegant method
    if (typeIsAtLimit(type)) return false;
    else {
        return addEntity(createEnemy(type));
    }
}

Enemy* SpawnSystem::createEnemy(EnemyType type) {
    Enemy *enemy;
    switch(type) {
        default:
        case EnemyType::BASIC:
            enemy = new BasicEnemy();
            break;
        case EnemyType::SHOOTING:
            enemy = new ShootingEnemy();
            break;
        case EnemyType::SPEED:
            enemy = new SpeedEnemy();
            break;
        case EnemyType ::BOSS:
            enemy = new BossEnemy();
            break;
        case EnemyType ::BOSS2:
            enemy = new BossEnemy2();
            break;
    }
    enemy->init();
    vec2 position = getValidSpawnPosition();
    enemy->getPositionComponent()->setPosition(position);

    // TODO add back later
    // enemies.push_back(enemy);
    syss->getDrawSystem()->addEntity((Drawable *) enemy);
    syss->getCollisionSystem()->addEntity((Collides *) enemy);
    syss->getMoveSystem()->addEntity((Movable *) enemy);
    syss->getScoreSystem()->addEntity(enemy);

    if (type == EnemyType::SHOOTING) {
        syss->getShootingAISystem()->addEntity((Movable *) enemy);
    } else if (type == EnemyType::BASIC){
        syss->getSimpleAISystem()->addEntity((Movable *) enemy);
        syss->getAbilitySystem()->addEntity(enemy);
    } else if (type == EnemyType::BOSS) {
        syss->getBossAISystem()->addEntity((Movable *) enemy);
    } else if (type == EnemyType::BOSS2) {
        syss->getBossAISystem2()->addEntity((Movable *) enemy);
    } else {
        syss->getSimpleAISystem()->addEntity((Movable *) enemy);
    }

    return enemy;
}

bool SpawnSystem::updateBasic(int amount) {
    numBasicEnemies += amount;
    return numBasicEnemies < 0 || numBasicEnemies > currLimits->MAX_BASIC_ENEMIES;
}

bool SpawnSystem::updateShooting(int amount) {
    int updatedVal = numShootingEnemies + amount;
    if (updatedVal < 0 || updatedVal > currLimits->MAX_SHOOTING_ENEMIES) {
        return false;
    }
    numShootingEnemies = updatedVal;
    return true;
}

bool SpawnSystem::updateSpeed(int amount) {
    int updatedVal = numSpeedEnemies + amount;
    if (updatedVal < 0 || updatedVal > currLimits->MAX_SPEED_ENEMIES) {
        return false;
    }
    numSpeedEnemies = updatedVal;
    return true;
}

bool SpawnSystem::updateBoss(int amount) {
    int updatedVal = numBossEnemies + amount;
    if (updatedVal < 0 || updatedVal > currLimits->MAX_BOSS_ENEMIES) {
        return false;
    }
    numBossEnemies = updatedVal;
    return true;
}

bool SpawnSystem::updateBoss2(int amount) {
    int updatedVal = numBoss2Enemies + amount;
    if (updatedVal < 0 || updatedVal > currLimits->MAX_BOSS2_ENEMIES) {
        return false;
    }
    numBoss2Enemies = updatedVal;
    return true;
}

void SpawnSystem::setSpawnLimits(SpawnLimits *limits) {
    currLimits = limits;
}

EnemyType SpawnSystem::chooseEnemyTypeToSpawn() {
    int numTypes = spawnableEnemyTypes.size();
    if (numTypes == 0) {
        return EnemyType::NO_ENEMY;
    }
    int index = rand() % numTypes;
    return spawnableEnemyTypes[index];
}

bool SpawnSystem::typeIsAtLimit(EnemyType type) {
    switch (type) {
        case EnemyType::BASIC:return numBasicEnemies >= currLimits->MAX_BASIC_ENEMIES;
        case EnemyType::SHOOTING:return numShootingEnemies >= currLimits->MAX_SHOOTING_ENEMIES;
        case EnemyType::SPEED:return numSpeedEnemies >= currLimits->MAX_SPEED_ENEMIES;
        case EnemyType::BOSS:return numBossEnemies >= currLimits->MAX_BOSS_ENEMIES;
        case EnemyType::BOSS2:return numBoss2Enemies >= currLimits->MAX_BOSS2_ENEMIES;
        default: break;
    }
    return true;
}

void SpawnSystem::update(float elapsed_Ms) {
    timeUntilAbilitySpawn -= elapsed_Ms;
    if (timeUntilAbilitySpawn < 0) {
        timeUntilAbilitySpawn = currLimits->TIME_PER_ABILITY_SPAWN;
        spawnAbility();
    }
    int partile_per_update = 1;
    for (int i = 0; i < partile_per_update; i++) {
        spawnParticle();
    }
    spawnEnemies();

}

void SpawnSystem::destroyAbilityContainer(AbilityContainer *container) {
    if (container != nullptr) {
        syss->removeEntityFromSystems(container);
//        container->destroy();
        delete container;
    }
}

void SpawnSystem::spawnAbility() {
    AbilityType type = chooseAbilityType();
    if (type == AbilityType::NO_ABILITY || type == AbilityType::BASIC_SLASH)
        return;

//  reset
    syss->getDrawSystem()->removeEntity(currContainer);
    syss->getCollisionSystem()->removeEntity(currContainer);

    vec2 position = getValidSpawnPosition();
    currContainer->init();
    currContainer->setAbilityContain(type);
    currContainer->setPosition(position);
    syss->getDrawSystem()->addEntity(currContainer);
    syss->getCollisionSystem()->addEntity(currContainer);
}

vec2 SpawnSystem::getValidSpawnPosition() {
    vec2 candidate = {(float) (rand() % width), (float) (rand() % height)};

    // TODO find more elegant way
    float offset = 200;
    if (candidate.x < offset || (width - candidate.x) < offset // check distance to borders
        || candidate.y < offset || (height - candidate.y) < offset) {
        return getValidSpawnPosition();
    }
    for (Entity* entity : syss->getDrawSystem()->getEntityList()){
        Drawable* dentity = dynamic_cast<Drawable*>(entity);
        // check that point is not too close to player
        if (dentity->type == EntityType::THEGUY && syss->getCollisionSystem()->isTooClose(candidate, dentity->getPositionComponent()->getPosition(), MIN_DISTANCE_TO_PLAYER)) {
            return getValidSpawnPosition();
        }
        // if any are true, invalid point, try again
        if (dentity->type == EntityType::ROCK && syss->getCollisionSystem()->pointWillCollide(candidate, dynamic_cast<Rock*>(dentity))) {
            return getValidSpawnPosition();
        }
    }
    return candidate;
}

AbilityType SpawnSystem::chooseAbilityType() {
    int numTypes = spawnableAbilityTypes.size();
    if (numTypes == 0) {
        return AbilityType::NO_ABILITY;
    }
    int index = rand() % numTypes;
    return spawnableAbilityTypes[index];
}

// Made this to conform to the delete system
void SpawnSystem::onEnemyDespawn(Enemy *enemyDespawning) {
    switch (enemyDespawning->getEnemyType()) {
        case EnemyType::BASIC: updateBasic(-1);
        case EnemyType::SHOOTING: updateShooting(-1);
        case EnemyType::SPEED: updateSpeed(-1);
        case EnemyType::BOSS: updateBoss(-1);
        case EnemyType::BOSS2: updateBoss2(-1);
        case EnemyType::NO_ENEMY:break;
    }
}

void SpawnSystem::initAbilityContainer() {
    currContainer->init();
    if(currContainer->type != EntityType::ABILITY_CONTAINER) {
        printf("error occur: %d\n", currContainer->type);
    }
}

void SpawnSystem::spawnParticle() {
    RainDrop* p = new RainDrop();

    p->init();

    vec2 position = {(float) (rand() % width), (float) (rand() % height)};
    // position set twice for random direction
//    p->getPositionComponent()->setPosition(position);

    position = {(float) (rand() % width), (float) (rand() % height)};
    p->getPositionComponent()->setPosition(position);
    syss->getDrawSystem()->addEntity(p);
    syss->getDeleteSystem()->addEntity(p);
    syss->getDynamicEnitityStoreSystem()->addEntity(p);
}

AbilityContainer *SpawnSystem::getCurrAbilityContainer() {
    return currContainer;
}




