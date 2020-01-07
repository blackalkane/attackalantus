#ifndef ATTACKATLANTIS_ABILITYCOMPONENT_HPP
#define ATTACKATLANTIS_ABILITYCOMPONENT_HPP


#include <common.hpp>
#include <entities/abilityType.hpp>
#include "gcomponent.hpp"

struct AbilityComponent : public virtual GComponent {
    int getNumCharges() {
        return numCharges;
    }

    void addCharge() {
        numCharges++;
    }

public:
    virtual bool init() {
        isActive = false;
        return true;
    }

    virtual void start() {
        isActive = true;
    }

    virtual void finish() {
        isActive = false;
        currentTime = 0;
    };

    virtual bool isAbilityActive() {
        return isActive;
    }

    virtual int getDuration() {
        return abilityDuration;
    }

    virtual int getCurrentTime() {
        return currentTime;
    }

    virtual AbilityType getAbilityType() {
        return abilityType;
    }

    virtual void setCurrentTime(int time) {
        currentTime = time;
    }

    virtual void update() = 0;

    virtual void setMousePos(vec2 pos) {
        mousePos = pos;
    }

    virtual void setPos(vec2 pos) {
        curPos = pos;
    }

protected:
    bool isActive;
    int abilityDuration;
    int currentTime;
    // number of times player is allowed to use the ability
    int numCharges;
    vec2 mousePos;
    vec2 curPos;
    AbilityType abilityType;
    float curRotation;
};


#endif //ATTACKATLANTIS_ABILITYCOMPONENT_HPP
