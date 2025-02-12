//
// Created by perwi on 19/04/2023.
//

#include "Door.h"
#include <cmath>

Door::Door(sf::Texture& texture, int x, int y, int height) : enabled(true)
{
  for (int i = 0; i < height; i++)
  {
    if (i == std::floor(height / 2))
    {
      door_tiles.emplace_back(std::make_unique<Tile>(texture, x, y + i, 101, 0));
    }
    else
    {
      door_tiles.emplace_back(std::make_unique<Tile>(texture, x, y + i, 83, 0));
    }

  }

  collision_box = std::make_unique<GameObject>("", door_tiles[0]->getMin());
  collision_box->setWidth(40);
  collision_box->setHeight(40 * height);

  collision_box->setMin();
  collision_box->calculateMax();
}

void Door::enableDoor()
{
  enabled = true;
}

void Door::disableDoor()
{
  enabled = false;
}

GameObject& Door::getCollisionBox()
{
  return *collision_box;
}

void Door::update(float dt)
{
  if (enabled)
  {

  }
}

void Door::render(sf::RenderWindow& window)
{
  if (enabled)
  {
    for (auto& tile : door_tiles)
    {
      tile->render(window);
    }
  }
}