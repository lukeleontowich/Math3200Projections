/*****************************************************
** Project:Math 3200 Project
** File: Mesh.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description:  **
** Implementation of Mesh class
** See https://learnopengl.com/Model-Loading/Mesh
** for more information.
*****************************************************/

#include "Mesh.h"

game::Mesh::Mesh(std::vector<game::VertexData> v,
           std::vector<unsigned int> i,
           std::vector<game::TextureData> t) : vertices(v), indices(i), textures(t) {
    this->init();
}

game::Mesh::~Mesh() {}

void game::Mesh::init() {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(game::VertexData),
                 &vertices.at(0),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 &indices.at(0),
                 GL_STATIC_DRAW);

    //  Set attribute pointers
    //  vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(game::VertexData), (void*)0);

    //  vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(game::VertexData),
                          (void*)offsetof(game::VertexData, normal));

    //  vertex texture coorinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(game::VertexData),
                          (void*)offsetof(game::VertexData, textcor));

    //  vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(game::VertexData),
                          (void*)offsetof(game::VertexData, tangent));

    //  vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(game::VertexData),
                          (void*)offsetof(game::VertexData, bitangent));

    glBindVertexArray(0);

}

void game::Mesh::draw(game::Shader& shader) {
    //  Get correct textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        else if(name == "texture_normal")
            number = std::to_string(normalNr++);
        else if(name == "texture_height")
            number = std::to_string(heightNr++);

        glUniform1i(glGetUniformLocation(shader.id(), (name + number).c_str()), i);

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    //  Draw mesh
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void game::Mesh::destroyMesh() {
    glDeleteBuffers(1, &_ebo);
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
