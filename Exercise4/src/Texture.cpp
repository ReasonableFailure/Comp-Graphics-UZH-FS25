#include "Texture.h"

#include <iostream>
#include <cstring>

#define cimg_display 0
#include <CImg.h>

// Bonus Task
#include <vector>
#include <numeric>
#include <algorithm>
// END Bonus

using namespace cimg_library;


namespace cgCourse
{
    void Texture::loadFromFile(const std::string & _filename)
    {
        CImg<unsigned char> img(_filename.c_str());

        int channels = img.spectrum();
        size.x = img.width();
        size.y = img.height();

        img.permute_axes("cxyz");

        /*
		 *  TODO: generate the texture here:
		 *        - generate the texture handle and set the variable texhandle done
		 *        - bind the texture handle done
		 *        - set the min/mag filter parameter and if it works test if you
		 *          see a difference between GL_LINEAR, MIPMAP_LINEAR, NEAREST etc..
		 *        - set the texture wrap parameters
		 *        - set the texture data with glTexImage2D
		 *        - generate mipmaps
		 *        - unbind the texture handle (we do this to have a clean state when the
		 *          function is ending and no textures are bound after this call.)
		 *   Note that depending on the channels the a different kind of texture might be created, for 4 channels GL_RGBA, for 3 GL_RGB and for one GL_RED.
         *   Some operating systems might use GL_BGRA
		 */
        glGenTextures(1, &texhandle);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        if (img)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        // TODO END
    }

    // Bonus Task:
    void Texture::createBonus(int checkerSize) {

    }

    void Texture::createBonusSpecular(int checkerSize) {

    }

    void Texture::createBonusNormal(int checkerSize) {

    }
    // End Bonus Task

    const GLuint & Texture::getTexHandle() const
    {
        return texhandle;
    }
}