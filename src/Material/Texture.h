//
// Created by wojciech on 13.04.17.
//

#ifndef GLPRESS_TEXTURE_H
#define GLPRESS_TEXTURE_H


#include <memory>
#include <GL/glew.h>

class Texture {
public:
    static std::shared_ptr<Texture> loadFromFile(GLuint id, std::string file);
private:
    Texture();
private:
    GLuint mID;
};


#endif //GLPRESS_TEXTURE_H
