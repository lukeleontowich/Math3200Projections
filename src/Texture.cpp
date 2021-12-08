#include "Texture.h"

Texture::Texture() {
    textures = new unsigned int[NUM_TEXTURES];
    glGenTextures(NUM_TEXTURES, textures);
}

Texture::~Texture() {
    if (textures != nullptr)
        delete [] textures;
}


int Texture::addTexture(std::string file_path) {
    //  check if we will exceed the max textures
    if (n + 1 >= NUM_TEXTURES)
        return 0;
    else {
        ++n;
    }

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


    glBindTexture(GL_TEXTURE_2D, textures[n]);
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

int Texture::bind(unsigned int index) {
    if (index < 0 || index >= n) {
        return 0;
    }
    glBindTexture(GL_TEXTURE_2D, textures[index]);
    return 1;
}


void Texture::destroy() {
    glDeleteTextures(NUM_TEXTURES, textures);
}

