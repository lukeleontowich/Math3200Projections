/*****************************************************
** Project: Math 3200 Project
** File: Mesh.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: **
** This class is from learnopengl.com. I made a few changes so
** it would work with this project
** see https://learnopengl.com/Model-Loading/Mesh
** for more information.
*****************************************************/

#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <string>
#include <vector>

namespace game {

    typedef struct {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 textcor;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    } VertexData;

    typedef struct {
        unsigned int id;
        std::string type;
        std::string path;
    } TextureData;



    class Mesh {
    private:
        unsigned int _vbo, _ebo, _vao;
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
        std::vector<TextureData> textures;

        void init();

    public:
        explicit Mesh(std::vector<game::VertexData> vertices,
                      std::vector<unsigned int> indices,
                      std::vector<game::TextureData> textures);
        ~Mesh();
        void draw(game::Shader& shader);

        //  Getters
        unsigned int vbo() {return _vbo;}
        void destroyMesh();
    };
}

#endif // MESH_H
