#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>

class TextureManager {
public:

    /**
	 * Loads the object's texture
	 * 
	 * @return The object's texture
	 */
	static SDL_Texture* LoadTexture(const char* textureName, SDL_Renderer* renderer);
};


#endif