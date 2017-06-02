//
// Created by wojciech on 13.04.17.
//

#include <SOIL/SOIL.h>
#include "Texture.h"

std::shared_ptr<Texture> Texture::loadFromFile(std::string file) {

    int width, height;
    unsigned char* image;
    GLuint texture;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image = SOIL_load_image(file.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr)
        throw std::runtime_error("Failed to load texture file: " + std::string(file));

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    return std::make_shared<Texture>(texture);
}

Texture::Texture(GLuint texture) : mTextureID(texture) { }

