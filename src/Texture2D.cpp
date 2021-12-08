/*****************************************************
** Project: Cube Builder Game
** File: Texture2D.cpp
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Implementation of Texture2D.h
*****************************************************/

#include "Texture2D.h"

game::Texture2D::Texture2D() {}

game::Texture2D::~Texture2D() {}

game::TEXTURE_ERROR game::Texture2D::init() {
    glGenTextures(game::NUM_TEXTURES, textures);

    if (this->addTexture(WATER, water_file) != 1) {
        return WATER_FILE_NOT_FOUND;
    }
    if (this->addTexture(GRASS, grass_file) != 1) {
        return GRASS_FILE_NOT_FOUND;
    }
    if (this->addTexture(DESERT, desert_file) != 1) {
        return DESERT_FILE_NOT_FOUND;
    }
    if (this->addTexture(DIRT, dirt_file) != 1) {
        return DIRT_FILE_NOT_FOUND;
    }
    if (this->addTexture(ROCK, rock_file) != 1) {
        return ROCK_FILE_NOT_FOUND;
    }
    if (this->addTexture(ROAD, road_file) != 1) {
        return ROAD_FILE_NOT_FOUND;
    }
    if (this->addTexture(BRICK, brick_file) != 1) {
        return BRICK_FILE_NOT_FOUND;
    }
    if (this->addTexture(WOOD, wood_file) != 1) {
        return WOOD_FILE_NOT_FOUND;
    }
    if (this->addTexture(WALL, wall_file) != 1) {
        return WALL_FILE_NOT_FOUND;
    }
    if (this->addTexture(WOODLAND, woodland_file) != 1) {
        return WOODLAND_FILE_NOT_FOUND;
    }

    return TEXTURE_SUCCESS;
}

bool game::Texture2D::addTexture(unsigned int index, std::string file_path) {
    if (index < 0 || index >= game::NUM_TEXTURES) return 0;

    //  type; 0 == file not compatible, 1 == png, 2 == jpg, 3 == jpeg
    int type = 0;

    if (file_path.substr(file_path.size()-3, 3) == "png") {
        type = 1;
    }
    if (file_path.substr(file_path.size()-3, 3) == "jpg") {
        type = 2;
    }
    if (file_path.substr(file_path.size()-4, 4) == "jpeg") {
        type = 3;
    }


    glBindTexture(GL_TEXTURE_2D, textures[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrchannels;

    auto data = stbi_load(file_path.c_str(), &width, &height, &nrchannels, 0);
    if (data) {
        if (type == 1) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
        } else if (type == 2 || type == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "type of data file for texture not found\n";
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load " << file_path << "\n";
        return 0;
    }
    stbi_image_free(data);

    return 1;
}

bool game::Texture2D::bind(unsigned int index) {
    if (index < 0 || index >= game::NUM_TEXTURES) {
        return false;
    } else {
        glBindTexture(GL_TEXTURE_2D, textures[index]);
        return true;
    }
}

void game::Texture2D::deleteTextures() {
    glDeleteTextures(game::NUM_TEXTURES, textures);
}
