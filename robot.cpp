#include "robot.h"

int Robot::robotCounter = 0;

Robot::Robot(const Position &position, SDL_Renderer* renderer, const char* textureSheet)
{
    objectTexture = TextureManager::LoadTexture(textureSheet, renderer);
    this->objectRenderer = renderer;
    this->position = position;
    this->id = robotCounter++;
    this->symbol = 'R';
}

/******************************************************************************/

SDL_Rect& Robot::getSourceRectangle()
{
    return sourceRectangle;
}

/******************************************************************************/

void Robot::setTexture(const char* textureSheet)
{
    objectTexture = TextureManager::LoadTexture(textureSheet, objectRenderer);
}

/******************************************************************************/

SDL_Rect& Robot::getDestinationRectangle()
{
    return destinationRectangle;
}

/******************************************************************************/

int Robot::getID() const
{
    return id;
}

/******************************************************************************/

char Robot::getSymbol() const
{
    return symbol;
}

/******************************************************************************/

int Robot::getRow() const
{
    return position.row;
}

/******************************************************************************/

int Robot::getCol() const
{
    return position.col;
}

/******************************************************************************/

Position Robot::getPosition() const
{
    return position;
}

/******************************************************************************/

bool Robot::isAlive() const
{
    if(alive)
        return true;
    else
        return false;
}

/******************************************************************************/

void Robot::setRow(int row)
{
    position.row = row;
}

/******************************************************************************/

void Robot::setCol(int col)
{
    position.col = col;
}

/******************************************************************************/

void Robot::seekHuman(const Position &playerPos)
{

    // When updating robots' places, we need to make sure
    // that they follow the shortest path possible to the human.
    // To do so, we first need to check if moving in a diagonal
    // would benefit the robot, as it covers more space.

    if (position.row > playerPos.row && position.col > playerPos.col)
    {
        setRow(position.row - 1);
        setCol(position.col - 1);
    }

    else if (position.row < playerPos.row && position.col < playerPos.col)
    {
        setRow(position.row + 1);
        setCol(position.col + 1);
    }

    else if (position.row > playerPos.row && position.col < playerPos.col)
    {
        setRow(position.row - 1);
        setCol(position.col + 1);
    }

    else if (position.row < playerPos.row && position.col > playerPos.col)
    {
        setRow(position.row + 1);
        setCol(position.col - 1);
    }

    else if (position.row > playerPos.row)
    {
        setRow(position.row - 1);
    }

    else if (position.row < playerPos.row)
    {
        setRow(position.row + 1);
    }
    
    else if (position.col > playerPos.col)
    {
        setCol(position.col - 1);
    }

    else if (position.col < playerPos.col)
    {
        setCol(position.col + 1);
    }
    
}

/******************************************************************************/

void Robot::setPosition(const Position &pos)
{
    this->position.row = pos.row;
    this->position.col = pos.col;
}

/******************************************************************************/

void Robot::setAsDead()
{
    alive = false;
    symbol = 'r';
}