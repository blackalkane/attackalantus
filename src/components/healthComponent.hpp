#ifndef ATTACKATLANTIS_HEALTHCOMPONENT_HPP
#define ATTACKATLANTIS_HEALTHCOMPONENT_HPP

#include "gcomponent.hpp"

class HealthComponent: public virtual GComponent {
public:
    HealthComponent();
    ~HealthComponent();

    bool init();

    void destroy();

    int getHealth();

    void decrementHealth();

    void setHealth(int health);

    void alive();

    void dead();

    bool isAlive();

private:
    int health;
    bool isLive;
};

#endif //ATTACKATLANTIS_HEALTHCOMPONENT_HPP
