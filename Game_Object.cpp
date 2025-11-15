#include "Game_Object.h"

bool Game_Object::getIsActive()
{
    return this->is_active;
}

void Game_Object::setToActive()
{
    this->is_active = true;
}

void Game_Object::deactivate()
{
    this->is_active = false;
}

Game_Object::type Game_Object::getType()
{
    return this->object_type;
}
