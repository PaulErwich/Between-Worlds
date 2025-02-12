//
// Created by perwi on 03/03/2023.
//

#ifndef SFMLGAME_CUSTOMPACKET_H
#define SFMLGAME_CUSTOMPACKET_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "PacketType.h"
#include "SFMLPacketOverloads.h"
#include "../GameObjects/Collectible.h"

class Puzzle;

struct CustomPacket
{
  CustomPacket();
  CustomPacket(PacketType _packet_type);

  PacketType packet_type;


};

sf::Packet& operator <<(sf::Packet& packet, const CustomPacket& data);
sf::Packet& operator >>(sf::Packet& packet, CustomPacket& data);

struct CustomPacketMessage : CustomPacket
{
  CustomPacketMessage();
  CustomPacketMessage(std::string _message);

  std::string message;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketMessage& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketMessage& data);

struct CustomPacketVector2f : CustomPacket
{
  CustomPacketVector2f();
  CustomPacketVector2f(sf::Vector2f _position, Vector2fType _vector2f_type);

  sf::Vector2f position;
  Vector2fType vector2f_type;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketVector2f& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketVector2f& data);

struct CustomPacketSwitch : CustomPacket
{
  CustomPacketSwitch();
  CustomPacketSwitch(bool _status);

  bool status; // Status for switch
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketSwitch& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketSwitch& data);

struct CustomPacketLevel : CustomPacket
{
  CustomPacketLevel() : CustomPacket(PacketType::LEVEL) {}
  CustomPacketLevel(sf::Vector2f _p1p, sf::Vector2f _p2p, Puzzle* _p1,
                    Puzzle* _p2, Puzzle* _p3);

  sf::Vector2f player_1_pos;
  sf::Vector2f player_2_pos;

  Puzzle* puzzle_1 = nullptr;
  Puzzle* puzzle_2 = nullptr;
  Puzzle* puzzle_3 = nullptr;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketLevel& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketLevel data);

struct CustomPacketPuzzle : CustomPacket
{
  CustomPacketPuzzle();
  CustomPacketPuzzle(Puzzle* _puzzle);

  Puzzle* puzzle;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketPuzzle& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketPuzzle& data);

struct CustomPacketCoinPositions : CustomPacket
{
  CustomPacketCoinPositions(std::vector<std::unique_ptr<Collectible>>& _collectibles);

  std::vector<std::unique_ptr<Collectible>>& collectibles;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketCoinPositions& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketCoinPositions& data);

struct CustomPacketState : CustomPacket
{
  CustomPacketState();
  CustomPacketState(State _state);

  State state;
};

sf::Packet& operator << (sf::Packet& packet, const CustomPacketState& data);
sf::Packet& operator >> (sf::Packet& packet, CustomPacketState& data);
#endif // SFMLGAME_CUSTOMPACKET_H
