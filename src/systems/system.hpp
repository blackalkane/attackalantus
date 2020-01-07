#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <entities/entity.hpp>

struct System {
    virtual bool init(){
        return true;
    };

    virtual void destroy() {
        entities.clear();
    }

    virtual void update(float elapsedMs) = 0;

    virtual bool addEntity(Entity* entity){
        entities.push_back(entity);
        return true;
    }

    virtual bool removeEntity(Entity* entity){
        int elementIndex = -1;
        for (int i = 0; i < entities.size(); i++){
            if (entities[i] == entity){
                elementIndex = i;
                // printf("delete");
                break;
                // free(entities[i]);
            }
        }
        if (elementIndex == -1){
            return false;
        }
        entities.erase(entities.begin() + elementIndex);
        return true;
    }

    virtual std::vector<Entity*> getEntityList() {
        return entities;
    }

protected:
    std::vector<Entity*> entities;
};

#endif
