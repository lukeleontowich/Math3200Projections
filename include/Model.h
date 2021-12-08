/*****************************************************
** Project: Math 3200 Project
** File: Model.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: This class stores the data for a model
** This class originates from learnopengl.com and is
** re-worked so it works for the purpose of this game
** see https://learnopengl.com/Model-Loading/Model
** for more information
*****************************************************/

#ifndef MODEL_H
#define MODEL_H


#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"

namespace game {

class Model {
public:
    Model();
    ~Model();

    void draw(Shader& shader);
    void destroyModel();
    void init(const std::string& path);

private:
    std::vector<game::TextureData> textures_loaded;
    std::vector<game::Mesh> meshes;
    std::string directory;


    void processNode(aiNode* node, const aiScene* scene);
    game::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<game::TextureData> loadMaterialTextures(aiMaterial* mat,
                                                        aiTextureType type,
                                                        std::string type_name);
    unsigned int textureFromFile(const char* path);

};

}
#endif // MODEL_H
