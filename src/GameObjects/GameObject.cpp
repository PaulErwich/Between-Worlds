//
// Created by perwi on 03/03/2023.
//

#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const std::string& filename, sf::Vector2f pos)
{

  /// Initialise the sprite
  sprite = std::make_unique<sf::Sprite>();

  // If there is a filename then create a texture and load it into the sprite
  if (!filename.empty())
  {
    texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename)){
      std::cout << "Failed to load: " + filename << std::endl;
    }
    sprite->setTexture(*texture);
  }

  sprite->setPosition(pos);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  setMin();
  calculateMax();

}

void GameObject::init() {}
void GameObject::update(float dt)
{

}

void GameObject::render(sf::RenderWindow& window)
{
  if (visible && sprite != nullptr)
  {
    window.draw(*sprite);
  }
}

void GameObject::calculateMax()
{
  max.x = min.x + width;
  max.y = min.y + height;
}

bool GameObject::AABBCollision(GameObject& collider) const
{
  if (max.x <= collider.min.x || min.x >= collider.max.x) return false;
  if (max.y <= collider.min.y || min.y >= collider.max.y) return false;

  return true;
}

Side GameObject::sideCollision(GameObject& collider) const
{
  sf::Vector2f aMin = min;
  sf::Vector2f aMax = max;

  sf::Vector2f bMin = collider.min;
  sf::Vector2f bMax = collider.max;

  float x_pen = 0, y_pen = 0;
  bool right = false, bottom = false;

  if (bMin.x < aMin.x && aMin.x < bMax.x)
  {
    x_pen = bMax.x - aMin.x;
    right = true;
  }
  else
  {
    x_pen = aMax.x - bMin.x;
  }

  if (bMin.y < aMin.y && aMin.y < bMax.y)
  {
    y_pen = bMax.y - aMin.y;
    bottom = true;
  }
  else
  {
    y_pen = aMax.y - bMin.y;
  }

  if (x_pen == 0 || y_pen == 0)
  {
    return Side::NONE;
  }
  else
  {
    if (x_pen < y_pen)
    {
      if (right)
      {
        return Side::RIGHT;
      }
      return Side::LEFT;
    }
    else
    {
      if (bottom)
      {
        return Side::BOTTOM;
      }
      return Side::TOP;
    }
  }
}

void GameObject::setPosition(sf::Vector2f _pos)
{
  sprite->setPosition(_pos);
  setMin();
  calculateMax();
}

void GameObject::setPosition(float x, float y)
{
  sprite->setPosition(x, y);
  setMin();
  calculateMax();
}

