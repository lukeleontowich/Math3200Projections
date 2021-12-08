/*****************************************************
** Project: Math 3200 Project
** File: Shader.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: The Shader class creates and compiles
** a shader. Must use init() function before using the
** shader.
*****************************************************/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

namespace game {

class Shader {
private:
    //  Shader id
    unsigned int _id;

    /** getCode()
    ** @param string: file path to shader code
    ** @return string: code in form of string
    ** Description: Gets the shader code from a file
    **/
    std::string getCode(std::string path);

    /** compiled()
    ** @param unsigned int, const char*: shader and error msg if error
    ** @return bool: true on successful compilation
    ** Description: Checks compile status, returns true if compilation was success
    **/
    bool compiled(unsigned int shader, const char* msg);

public:
    /**  Constructor  **/
    Shader();

    /**  Descructor  **/
    ~Shader();

    /**
    ** id()
    ** @param none
    ** @return unsigned int: shader id
    ** Description: returns the shader id
    **/
    unsigned int id() {return _id;}

    /** init()
    ** @param string, string,
    ** @return bool
    ** Description: Initializes the shader, compiles the vertex and fragment shader
    ** and links them
    **/
    bool init(std::string v_path, std::string f_path);

    /** deleteShader()
    ** @param none
    ** @return void
    ** Description: Deallocates the shader memory
    **/
    void deleteShader();

    /** use()
    ** @param none
    ** @return void
    ** Description: Call to use shader
    **/
    void use();

};
}
#endif // SHADER_H
