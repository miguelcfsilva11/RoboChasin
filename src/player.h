#ifndef PLAYER_H
#define PLAYER_H

#include "movement.h"
#include "game_object.h"

#include <SDL.h>
#include <SDL_image.h>

class Player : public GameObject {

public:

    /**
     * Default Player constructor.
     */
    Player();


    /**
     * Class Constructor
     *
     * @param position A Position struct representing the player's coordinates in the maze 
     */
    Player(const Position &position, SDL_Renderer* renderer, const char* textureSheet);

    void printIdentity() { std::cout << "Player" << std::endl; }

    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    bool isAlive() const;
    void setAsDead();
    Position getPosition() const;
    void move(Movement delta);
    SDL_Rect& getSourceRectangle();
    SDL_Rect& getDestinationRectangle();

private:

    SDL_Rect sourceRectangle, destinationRectangle;

    bool alive = true;
    char symbol;

};

#endif