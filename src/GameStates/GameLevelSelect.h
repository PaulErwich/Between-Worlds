//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMELEVELSELECT_H
#define SFMLGAME_GAMELEVELSELECT_H

#include "GameStateBase.h"

class GameLevelSelect : public GameStateBase
{
 public:
  GameLevelSelect();
  GameLevelSelect(State _state, GameData& _game_data);

  bool init() override;
  void onEnter() override;
  void onExit() override;
  void keyboard_input(sf::Event event) override;
  void mouse_input(sf::Event event) override;
  State update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
};

#endif // SFMLGAME_GAMELEVELSELECT_H
