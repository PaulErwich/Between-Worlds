//
// Created by MLG Erwich on 02/03/2023.
//

#include "GameLevelSelect.h"

GameLevelSelect::GameLevelSelect()
{
  state = State::GAME_LEVEL_SELECT;
}

GameLevelSelect::GameLevelSelect(State _state, GameData& _game_data) :
  GameStateBase(_state, _game_data)
{

}

bool GameLevelSelect::init()
{
  return GameStateBase::init();
}
void GameLevelSelect::onEnter()
{
  GameStateBase::onEnter();
}
void GameLevelSelect::onExit()
{
  GameStateBase::onExit();
}
void GameLevelSelect::keyboard_input(sf::Event event)
{
  GameStateBase::keyboard_input(event);
}
void GameLevelSelect::mouse_input(sf::Event event)
{
  GameStateBase::mouse_input(event);
}
State GameLevelSelect::update(float dt)
{
  return GameStateBase::update(0);
}
void GameLevelSelect::render(sf::RenderWindow& window)
{
  GameStateBase::render(window);
}
