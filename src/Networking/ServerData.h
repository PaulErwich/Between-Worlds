//
// Created by MLG Erwich on 31/03/2023.
//

#ifndef SFMLGAME_SERVERDATA_H
#define SFMLGAME_SERVERDATA_H

#include <SFML/Graphics.hpp>
#include <map>

#include "../Other/ControlledPlayer.h"
#include "../GameObjects/Puzzle.h"

struct ServerData
{
  void setupData(sf::Vector2f plr_1_pos, sf::Vector2f plr_2_pos)
  {
    player_positions[ControlledPlayer::PLAYER_ONE] = plr_1_pos;
    player_positions[ControlledPlayer::PLAYER_TWO] = plr_2_pos;
  }

  /// Server keeps track of last known player positions
  /// Will update them as it receives updates from clients
  std::map<ControlledPlayer, sf::Vector2f> player_positions;

  /// Server keep track of current levels puzzles
  /// Will update them as players interact
  Puzzle* puzzle_one;
  Puzzle* puzzle_two;
  Puzzle* puzzle_three;

};

#endif // SFMLGAME_SERVERDATA_H
