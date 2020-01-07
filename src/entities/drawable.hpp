#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <components/drawComponent.hpp>
#include <components/positionComponent.hpp>
#include "entity.hpp"

struct Drawable: public virtual Entity {
    virtual DrawComponent* getDrawComponent() = 0;

    virtual PositionComponent* getPositionComponent() = 0;

    virtual int getCurrentState() {
        return entityState.getState();
    }

    virtual void setState(int nextState) {
        entityState.setState(nextState);
    }

    virtual GameState* getStateObj() {
        return &entityState;
    }

    virtual void loadStateSprite() {
        // do nothing
    }

    virtual void updateStateFrame() {
        entityState.frameUpdate();
    }

    virtual int getPreFrameState() {
        return entityState.getPreFrameState();
    }

    static std::vector<Texture*> setSpriteTextures(const char* path, char* picType, int indexBegin, int size) {
        std::vector<Texture*> textures = {};
        for(int i = indexBegin; i < size + indexBegin; i++){
            std::string spritePath = path;
            spritePath.append(std::to_string(i) + "." + picType);

            Texture* curTexture = new Texture();
            if (!curTexture->load_from_file(spritePath)) {
                fprintf(stderr, "Failed to texture: %s\n", path);
                return {};
            }
            textures.push_back(curTexture);
        }
        return textures;
    }

    static Texture* setTexture(const std::string &path) {
        Texture* curTexture = new Texture();
        if (!curTexture->load_from_file(path)) {
            fprintf(stderr, "Failed to texture: %s\n", path.c_str());
            return {};
        }
        return curTexture;
    }

    virtual void emptyTextureVector(std::vector<Texture*> textures) {
        for(Texture* texture : textures) {
            free(texture);
        }
        textures.clear();
    }

    virtual void preloadTexture() = 0;

    GameState entityState;
};

#endif