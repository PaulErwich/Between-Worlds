//
// Created by perwi on 08/03/2023.
//

#ifndef SFMLGAME_PACKETTYPE_H
#define SFMLGAME_PACKETTYPE_H

#include <SFML/Network.hpp>
#include "../GameStates/State.h"

enum class PacketType
{
  NONE,
  MESSAGE,
  VECTOR2F,
  PUZZLE,
  LEVEL,
  COIN_STATUS,
  STATE
};

sf::Packet& operator << (sf::Packet& packet, const PacketType& packet_type);

sf::Packet& operator >> (sf::Packet& packet, PacketType& packet_type);

enum class Vector2fType
{
  NONE,
  PLAYER_POS,
  BOX_POS
};

sf::Packet& operator << (sf::Packet& packet, const Vector2fType& vector2f_type);

sf::Packet& operator >> (sf::Packet& packet, Vector2fType& vector2f_type);



sf::Packet& operator << (sf::Packet& packet, const State& state);

sf::Packet& operator >> (sf::Packet& packet, State& state);

#endif // SFMLGAME_PACKETTYPE_H
