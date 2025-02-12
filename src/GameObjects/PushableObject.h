//
// Created by 44749 on 21/04/2023.
//

#ifndef SFMLGAME_PUSHABLEOBJECT_H
#define SFMLGAME_PUSHABLEOBJECT_H

#include "GameObject.h"
#include "../Other/AnimationHelper.h"

class PushableObject : public GameObject
{
 public:
  PushableObject(std::string filename, sf::Vector2f pos);

  void init() override;
  void update(float dt) override;
  void move(float x, float y, float dt, float max_velocity, float min_velocity, float acceleration, float deceleration);

 private:
  sf::IntRect frame;

};

#endif // SFMLGAME_PUSHABLEOBJECT_H
