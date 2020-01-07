//
// Created by Andy He on 2019-12-06.
//

#include "particleEffectSystem.hpp"

void ParticleEffectSystem::update(float elapsedMs) {
    for (Entity* entity: entities) {
        FireLittleParticle* p = dynamic_cast<FireLittleParticle*>(entity);
        int current_t = p->getDrawComponent()->getCurrentFrame() % p->getDrawComponent()->getTotalFrame();
        // function 1/33(x - 18)^2 + 10 or 1/33(x + 18)^2 + 10

        vec2 origin = p->getStartPosition();
        float off_x = (float) current_t;
        float off_y = (float) ((current_t - 18) * (current_t - 18)) / 33.0 - 10.0;
        if (p->getDirection()) {
            off_x = -off_x;
        }

        vec2 new_pos = {origin.x + off_x, origin.y + off_y};
//        printf("%f, %f, %d\n", off_x, off_y, current_t);
        p->getPositionComponent()->setPosition(new_pos);
    }

}
