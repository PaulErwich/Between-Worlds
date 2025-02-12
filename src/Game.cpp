
#include "Game.h"

#include "GameStates/GameMenu.h"
#include "GameStates/GameLobby.h"
#include "GameStates/GameLevelSelect.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GameWin.h"
#include "GameStates/GameOver.h"

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));

  player_one = std::make_unique<Character>("Data/Images/FullSpriteBlue.png", sf::Vector2f(100.f, 400.f), window);
  player_two = std::make_unique<Character>("Data/Images/FullSpriteRed.png", sf::Vector2f{50.f, 20.f}, window);

  // Create instance of GameData
  game_data = std::make_unique<GameData>();
  game_data->window = &window;

  game_data->players[ControlledPlayer::PLAYER_ONE] = &*player_one;
  game_data->players[ControlledPlayer::PLAYER_TWO] = &*player_two;

  game_data->client = std::make_unique<Client>(&*game_data);

  // Define starting state
  game_data->current_state = State::GAME_MENU;

  // Create instances of all the game states and put them into Map
  game_states[State::GAME_MENU] = std::make_unique<GameMenu>(State::GAME_MENU, *game_data);
  game_states[State::GAME_LOBBY] = std::make_unique<GameLobby>(State::GAME_LOBBY, *game_data);
  game_states[State::GAME_LEVEL_SELECT] = std::make_unique<GameLevelSelect>(State::GAME_LEVEL_SELECT, *game_data);
  game_states[State::GAME_PLAY] = std::make_unique<GamePlay>(State::GAME_PLAY, *game_data);
  game_states[State::GAME_WIN] = std::make_unique<GameWin>(State::GAME_WIN, *game_data);
  game_states[State::GAME_OVER] = std::make_unique<GameOver>(State::GAME_OVER, *game_data);


}

bool Game::init()
{
  for (auto& state : game_states)
  {
    if (!state.second->init())
    {
      std::cout << "State didn't load properly\n";
      return false;
    }
  }
  return true;
}

void Game::update(float dt)
{
  //game_data->window = &window;
  State prev_state = game_data->current_state;
  game_data->current_state = game_states[game_data->current_state]->update(dt);

  if (game_data->received_state_change)
  {
    game_data->current_state = game_data->received_state;
    game_data->received_state_change = false;
  }

  if (game_data->current_state != prev_state)
  {
    if (game_data->current_state == State::GAME_EXIT)
    {
      shutServer();
      window.close();
      return;
    }
    else
    {
      game_states[prev_state]->onExit();
      game_states[game_data->current_state]->onEnter();
    }
  }
  //Character

}

void Game::render()
{
  game_states[game_data->current_state]->render(window);
}

void Game::keyboard_input(sf::Event event)
{
  game_states[game_data->current_state]->keyboard_input(event);

  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  game_data->client->input(event);
}

void Game::keyboard_released(sf::Event event)
{
  game_states[game_data->current_state]->keyboard_release(event);
}

void Game::mouse_input(sf::Event event)
{
  game_states[game_data->current_state]->mouse_input(event);
}

void Game::shutServer()
{
  if (game_data->server != nullptr)
  {
    game_data->server->shutdownServer();
  }
}
void Game::textEntered(sf::Event event)
{
  game_states[game_data->current_state]->textEntered(event);
}


