#include "player.h"
#include "texture_manager.h"

Player::Player()

{
    this->position.row = 1;
    this->position.col = 1;
    this->symbol = 'H';

}

/******************************************************************************/

Player::Player(const Position &position, SDL_Renderer* renderer, const char* textureSheet)

{
    objectTexture = TextureManager::LoadTexture(textureSheet, renderer);
    this->objectRenderer = renderer;
    this->position = position;
    this->symbol = 'H';

}

/******************************************************************************/

SDL_Rect& Player::getSourceRectangle()
{
    return sourceRectangle;
}

/******************************************************************************/

SDL_Rect& Player::getDestinationRectangle()
{
    return destinationRectangle;
}

/******************************************************************************/

int Player::getRow() const {

    return position.row;

}

/******************************************************************************/

int Player::getCol() const {

    return position.col;

}

/******************************************************************************/

char Player::getSymbol() const {

    return symbol;

}

/******************************************************************************/

bool Player::isAlive() const {

    if (alive) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************/

void Player::setAsDead(){

    alive = false;
    symbol = 'h';

}

/******************************************************************************/

void Player::move(Movement delta){

    position.row += delta.dRow;
    position.col += delta.dCol;
    

}

/******************************************************************************/

Position Player::getPosition() const{
    return position;
}