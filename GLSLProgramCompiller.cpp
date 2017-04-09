#include <fstream>
#include <sstream>
#include "GLSLProgramCompiler.h"


std::string GLSLProgramCompiler::readShaderCode(const GLchar* shaderPath) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    shaderFile.open(shaderPath);

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

GLuint GLSLProgramCompiler::compileShader(const GLchar* shaderCode, GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
        throw std::runtime_error(std::string("Shader compilation: ") + infoLog);
    }

    return shaderID;
}

GLuint GLSLProgramCompiler::fromFiles(std::string vertexShaderFile, std::string fragmentShaderFile) {
    std::string vertexCode = readShaderCode(vertexShaderFile.c_str());
    GLuint vertexID = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);

    std::string fragmentCode = readShaderCode(fragmentShaderFile.c_str());
    GLuint fragmentID = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);


    GLuint programID;
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);

    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(std::string("Shader linking: ") + infoLog);
    }

    return programID;
}
