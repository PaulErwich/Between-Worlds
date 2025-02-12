//
// Created by perwi on 17/03/2023.
//

#include "SFMLPacketOverloads.h"

sf::Packet& operator << (sf::Packet& packet, const sf::Vector2f& _vector2f)
{
  return packet << _vector2f.x << _vector2f.y;
}

sf::Packet& operator >> (sf::Packet& packet, sf::Vector2f& _vector2f)
{
  return packet >> _vector2f.x >> _vector2f.y;
}