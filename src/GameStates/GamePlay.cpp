//
// Created by MLG Erwich on 02/03/2023.
//

#include "GamePlay.h"

GamePlay::GamePlay()
{
  state = State::GAME_PLAY;
}



GamePlay::GamePlay(State _state, GameData& _game_data) :
  GameStateBase(_state, _game_data)
{

}

bool GamePlay::init()
{
  //test_switch->init();
  game_data->level_one = std::make_unique<LevelData>("Data/TileMaps/Platformer.tmx", *game_data->window);
  //level_test = std::make_unique<LevelData>("Data/TileMaps/Platformer - backup.tmx", *game_data->window);
  //level_test = std::make_unique<LevelData>("Data/TileMaps/Platformer.tmx", *game_data->window);
  //level_test = std::make_unique<LevelData>("Data/TileMaps/Platformer - backup.tmx", *game_data->window);

  camera = std::make_unique<Camera>("", sf::Vector2f(0, 0), game_data);
  portalBlue = std::make_unique<Portal>("Data/Images/portals.png", sf::Vector2f(0,0));
  portalBlue->setPosition(sf::Vector2f(86 * 40, 6 * 49));
  //portalRed = std::make_unique<Portal>("Data/Images/portals.png", sf::Vector2f(0,0));
  //portalRed->setPosition(sf::Vector2f(86 * 40, 6 * 83));

  loadAudio("Data/Sounds/death.wav");

  // init text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  //LIVES
  life_text2.setFont(font);
  life_text2.setCharacterSize(90);
  life_text2.setPosition(20, 30 );
  life_text2.setString("Lives :");
  life_text2.setFillColor(sf::Color::White);
  life_text.setString(std::to_string(life));
  life_text.setFont(font);
  life_text.setCharacterSize(70);
  life_text.setFillColor(sf::Color(255,20,20,200));
  life_text.setPosition(320, 50);

  //end_point = std::make_unique<GameObject>("Data/Images/pacman.png", sf::Vector2f(86 * 40, 6 * 40));

  if (bgTexture.loadFromFile("Data/Images/gameBGL.png"))
  {
    std::cout << "BG did not load \n";
  }
  bgSprite.setTexture(bgTexture);
  return GameStateBase::init();
}

bool GamePlay::WallCollisions()
{
  if (game_data->players[game_data->controlled_player]->getMax().y > 16 * 40)
  {
    life--;
    spawn();
    death_sound.play();
  }
  return true;
}


void GamePlay::loadAudio(const std::string& filepath)
{
  if (!death_buffer.loadFromFile(filepath))
  {
    std::cout << "audioerror";
  }
  else
  {
    death_sound.setBuffer(death_buffer);
  }
}

void GamePlay::onEnter()
{
  //camera = std::make_unique<Camera>("", sf::Vector2f(0, 0), *game_data->players[game_data->controlled_player]);
  life = 3;
  life_text.setString(std::to_string(life));

  game_data->level_one->prepareLevel(*game_data);

  GameStateBase::onEnter();
}
void GamePlay::onExit()
{
  game_data->window->setView(game_data->window->getDefaultView());
  GameStateBase::onExit();
}
void GamePlay::keyboard_input(sf::Event event)
{
  game_data->players[game_data->controlled_player]->key_pressed(event);


}

void GamePlay::keyboard_release(sf::Event event)
{
  game_data->players[game_data->controlled_player]->key_released(event);
}

void GamePlay::mouse_input(sf::Event event)
{
  GameStateBase::mouse_input(event);
}

