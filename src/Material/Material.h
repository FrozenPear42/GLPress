#ifndef GKOM_INTRO_MATERIAL_H
#define GKOM_INTRO_MATERIAL_H

#include <cstdlib>
#include <string>
#include <memory>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "Texture.h"

class Material {
    friend class Renderer;

private:
    bool mMapping;
    glm::vec4 mDiffuseColor;
    std::shared_ptr<Texture> mDiffuseMap;
    std::shared_ptr<Texture> mNormalMap;
    std::shared_ptr<Texture> mSpecularMap;
    GLfloat mOpacity;
    GLfloat mShiness;
public:
    Material() :
            mMapping(false), mDiffuseColor(glm::vec4(1, 1, 1, 1)), mOpacity(1.0) {};

    Material(std::shared_ptr<Texture> diffuse) :
            mMapping(true), mDiffuseMap(diffuse), mOpacity(1.0) {};

    Material(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> normal) :
            mMapping(true), mDiffuseMap(diffuse), mNormalMap(normal), mOpacity(1.0) {};


    void enableMapping(bool mapping) { mMapping = mapping; };

    void setDiffuseMap(std::shared_ptr<Texture>& texture) {
        mMapping = true;
        mDiffuseMap = texture;
    }

    void setNormalMap(std::shared_ptr<Texture>& texture) {
        mMapping = true;
        mNormalMap = texture;
    }

    void setSpecularMap(std::shared_ptr<Texture>& texture) {
        mMapping = true;
        mSpecularMap = texture;
    }

    void setDiffuseColor(glm::vec4 color) {
        mMapping = true;
        mDiffuseColor = color;
    }

    GLfloat getOpacity() { return mOpacity; }

    void setOpacity(GLfloat opacity) { mOpacity = opacity; }


};

#endif //GKOM_INTRO_MATERIAL_H
