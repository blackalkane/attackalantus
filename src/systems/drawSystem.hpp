#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include <entities/drawable.hpp>
#include "system.hpp"
#include "common.hpp"


class DrawSystem: public virtual System {
	public:
		DrawSystem();
		~DrawSystem();

		// init a System
		bool init()override;

		void destroy()override;

		// bool addEntity(Entity* entity)override;

		// bool removeEntity(Entity* entity)override;

		void update(float elapsedMs) override;

		void draw(DrawComponent* drawingObject, PositionComponent* position, const mat3& projection);

		void setProjection(int w, int h, float scale);

		struct Transform {
			mat3 out;

			void begin();
			void scale(vec2 scale);
			void rotate(float radians);
			void translate(vec2 offset);
			void end();
		} transform;

    std::vector<Entity*> *getEntityListPointer();

protected:
		// std::vector<Drawable*> entities;
        mat3 projection_2D;

        void drawUpdateBeforeDraw(PositionComponent *position, DrawComponent *drawingObject, Drawable* drawEntity);
};

#endif
