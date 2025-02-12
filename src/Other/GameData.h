//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMEDATA_H
#define SFMLGAME_GAMEDATA_H

#include <SFML/Graphics.hpp>
#include <map>

#include "../GameObjects/Character.h"
#include "../Networking/Client.h"
#include "../Networking/Server.h"
#include "../GameStates/State.h"
#include "../GameObjects/Puzzle.h"
#include "ControlledPlayer.h"
#include "../LevelLoading/LevelData.h"

struct GameData
{
  ControlledPlayer controlled_player;
  ControlledPlayer other_player;

  std::map<ControlledPlayer, Character*> players;

  std::unique_ptr<Client> client;
  std::unique_ptr<Server> server;

  sf::RenderWindow* window;
  sf::Event* event;

  State current_state;

  bool received_state_change = false;
  State received_state; // State change received from network

  //std::unique_ptr<Puzzle> puzzle_one;

  std::unique_ptr<LevelData> level_one;

  bool startGame = false;
};

#endif // SFMLGAME_GAMEDATA_H
