//
// Created by perwi on 03/03/2023.
//

#include "CustomPacket.h"

#include "../GameObjects/Puzzle.h"

#include <utility>

/// CustomPacket setup
/// Base packet type that holds enum for type of message being sent
/// Includes constructors and overloads for packet type
CustomPacket::CustomPacket() { packet_type = PacketType::NONE; }

CustomPacket::CustomPacket(PacketType _packet_type) : packet_type(_packet_type) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacket& data)
{
  return packet << data.packet_type;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacket& data)
{
  return packet >> data.packet_type;
}

/// CustomPacketMessage setup
/// Packet for sending strings in packets
/// Includes constructors and overloads for packet type
CustomPacketMessage::CustomPacketMessage() : CustomPacket(PacketType::MESSAGE),
  message("No Message") {}

CustomPacketMessage::CustomPacketMessage(std::string _message) :
  CustomPacket(PacketType::MESSAGE), message(std::move(_message)) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketMessage& data)
{
  return packet << data.packet_type << data.message;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketMessage& data)
{
  return packet >> data.packet_type >> data.message;
}

/// CustomPacketVector2f setup
/// Packet for sending sf::Vector2f - main use is for sending positions
/// Includes constructors and overloads for packet type
CustomPacketVector2f::CustomPacketVector2f() : CustomPacket(PacketType::MESSAGE),
  position({0, 0}), vector2f_type(Vector2fType::NONE) {}

CustomPacketVector2f::CustomPacketVector2f(sf::Vector2f _position, Vector2fType _vector2f_type) :
  CustomPacket(PacketType::VECTOR2F), position(_position), vector2f_type(_vector2f_type) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketVector2f& data)
{
  return packet << data.packet_type << data.vector2f_type << data.position;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketVector2f& data)
{
  return packet >> data.packet_type >> data.vector2f_type >> data.position;
}

/// CustomPacketPuzzle setup
/// Packet for sending puzzle_test number and status
/// Includes constructors and overloads for packet type
CustomPacketSwitch::CustomPacketSwitch() : CustomPacket(PacketType::PUZZLE),
  status(false) {}

CustomPacketSwitch::CustomPacketSwitch(bool _status) : CustomPacket(PacketType::PUZZLE),
  status(_status) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketSwitch& data)
{
  return packet << data.packet_type << data.status;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketSwitch& data)
{
  return packet >> data.packet_type >> data.status;
}

/// CustomPacketLevel setup
/// Packet for sending required level data to server
/// Includes constructors and overloads for packet type
CustomPacketLevel::CustomPacketLevel(sf::Vector2f _p1p, sf::Vector2f _p2p, Puzzle* _p1, Puzzle* _p2, Puzzle* _p3) :
CustomPacket(PacketType::LEVEL), player_1_pos(_p1p), player_2_pos(_p2p), puzzle_1(_p1), puzzle_2(_p2), puzzle_3(_p3) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketLevel& data)
{
  packet << data.packet_type << data.player_1_pos << data.player_2_pos;

  if (data.puzzle_1 && data.puzzle_2 && data.puzzle_3)
  {
    packet << data.puzzle_1->getCompleted() << data.puzzle_2->getCompleted() << data.puzzle_3->getCompleted();
  }

  return packet;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketLevel& data)
{
  return packet >> data.packet_type >> data.player_1_pos >> data.player_2_pos;
}

/// CustomPacketPuzzle setup
/// Packet for sending updates of a whole puzzle
/// Includes constructors and overloads for packet type
CustomPacketPuzzle::CustomPacketPuzzle(): CustomPacket(PacketType::PUZZLE), puzzle(nullptr) {}
CustomPacketPuzzle::CustomPacketPuzzle(Puzzle* _puzzle) : CustomPacket(PacketType::PUZZLE), puzzle(_puzzle) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketPuzzle& data)
{
  packet << data.packet_type;

  for (auto& piece : data.puzzle->getPuzzlePieces())
  {
    packet << piece->getActive();
    //std::cout << piece->getActive();
  }

  return packet;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketPuzzle& data)
{
  packet >> data.packet_type;

  bool temp;
  for (auto& piece : data.puzzle->getPuzzlePieces())
  {
    packet >> temp;
    if (temp)
    {
      piece->activate();
    }
    else
    {
      piece->deactivate();
    }
    std::cout << "received " << temp << std::endl;
  }

  return packet;
}

/// CustomPacketCoinPositions setup
/// Packet for sending status of all coins in the level
/// Includes constructors and overloads for packet type
CustomPacketCoinPositions::CustomPacketCoinPositions(std::vector<std::unique_ptr<Collectible>>& _collectibles)
  : CustomPacket(PacketType::COIN_STATUS), collectibles(_collectibles) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketCoinPositions& data)
{
  packet << data.packet_type;

  for (auto& collectible : data.collectibles)
  {
    packet << collectible->isVisible();
  }

  return packet;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketCoinPositions& data)
{
  packet >> data.packet_type;

  for (auto& collectible : data.collectibles)
  {
    bool temp;
    packet >> temp;
    collectible->setVisible(temp);
  }

  return packet;
}

/// CustomPacketState setup
/// Packet for sending state updates for the game
/// Includes constructors and overloads for packet type
CustomPacketState::CustomPacketState() : CustomPacket(PacketType::STATE), state(State::GAME_UNKNOWN) {}

CustomPacketState::CustomPacketState(State _state) : CustomPacket(PacketType::STATE), state(_state) {}

sf::Packet& operator << (sf::Packet& packet, const CustomPacketState& data)
{
  return packet << data.packet_type << data.state;
}

sf::Packet& operator >> (sf::Packet& packet, CustomPacketState& data)
{
  return packet >> data.packet_type >> data.state;
}