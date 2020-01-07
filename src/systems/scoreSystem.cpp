#include <global.hpp>
#include <ctime>
#include <utility>
#include "scoreSystem.hpp"

#define MAX_RECORDS_SIZE 10

ScoreSystem::ScoreSystem() {
    score = 0;
    minHighScore = 0;
}

void ScoreSystem::update(float elapsedMs) {
    std::string title = "ATTACKALANTUS --- SCORE: "
                        + std::to_string(score)
                        + " --- HIGHSCORE: "
                        + std::to_string(minHighScore);
    if (window != nullptr) {
        glfwSetWindowTitle(window, title.c_str());
    }
}

bool ScoreSystem::init() {
    return true;
}

void ScoreSystem::addPoints(int pointsToAdd) {
    score += pointsToAdd;
}

void ScoreSystem::resetScore() {
    if (score > minHighScore) {
        minHighScore = score;
    }
    score = 0;
}

void ScoreSystem::destroy() {
    // nothing to free
    System::destroy();
}

bool ScoreSystem::removeEntity(Entity *entity) {
    if (System::removeEntity(entity)) {
        switch (entity->type) {
            case EntityType::ENEMY: {
                auto *enemy = dynamic_cast<Enemy *>(entity);
                switch (enemy->getEnemyType()) {
                    default:
                    case EnemyType::BASIC:
                        addPoints(100);
                        break;
                    case EnemyType::SHOOTING:
                        addPoints(150);
                        break;
                    case EnemyType::SPEED:
                        addPoints(200);
                        break;
                    case EnemyType::BOSS:
                        addPoints(5000);
                        break;
                    case EnemyType::BOSS2:
                        addPoints(100000);
                        break;
                }
                return true;
            }
            case EntityType::THEGUY:
                break;
            case EntityType::ENVIRONMENT:
                break;
            case EntityType::ROCK:
                break;
            case EntityType::PROJECTILE:
                break;
            default:
                break;
        }
        return true;
    } else {
        return false;
    }
}

void ScoreSystem::setWindow(GLFWwindow *w) {
    window = w;
}

bool ScoreSystem::isHighScore() {
    return (records.size() < MAX_RECORDS_SIZE) || (score > minHighScore);
}

void ScoreSystem::saveCurrentScore() {
    savedScore = score;
}

unsigned long ScoreSystem::getSavedScore() {
    return savedScore;
}

void ScoreSystem::storeScoreRecord(ScoreRecord record) {
    // Find the highest score that's less than the one getting inserted
    bool wasInserted = false;
    for (auto it = records.begin(); it != records.end(); it++) {
        if (it->score < record.score) {
            // insert the new entry before that score
            records.insert(it, record);
            wasInserted = true;
            break;
        }
    }
    if (!wasInserted) { // Lower than all existing scores, put at the bottom
        records.insert(records.end(), record);
    }
    // Make sure we don't have too many records
    if (records.size() > MAX_RECORDS_SIZE) {
        //records.erase(records.end());
        records.pop_back();
    }
}

std::list<ScoreRecord> *ScoreSystem::getHighScores() {
    return &records;
}

void ScoreSystem::addScoreRecord(unsigned long highScore, std::string name) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[12];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    std::string date(buffer);

    storeScoreRecord({highScore, std::move(name), date });
}
