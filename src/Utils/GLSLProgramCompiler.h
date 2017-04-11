#ifndef GKOM_INTRO_GLSLPROGRAMCOMPILER_H
#define GKOM_INTRO_GLSLPROGRAMCOMPILER_H

#include <GL/glew.h>
#include <cstdlib>
#include <cstring>

class GLSLProgramCompiler {
private:
    static std::string readShaderCode(const GLchar* shaderPath);

    static GLuint compileShader(const GLchar* shaderCode, GLenum shaderType);

public:
    static GLuint fromFiles(std::string vertexShaderFile, std::string fragmentShaderFile);
};


#endif //GKOM_INTRO_GLSLPROGRAMCOMPILER_H
