//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMESTATEBASE_H
#define SFMLGAME_GAMESTATEBASE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "State.h"
#include "../Other/GameData.h"
#include "../Other/Helper.h"
#include "../Other/AnimationHelper.h"
#include "../Other/Helper.h"

class GameStateBase
{
 public:
  GameStateBase();
  GameStateBase(State _state, GameData& _game_data);
  ~GameStateBase();

  virtual bool init(); // To be called after object creation
  virtual void onEnter(); // To be called when entering the state
  virtual void onExit(); // To be called when exiting the state
  virtual void keyboard_input(sf::Event); // To be called to process inputs for the state
  virtual void keyboard_release(sf::Event);
  virtual void mouse_input(sf::Event); // To be called to process inputs for the state
  virtual State update(float dt); // To be called to update objects in the state
  virtual void render(sf::RenderWindow& window); // To be called to render objects in the state
  virtual void textEntered(sf::Event event); // When a message is typed



 protected:
  static bool collidingWithBox(sf::RectangleShape& shape, sf::Vector2i mouse_pos);

  State state; // The state of the implementation
  GameData* game_data; // A pointer to the central GameData object

};

#endif // SFMLGAME_GAMESTATEBASE_H
