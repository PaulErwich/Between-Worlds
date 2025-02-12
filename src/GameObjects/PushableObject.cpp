//
// Created by 44749 on 21/04/2023.
//
#include "PushableObject.h"
#include <cmath>

PushableObject::PushableObject(
  std::string filename, sf::Vector2f pos) :
  GameObject(filename, pos)
{
  frame = sf::IntRect(96, 64, 64, 64);
  sprite->setTextureRect(frame);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  setMin();
  calculateMax();
}

void PushableObject::init()
{

}

void PushableObject::update(float dt)
{
  setMin();
  calculateMax();
}

void PushableObject::move(
  float x, float y, float dt, float max_velocity, float min_velocity,
  float acceleration, float deceleration)
{
  velocity.x *= deceleration;
  if (std::abs(velocity.x) < min_velocity)
  {
    velocity.x = 0.f;
  }
  sprite->move(velocity * dt);

  velocity.x += x * acceleration;

  if (std::abs(velocity.x) > max_velocity)
  {
    velocity.x = max_velocity * ((velocity.x < 0.f) ? -1.f : 1.f);
  }
}
