#include "texture_manager.h"

SDL_Texture* TextureManager::LoadTexture(const char* textureName, SDL_Renderer* renderer)
{
	SDL_Surface* temporarySurface = IMG_Load(textureName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
	SDL_FreeSurface(temporarySurface);

	return texture;
}