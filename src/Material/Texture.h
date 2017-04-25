//
// Created by wojciech on 13.04.17.
//

#ifndef GLPRESS_TEXTURE_H
#define GLPRESS_TEXTURE_H


#include <memory>
#include <GL/glew.h>

class Texture {
public:
    static std::shared_ptr<Texture> loadFromFile(std::string file);

    Texture(GLuint texture);

    GLuint getID() { return mTextureID; };
private:
    GLuint mTextureID;
};


#endif //GLPRESS_TEXTURE_H
