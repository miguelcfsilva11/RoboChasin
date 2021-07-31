#include "post.h"
#include "texture_manager.h"

Post::Post(const Position &position, char type, SDL_Renderer* renderer, const char* textureSheet)
{
    objectTexture = TextureManager::LoadTexture(textureSheet, renderer);
    this->objectRenderer = renderer;
    this->position = position;
    this->type = type;
}

/******************************************************************************/

int Post::getRow() const
{
    return position.row;
}

/******************************************************************************/

int Post::getCol() const
{
    return position.col;
}

/******************************************************************************/

char Post::getSymbol() const
{
    return type;
}

/******************************************************************************/

bool Post::isElectrified() const
{
    if(type == '*')
        return true;
    else
        return false;
}

/******************************************************************************/

Position Post::getPosition() const
{
    return position;
}

/******************************************************************************/

void Post::setTexture(const char* textureSheet)
{
    objectTexture = TextureManager::LoadTexture(textureSheet, objectRenderer);
}