/*****************************************************
** Project: Math 3200 Project
** File: Shader.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of Shader class
*****************************************************/

#include "Shader.h"

game::Shader::Shader() {}

game::Shader::~Shader() {}

bool game::Shader::init(std::string v_path, std::string f_path) {
    const char* vertex_code;
    const char* fragment_code;

    //  Get Code as strings
    std::string vertex_string = getCode(v_path);
    std::string fragment_string = getCode(f_path);

    //  convert to c-strings
    vertex_code = vertex_string.c_str();
    fragment_code = fragment_string.c_str();


    //  Check for errors
    bool errors = false;
    if (strcmp("ERROR", vertex_code) == 0) {
        std::cout << "Error Shader.h, Constructor.\n";
        std::cout << "Vertex shader file '" << v_path << "' not found\n";
        errors = true;
    }
    if (strcmp("ERROR", fragment_code) == 0) {
        std::cout << "Error Shader.h, Constructor.\n";
        std::cout << "Fragment shader file '" << f_path << "' not found\n";
        errors = true;
    }



    if (!errors) {
        //  Create vertex shader
        auto vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);

        //  Check for errors
        if (!compiled(vertex, "Vertex")) {
            std::cout << "Vertex shader compilation failed\n";
            return false;
        }


        //  Create fragment shader
        auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, NULL);
        glCompileShader(fragment);

        //  Check for errors
        if (!compiled(fragment, "fragment")) {
            std::cout << "Fragment shader compilation failed\n";
            return false;
        }


        //  Link shaders and create program
        _id = glCreateProgram();
        glAttachShader(_id, vertex);
        glAttachShader(_id, fragment);
        glLinkProgram(_id);

        //  Check for linking errors
        int success;
        char info_log[512];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(_id, 512, NULL, info_log);
            std::cout << "Error, Shader.h, Constructor.\n";
            std::cout << "Program linking failed\n";
            std::cout << info_log << "\n";
        }

        //  Delete Shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    return true;
}

void game::Shader::deleteShader() {
    glDeleteProgram(_id);
}

std::string game::Shader::getCode(std::string path) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(path);
    if (!file.is_open()) {
        return "ERROR";
    } else {
        //  Get contents of file
        buffer << file.rdbuf();

        //  close the file
        file.close();

        return buffer.str();
    }
}

bool game::Shader::compiled(unsigned int shader, const char* msg) {
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << msg;
        std::cout << " compilation failed\n";

        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cout << info_log << "\n";
        return false;
    }
    return true;
}

void game::Shader::use() {
    glUseProgram(_id);
}
