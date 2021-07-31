#ifndef GATE_H
#define GATE_H

#include <SDL.h>
#include <SDL_image.h>

#include "movement.h"
#include "game_object.h"

class Gate : public GameObject{
public:

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the gate's coordinates in the maze 
     */
    Gate(const Position &position, SDL_Renderer* renderer, const char* textureSheet);

    
    Position getPosition() const;
};

#endif