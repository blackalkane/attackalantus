// Limits to check against when spawning.
// Essentially constants, but leaving open to change
// so that different levels can have different spawn patterns.
struct SpawnLimits {
    int MAX_BASIC_ENEMIES;
    int MAX_SHOOTING_ENEMIES;
    int MAX_SPEED_ENEMIES;
    int MAX_FRAMES_UNTIL_SPAWN;
    int MAX_FRAMES_TO_DECREMENT;
    int DEFAULT_FRAMES_UNTIL_SPEEDUP;
    int MIN_FRAMES_UNTIL_SPAWN;
    int FRAMES_TO_SPEEDUP_BY;
    float TIME_PER_ABILITY_SPAWN;
    int MAX_FRAMES_UNTIL_SHOOT;
    int MAX_BOSS_ENEMIES;
    int MAX_BOSS2_ENEMIES;
};