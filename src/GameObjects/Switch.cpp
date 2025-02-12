//
// Created by perwi on 10/03/2023.
//

#include "Switch.h"
Switch::Switch(const std::string& filename, sf::Vector2f pos) :
  PuzzlePiece(filename, pos)
{
  // Here
}

void Switch::init()
{
  sprite->setTextureRect(rect_not_active);

  sprite->setScale(4, 4);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  setMin();
  calculateMax();
}

void Switch::activate()
{
  active = true;
  sprite->setTextureRect(rect_active);

  linked_door->disableDoor();
}

void Switch::deactivate()
{
  active = false;
  sprite->setTextureRect(rect_not_active);

  linked_door->enableDoor();
}

void Switch::update(float dt)
{

}
