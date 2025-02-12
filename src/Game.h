
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#include "GameStates/State.h"
#include "GameStates/GameStateBase.h"
#include "Other/GameData.h"

#include "LevelLoading/LevelData.h"
#include "GameObjects/Collectible.h"

#include "Networking/Client.h"
#include "Networking/Server.h"

#include "GameObjects/Character.h"
#include "Camera/Camera.h"
#include "GameObjects/PushableObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game() = default;
  bool init();
  void update(float dt);
  void render();
  void keyboard_input(sf::Event event);
  void keyboard_released(sf::Event event);
  void mouse_input(sf::Event event);

  void textEntered(sf::Event event);

  void shutServer();

 private:
  sf::RenderWindow& window;

  std::map<State, std::unique_ptr<GameStateBase>> game_states;
  std::shared_ptr<GameData> game_data;

  std::unique_ptr<LevelData> level_test;

  //Character
  std::unique_ptr<Character> player_one;
  std::unique_ptr<Character> player_two;
};

#endif // PLATFORMER_GAME_H
