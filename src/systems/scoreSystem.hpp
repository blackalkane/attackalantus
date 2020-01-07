#ifndef ATTACKATLANTIS_SCORESYSTEM_HPP
#define ATTACKATLANTIS_SCORESYSTEM_HPP

#include "system.hpp"

struct ScoreRecord {
    unsigned long score;
    std::string name;
    std::string date;
};

class ScoreSystem : public System {
public:

    ScoreSystem();

    bool init() override;

    void update(float elapsedMs) override;

    void destroy() override;

    bool removeEntity(Entity *) override;

    void addPoints(int points);

    void resetScore();

    void setWindow(GLFWwindow *w);

    bool isHighScore();

    void saveCurrentScore();

    unsigned long getSavedScore();

    std::list<ScoreRecord> *getHighScores();

    void addScoreRecord(unsigned long highScore, std::string name);

private:
    std::list<ScoreRecord> records;
    unsigned long score;
    unsigned long minHighScore;
    // Hold for when we're transitioning to leaderboard
    unsigned long savedScore;

    void storeScoreRecord(ScoreRecord record);

    GLFWwindow *window;
};

#endif