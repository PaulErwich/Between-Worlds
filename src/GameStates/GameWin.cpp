//
// Created by MLG Erwich on 02/03/2023.
//

#include "GameWin.h"

GameWin::GameWin()
{
  state = State::GAME_WIN;
}

GameWin::GameWin(State _state, GameData& _game_data) :
  GameStateBase(_state, _game_data)
{

}

bool GameWin::init()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Failed to load font";
    return false;
  }
  if (!backgroundTexture.loadFromFile("Data/Images/win.png"))
  {
    std::cout << "Failed to load Game Over background";
    return false;
  }
  background_.setTexture(backgroundTexture);
  middleX = game_data->window->getSize().x * 0.5f;
  middleY = game_data->window->getSize().y * 0.5f;

  Helper::Generate(winText_, "You Win!", font, sf::Color::White,sf::Vector2f(0,0), 120);
  winText_.setPosition(middleX - (winText_.getPosition().x + winText_.getGlobalBounds().width * 0.5f), 60.0f);
  winText_.setOutlineColor(sf::Color::Black);
  winText_.setOutlineThickness(2.0f);
  classTexts.push_back(winText_);

  Helper::Generate(playAgainText, "Play Again", font, sf::Color::White, sf::Vector2f(0, 0), 40);
  playAgainText.setPosition(middleX - (playAgainText.getPosition().x + playAgainText.getGlobalBounds().width * 0.5f),
                            middleY - (playAgainText.getPosition().y + playAgainText.getGlobalBounds().height * 0.5f));
  playAgainText.setOutlineColor(sf::Color::Black);
  playAgainText.setOutlineThickness(2.0f);
  classTexts.push_back(playAgainText);

  Helper::Generate(exitText, "Exit", font, sf::Color::White, sf::Vector2f(0, 0), 40);
  exitText.setPosition(middleX - (exitText.getPosition().x + exitText.getGlobalBounds().width * 0.5f),
                            middleY - (exitText.getPosition().y + exitText.getGlobalBounds().height * 0.5f) + (playAgainText.getPosition().y * 0.3f));
  exitText.setOutlineColor(sf::Color::Black);
  exitText.setOutlineThickness(2.0f);
  classTexts.push_back(exitText);

  Helper::Generate(selectionSprite, selectionTexture, "Data/Images/selection.png", sf::Vector2f(-100,-100), sf::Vector2f(0.3f,0.3f));


  return GameStateBase::init();
}
void GameWin::onEnter()
{
  state = State::GAME_WIN;
  GameStateBase::onEnter();
}
void GameWin::onExit()
{
  GameStateBase::onExit();
}
void GameWin::keyboard_input(sf::Event event)
{
  GameStateBase::keyboard_input(event);
}
void GameWin::mouse_input(sf::Event event)
{
  // Hoover
  if (Helper::InsideText(event, playAgainText))
  {
    selectionSprite.setScale(sf::Vector2f(0.38f, 0.38f));
    selectionSprite.setPosition(playAgainText.getPosition() + sf::Vector2f(0, 55.f));
  }
  else if (Helper::InsideText(event, exitText))
  {
    selectionSprite.setScale(sf::Vector2f(0.15f, 0.3f));
    selectionSprite.setPosition(exitText.getPosition() + sf::Vector2f(0, 55.f));
  }
  else
  {
    selectionSprite.setPosition(sf::Vector2f(-100, -100.f));
  }

  // Clicked
  if (Helper::ClickedOnText(event, playAgainText))
  {
    state = State::GAME_PLAY;
    //game_data->current_state = State::GAME_PLAY;
    game_data->client->sendStateUpdate(State::GAME_PLAY);
  }
  else if (Helper::ClickedOnText(event, exitText))
  {
    game_data->window->close();
  }

  GameStateBase::mouse_input(event);
}
State GameWin::update(float dt)
{
  return state;
}
void GameWin::render(sf::RenderWindow& window)
{
  window.draw(background_);
  window.draw(selectionSprite);
  for (auto & text : classTexts)
  {
    window.draw(text);
  }
  GameStateBase::render(window);
}
