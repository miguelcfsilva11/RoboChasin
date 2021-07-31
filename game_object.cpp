#include "game_object.h"
#include "texture_manager.h"
#include <iostream>

GameObject::GameObject()
{
	
}


GameObject::~GameObject()
{

}

void GameObject::updateRender(bool animated, SDL_Rect& sourceRectangle, SDL_Rect& destinationRectangle, int speed, int frames)
{

	sourceRectangle.h = 50;
	sourceRectangle.w = 50;

	if (animated)
		sourceRectangle.x = 50 * static_cast<int>((SDL_GetTicks() / speed) % frames);
	else
		sourceRectangle.x = 0;

	sourceRectangle.y = 0;

	destinationRectangle.h = 50;
	destinationRectangle.w = 50;
	destinationRectangle.x = this->position.col * 50;
	destinationRectangle.y = this->position.row * 50;

	SDL_RenderCopy(objectRenderer, objectTexture, &sourceRectangle, &destinationRectangle);


}