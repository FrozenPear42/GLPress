//
// Created by wojciech on 31.05.17.
//

#ifndef GLPRESS_ANIMATIONMODELMATERIALSWAP_H
#define GLPRESS_ANIMATIONMODELMATERIALSWAP_H


#include "Animation.h"
#include "../Model/Model.h"
#include "../Material/Material.h"

class AnimationModelMaterialSwap : public Animation {
private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Material> mMaterial;
    std::shared_ptr<Material> mBaseMaterial;

public:
    AnimationModelMaterialSwap(std::shared_ptr<Model>& model, std::shared_ptr<Material>& targetMaterial) :
            Animation(0), mModel(model), mMaterial(targetMaterial) {}

    virtual void animationStart();

    virtual bool animationStep(GLfloat delta);

    virtual void animationReset();


};


#endif //GLPRESS_ANIMATIONMODELMATERIALSWAP_H
