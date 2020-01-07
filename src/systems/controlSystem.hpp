#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H


// not sure if we need the system
// put in first

#include "common.hpp"
#include "system.hpp"
#include <entities/movable.hpp>

class ControlSystem: public System {
	public:
		ControlSystem();
		~ControlSystem();

		// init a System
		bool init() override;

		void destroy() override;

        // bool addEntity(Entity* entity);

        // bool removeEntity(Entity* entity) override;

        void update(float elapsedMs) override;

        void setVelocity(float v);

        bool checkIsControl(Entity* controlObj);

        void setKeyEffect(int key, int action);

        void setMouseButtonEffect(int button, int action);

        void setMousePos(vec2 pos);

        void setPos(vec2 pos);

        bool* getKeyPress();

        bool isAbilitiesActive(HasAbility* abilityEntity);

    void stopMoving();

private:
        // std::vector<Entity*> entities;
        enum {UP, DOWN, LEFT, RIGHT};
        bool* isKeyPressed;
        float velocity;
        vec2 mousePos;
        vec2 curpos;
};

#endif