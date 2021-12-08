/*****************************************************
** Project: Cube Builder Game
** File: Texture2D.h
** Author: Luke Leontowich
** Date: September 10, 2021
** Description: Stores and initializes textures. Second
** version of Texture
*****************************************************/

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Texture.h"

namespace game {

class Texture2D {
private:
    //  Stores the game Textures
    unsigned int textures[game::NUM_TEXTURES];

    //  Add a texture image to a position in the textures array
    bool addTexture(unsigned int index, std::string file_path);

public:
    /**  Constructor  **/
    Texture2D();

    /**  Desctructor  **/
    ~Texture2D();

    /** init()
    ** @param none
    ** @return game::TEXTURE_ERROR
    ** Description: Initializes the game textures
    **/
    game::TEXTURE_ERROR init();

    /** bind()
    ** @param unsigned int
    ** @return bool
    ** Description: binds a texture to be drawn
    **/
    bool bind(unsigned int index);

    /** deleteTextures
    ** @param none
    ** @return void
    ** Description: deallocate the memory
    **/
    void deleteTextures();
};

}
#endif // TEXTURE2D_H
