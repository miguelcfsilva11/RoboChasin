#ifndef ROBOT_H
#define ROBOT_H

#include <SDL.h>
#include <SDL_image.h>

#include "movement.h"
#include "game_object.h"
#include "texture_manager.h"


class Robot : public GameObject{

public:

    enum State { ALIVE, STUCK, DEAD };

    /**
     * Class Constructor
     *
     * @param position A Position struct representing the robot's coordinates in the maze 
     */
    Robot(const Position &position, SDL_Renderer* renderer, const char* textureSheet);

    void printIdentity() { std::cout << "Robot" << std::endl; }

    int getID() const;
    char getSymbol() const;
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
    Position getPosition() const;
    bool isAlive() const;

    /**
     * For every located robot, compare its
     * position to the human's and find
     * the most efficient path that leads to him.
     *
     * @param playerPos the human's position
     */
    void seekHuman(const Position &playerPos);

    void setPosition(const Position &pos);
    void setAsDead();
    void setTexture(const char* textureSheet);

    SDL_Rect& getSourceRectangle();
    SDL_Rect& getDestinationRectangle();

private:

    SDL_Rect sourceRectangle, destinationRectangle;

    static int robotCounter;
    int id;
    char symbol;
    bool alive = true;
};

#endif