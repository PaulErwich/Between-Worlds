//
// Created by perwi on 17/03/2023.
//

#include "PacketType.h"

sf::Packet& operator << (sf::Packet& packet, const PacketType& packet_type)
{
  int temp = 0;

  switch (packet_type)
  {
    case PacketType::NONE:
      temp = 0;
      break;
    case PacketType::MESSAGE:
      temp = 1;
      break;
    case PacketType::VECTOR2F:
      temp = 2;
      break;
    case PacketType::PUZZLE:
      temp = 3;
      break;
    case PacketType::LEVEL:
      temp = 4;
      break;
    case PacketType::COIN_STATUS:
      temp = 5;
      break;
    case PacketType::STATE:
      temp = 6;
      break;
    default:
      temp = 0;
      break;
  }

  return packet << temp;
}

sf::Packet& operator >> (sf::Packet& packet, PacketType& packet_type)
{
  int temp = 0;
  packet >> temp;

  switch (temp)
  {
    case 0:
      packet_type = PacketType::NONE;
      break;
    case 1:
      packet_type = PacketType::MESSAGE;
      break;
    case 2:
      packet_type = PacketType::VECTOR2F;
      break;
    case 3:
      packet_type = PacketType::PUZZLE;
      break;
    case 4:
      packet_type = PacketType::LEVEL;
      break;
    case 5:
      packet_type = PacketType::COIN_STATUS;
      break;
    case 6:
      packet_type = PacketType::STATE;
      break;
    default:
      packet_type = PacketType::NONE;
      break;
  }

  return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Vector2fType& vector2f_type)
{
  int temp = 0;

  switch(vector2f_type)
  {
    case Vector2fType::NONE:
      temp = 0;
      break;
    case Vector2fType::PLAYER_POS:
      temp = 1;
      break;
    case Vector2fType::BOX_POS:
      temp = 2;
      break;
    default:
      temp = 0;
      break;
  }

  return packet << temp;
}

sf::Packet& operator >> (sf::Packet& packet, Vector2fType& vector2f_type)
{
  int temp = 0;
  packet >> temp;

  switch(temp)
  {
    case 0:
      vector2f_type = Vector2fType::NONE;
      break;
    case 1:
      vector2f_type = Vector2fType::PLAYER_POS;
      break;
    case 2:
      vector2f_type = Vector2fType::BOX_POS;
      break;
    default:
      vector2f_type = Vector2fType::NONE;
      break;
  }

  return packet;
}

sf::Packet& operator << (sf::Packet& packet, const State& state)
{
  int temp = 0;

  switch (state)
  {
    case State::GAME_UNKNOWN:
      temp = -1;
      break;
    case State::GAME_EXIT:
      temp = 0;
      break;
    case State::GAME_MENU:
      temp = 1;
      break;
    case State::GAME_LOBBY:
      temp = 2;
      break;
    case State::GAME_LEVEL_SELECT:
      temp = 3;
      break;
    case State::GAME_PLAY:
      temp = 4;
      break;
    case State::GAME_WIN:
      temp = 5;
      break;
    case State::GAME_OVER:
      temp = 6;
      break;
    default:
      temp = -1;
      break;
  }

  return packet << temp;
}

sf::Packet& operator >> (sf::Packet& packet, State& state)
{
  int temp = 0;
  packet >> temp;

  switch (temp)
  {
    case -1:
      state = State::GAME_UNKNOWN;
      break;
    case 0:
      state = State::GAME_EXIT;
      break;
    case 1:
      state = State::GAME_MENU;
      break;
    case 2:
      state = State::GAME_LOBBY;
      break;
    case 3:
      state = State::GAME_LEVEL_SELECT;
      break;
    case 4:
      state = State::GAME_PLAY;
      break;
    case 5:
      state = State::GAME_WIN;
      break;
    case 6:
      state = State::GAME_OVER;
      break;
  }

  return packet;
}