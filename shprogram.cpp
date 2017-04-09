#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include <GL/glew.h>
#include "shprogram.h"

string read_shader_code(const GLchar* shaderPath) {
    ifstream shader_file;
    shader_file.exceptions(ifstream::badbit);

    shader_file.open(shaderPath);
    stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    return shader_stream.str();
}

GLuint compile_shader(const GLchar* shaderCode, GLenum shaderType) {

    GLuint shader_id = glCreateShader(shaderType);
    glShaderSource(shader_id, 1, &shaderCode, NULL);
    glCompileShader(shader_id);

    // Print compile errors if any
    GLint success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader_id, sizeof(infoLog), NULL, infoLog);
        string msg = string("Shader compilation: ") + infoLog;
        throw runtime_error(msg.c_str());
    }
    return shader_id;
}

ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath) {

    string vertex_code = read_shader_code(vertexPath);
    GLuint vertex_id = compile_shader(vertex_code.c_str(), GL_VERTEX_SHADER);

    string fragment_code = read_shader_code(fragmentPath);
    GLuint fragment_id = compile_shader(fragment_code.c_str(), GL_FRAGMENT_SHADER);

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glBindFragDataLocation(program_id, 0, "color");

    glLinkProgram(program_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    GLint success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program_id, sizeof(infoLog), nullptr, infoLog);
        throw runtime_error(string("Shader program linking: ") + infoLog);
    }

}
