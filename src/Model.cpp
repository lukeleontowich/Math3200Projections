/*****************************************************
** Project: Math 3200 Project
** File: Model.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of Model.h
** See https://learnopengl.com/Model-Loading/Model
** for more information
*****************************************************/


#include "Model.h"

game::Model::Model() {}

game::Model::~Model() {

}


void game::Model::init(const std::string& path) {

    Assimp::Importer importer;


    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |
                                     aiProcess_GenSmoothNormals |
                                     aiProcess_FlipUVs |
                                     aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Error with assimp " << importer.GetErrorString() << "\n";
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));


    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

// processes a node in a recursive fashion. Processes each individual mesh
// located at the node and repeats this process on its children nodes (if any).
void game::Model::processNode(aiNode* node, const aiScene* scene) {
    // process each mesh located at the current node

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).

        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {

        processNode(node->mChildren[i], scene);
    }
}


game::Mesh game::Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    //  data to fill
    std::vector<game::VertexData> vertices;
    std::vector<unsigned int> indices;
    std::vector<game::TextureData> textures;


    //  Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

        game::VertexData temp;
        glm::vec3 vec;

        //  positions
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        temp.pos = vec;

        //  normals
        if (mesh->HasNormals()) {

            vec.x = mesh->mNormals[i].x;
            vec.y = mesh->mNormals[i].y;
            vec.z = mesh->mNormals[i].z;
            temp.normal = vec;
        }


        //  texture coordinates
        if (mesh->mTextureCoords[0]) {

            glm::vec2 text_cor;
            text_cor.x = mesh->mTextureCoords[0][i].x;
            text_cor.y = mesh->mTextureCoords[0][i].y;
            temp.textcor = text_cor;


            // tangent
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
            temp.tangent = vec;

            // bitangent
            vec.x = mesh->mBitangents[i].x;
            vec.y = mesh->mBitangents[i].y;
            vec.z = mesh->mBitangents[i].z;
            temp.bitangent = vec;

        } else {
            temp.textcor = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(temp);

    }

    //  Now go through all the mesh faces
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

        aiFace face = mesh->mFaces[i];
        //  get all the indices and store them
        for (unsigned int j = 0; j < face.mNumIndices; j++) {

            indices.push_back(face.mIndices[j]);
        }
    }

    //  process material
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // diffuse maps
    auto diffuse_maps = loadMaterialTextures(material,
                                                 aiTextureType_DIFFUSE,
                                                 "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    //  specular maps
    auto specular_maps = loadMaterialTextures(material,
                                              aiTextureType_SPECULAR,
                                              "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    //  normal maps
    auto normal_maps = loadMaterialTextures(material,
                                            aiTextureType_HEIGHT,
                                            "texture_normal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

    //  Height maps
    auto height_maps = loadMaterialTextures(material,
                                            aiTextureType_AMBIENT,
                                            "texture_height");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());
    return Mesh(vertices, indices, textures);
}


std::vector<game::TextureData> game::Model::loadMaterialTextures(aiMaterial* mat,
                                                                 aiTextureType type,
                                                                 std::string type_name){
    std::vector<game::TextureData> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            game::TextureData texture;
            texture.id = this->textureFromFile(str.C_Str());
            texture.type = type_name;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int game::Model::textureFromFile(const char* path) {
    std::string filename = std::string(path);
    filename = this->directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else
            format = GL_RGB;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void game::Model::draw(game::Shader& shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}

void game::Model::destroyModel() {
    for (auto it = meshes.begin(); it != meshes.end(); ++it) {
        (*it).destroyMesh();
    }
}