State GamePlay::update(float dt)
{
  life_text.setString(std::to_string(life));
  Character* player = game_data->players[game_data->controlled_player];
  portalBlue->update(dt);
  //portalRed->update(dt);
  player->update(dt);

  WallCollisions();

  // Do collision with portal
  if (player->AABBCollision(*portalBlue) && game_data->players[game_data->other_player]->AABBCollision(*portalBlue))
  {
    game_data->client->sendStateUpdate(State::GAME_WIN);
    return State::GAME_WIN;
  }


  for (auto& piece : game_data->level_one->getPuzzle()->getPuzzlePieces())
  {
    if (player->AABBCollision(*piece))
    {
      piece->activate();
    }
    else
    {
      //piece->deactivate();
    }
  }

  if (life == 0)
  {
    game_data->client->sendStateUpdate(State::GAME_OVER);
    return State::GAME_OVER;
  }

  player->setGrounded(false);

  // Check collision with the tiles in the level
  for (auto& tile : game_data->level_one->getTiles())
  {
    if (tile->isVisible())
    {
      if (game_data->controlled_player == ControlledPlayer::PLAYER_ONE && tile->getLayerNumber() == 1) continue;
      else if (game_data->controlled_player == ControlledPlayer::PLAYER_TWO && tile->getLayerNumber() == 3) continue;

      if (player->AABBCollision(*tile))
      {
        switch (player->sideCollision(*tile))
        {
          case Side::LEFT:
            player->setPosition(
              tile->getMin().x - player->getWidth(), player->getMin().y);
            break;
          case Side::RIGHT:
            player->setPosition(tile->getMax().x, player->getMin().y);
            break;
          case Side::TOP:
            player->setPosition(
              player->getMin().x, tile->getMin().y - player->getHeight());

            player->groundCharacter();
            break;
          case Side::BOTTOM:
            player->setPosition(player->getMin().x, tile->getMax().y);
            break;
          default:
            game_data->players[game_data->controlled_player]->setGrounded(
              false);
            break;
        }
      }

      PushableObject& box = *game_data->level_one->getBox();
      if (box.AABBCollision(*tile))
      {
        switch (box.sideCollision(*tile))
        {
          case Side::LEFT:
            box.setPosition(tile->getMin().x - box.getWidth(), box.getMin().y);
            break;
          case Side::RIGHT:
            box.setPosition(tile->getMax().x, box.getMin().y);
            break;
          case Side::TOP:
            box.setPosition(box.getMin().x, tile->getMin().y - box.getHeight());
            break;
          case Side::BOTTOM:
            box.setPosition(box.getMin().x, tile->getMax().y);
            break;
          default:
            break;
        }
      }
    }
  }

  // Check collision with doors in the level
  for (auto& door : game_data->level_one->getDoors())
  {
    if (door->getEnabled())
    {
      if (player->AABBCollision(door->getCollisionBox()))
      {
        switch(player->sideCollision(door->getCollisionBox()))
        {
          case Side::LEFT:
            player->setPosition(door->getCollisionBox().getMin().x - player->getWidth(), player->getMin().y);
            break;
          case Side::RIGHT:
            player->setPosition(door->getCollisionBox().getMax().x, player->getMin().y);
            break;
          default:
            break;
        }
      }
    }
  }

  for (auto& coin : game_data->level_one->getCoins())
  {
    if (coin->isVisible())
    {
      if (player->AABBCollision(*coin))
      {
        coin->setVisible(false);
        coin->onCollision();
      }
    }
  }

  game_data->level_one->updateLevel(dt);

  if (game_data->level_one->getPuzzle()->getPuzzlePieces().front()->AABBCollision(*player))
  {
    game_data->level_one->getPuzzle()->getPuzzlePieces().front()->activate();
    if (game_data->client->getConnected())
    {
      //std::thread send_thread([&]{game_data->client->sendPuzzleUpdate(test_switch->getActive());});
      //send_thread.detach();
    }
  }

  if (game_data->client->getConnected())
  {
    game_data->client->update();
  }

  PushBlock(dt);

  camera->update(dt, *game_data->window);

  //if (player->AABBCollision(*end_point) && game_data->players[game_data->other_player]->AABBCollision(*end_point))
  {
    //return State::GAME_WIN;
  }

  return state;
}

void GamePlay::render(sf::RenderWindow& window)
{
  window.draw(bgSprite);

  sf::View basic;
  basic.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  basic.setViewport(sf::FloatRect(0, 0, 1, 1));
  window.setView(basic);

  window.draw(life_text);
  window.draw(life_text2);
  window.setView(window.getDefaultView());

  camera->render(window);

  game_data->players[ControlledPlayer::PLAYER_ONE]->render(window);
  game_data->players[ControlledPlayer::PLAYER_TWO]->render(window);

  //game_data->puzzle_one->render(*game_data->window);
  //window.draw(portal->getSprite());
  portalBlue->render(window);
  //portalRed->render(window);

  game_data->level_one->render(*game_data);
  //end_point->render(window);
}

void GamePlay::spawn()
{
  game_data->players[game_data->controlled_player]->setPosition(100.f, 400.f);
}

void GamePlay::PushBlock(float dt)
{
  PushableObject& block = *game_data->level_one->getBox();

  // Check if player collides with block
  if (!game_data->players[game_data->controlled_player]->AABBCollision(
        block))
  {
    return;
  }

  // Player is above block (whether pushing or not)
  if (
    game_data->players[game_data->controlled_player]->getMax().y <
    block.getMax().y)
  {
    game_data->players[game_data->controlled_player]->getSprite().setPosition(
      game_data->players[game_data->controlled_player]->getSprite().getPosition().x,
      block.getSprite().getPosition().y -
        game_data->players[game_data->controlled_player]->getHeight());
    game_data->players[game_data->controlled_player]->setGrounded(true);
    return;
  }

  // Player is not pushing
  if (game_data->players[game_data->controlled_player]->getCurrentState() != PUSHING)
  {
    {
      // Player is next to the block
      if (
        game_data->players[game_data->controlled_player]
          ->getSprite()
          .getPosition()
          .x < block.getSprite().getPosition().x)
      {
        game_data->players[game_data->controlled_player]->move(
          -60, 0, dt, 80.f, 1.f, 3.f, .93f);
      }
      else
      {
        game_data->players[game_data->controlled_player]->move(
          60, 0, dt, 80.f, 1.f, 3.f, .93f);
      }
    }
  }
  // Player is pushing
  else
  {
    if (
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -30)
    {
      block.move(-200, 0, dt, 200.f, 1.f, 3.f, .93f);
    }

    if (
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 30)
    {
      block.move(200, 0, dt, 200.f, 1.f, 3.f, .93f);
    }
  }
}
