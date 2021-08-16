#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <SDL.h>
#include <SDL_image.h>

#include "movement.h"

class GameObject {

public:

	/**
	 * Class Constructor
	 */
	GameObject();
	~GameObject();
	
	/**
	 * Updates and renders the game objects
	 * onto the screen after the user's move
	 * 
	 * @param animated In case the object has some sort of animation
	 * @param sourceRectangle source SDL_Rect struct
	 * @param destinationRectangle destination SDL_Rect struct
	 * @param speed Animation speed
	 * @param frames Number of frames that makes the animation
	 * 
	 * @return
	 */
	void updateRender(bool animated, SDL_Rect& sourceRectangle, SDL_Rect& destinationRectangle, int speed = 0, int frames = 0);

	virtual void printIdentity() { std::cout << "Game-Object" << std::endl; }

protected:
	
	Position position;
	SDL_Renderer* objectRenderer;
	SDL_Texture* objectTexture;

};



#endif