//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_STATE_H
#define SFMLGAME_STATE_H

enum class State
{
  GAME_UNKNOWN = -1,
  GAME_EXIT = 0,
  GAME_MENU = 1,
  GAME_LOBBY = 2,
  GAME_LEVEL_SELECT = 3,
  GAME_PLAY = 4,
  GAME_WIN = 5,
  GAME_OVER = 6
};

#endif // SFMLGAME_STATE_H
