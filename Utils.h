#ifndef GKOM_INTRO_UTILS_H
#define GKOM_INTRO_UTILS_H

#include <GL/gl.h>
#include <GL/glew.h>

class Utils {
public:
    static GLuint mipmapTextureFromFile(GLuint textureID, const char* file);
};


#endif //GKOM_INTRO_UTILS_H
