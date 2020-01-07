#ifndef MOVESYSTEM_H
#define MOVESYSTEM_H

#include <components/positionComponent.hpp>
#include <components/velocityComponent.hpp>
#include <entities/movable.hpp>
#include "system.hpp"

class MoveSystem: public System {
	public:
		MoveSystem();
		~MoveSystem();

		// init a System
		bool init() override;

		void destroy() override;

        // bool addEntity(Movable* movable);

        // bool removeEntity(Entity* movable) override;

        void move(Movable *movingEntity);

        void update(float elapsedMs) override;

        void setBoundary(int width, int height);

    protected:
        // std::vector<Movable*> entities;
        int windowWidth;
        int windowHeight;

        void resetPosition(PositionComponent *position, VelocityComponent *velocity);

    bool shouldReverseDirection(const vec2 &currVelocity, const vec2 &originalDir) const;
};

#endif
