#include "gate.h"
#include "texture_manager.h"

Gate::Gate(const Position &position, SDL_Renderer* renderer, const char* textureSheet)
{
    
    objectTexture = TextureManager::LoadTexture(textureSheet, renderer);
    this->objectRenderer = renderer;
    this->position = position;
}

/******************************************************************************/

Position Gate::getPosition() const
{
    return position;
}