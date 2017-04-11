//
// Created by wojciech on 09.04.17.
//

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <stdexcept>
#include "Utils.h"

GLuint Utils::mipmapTextureFromFile(GLuint textureID, const char* file) {
    int width, height;
    unsigned char* image;
    GLuint texture;

    image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr)
        throw std::runtime_error("Failed to load texture file: " + std::string(file));

    glGenTextures(1, &texture);
    glActiveTexture(textureID);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    return texture;
}
