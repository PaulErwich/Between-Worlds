//
// Created by MLG Erwich on 02/03/2023.
//

#include "GameStateBase.h"

GameStateBase::GameStateBase()
{
  state = State::GAME_UNKNOWN;
  game_data = nullptr;
}

GameStateBase::GameStateBase(State _state, GameData& _game_data) : state(_state), game_data(&_game_data)
{

}

GameStateBase::~GameStateBase()
{
  game_data = nullptr;
}

bool GameStateBase::init()
{
  return true;
}

void GameStateBase::onEnter()
{

}

void GameStateBase::onExit()
{

}

void GameStateBase::keyboard_input(sf::Event)
{

}

void GameStateBase::keyboard_release(sf::Event)
{

}

void GameStateBase::mouse_input(sf::Event)
{

}

State GameStateBase::update(float dt)
{
  return state;
}

void GameStateBase::render(sf::RenderWindow& window)
{

}
void GameStateBase::textEntered(sf::Event event)
{

}
bool GameStateBase::collidingWithBox(sf::RectangleShape& shape, sf::Vector2i mouse_pos)
{
  if (shape.getPosition().x < mouse_pos.x && mouse_pos.x < shape.getPosition().x + shape.getGlobalBounds().width)
  {
    if (shape.getPosition().y < mouse_pos.y && mouse_pos.y < shape.getPosition().y + shape.getGlobalBounds().height)
    {
      return true;
    }
  }
  return false;
}

