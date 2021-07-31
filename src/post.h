#ifndef POST_H
#define POST_H

#include <SDL.h>
#include <SDL_image.h>

#include "movement.h"
#include "game_object.h"

class Post : public GameObject {
public:

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the post's coordinates in the maze
     * @param type specifies whether a fence is electrified or not
     */
    Post(const Position &position, char type, SDL_Renderer* renderer, const char* textureSheet);
    
    int getRow() const;
    int getCol() const;
    Position getPosition() const;
    char getSymbol() const;
    bool isElectrified() const;
    void setTexture(const char* textureSheet);

private:
    char type;
};

#endif