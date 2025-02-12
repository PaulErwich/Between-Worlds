//
// Created by perwi on 10/03/2023.
//

#include "Client.h"

#include "../Other/GameData.h"

Client::Client(GameData* _game_data) : connected(false), game_data(_game_data)
{
  socket = std::make_unique<sf::TcpSocket>();
}

void Client::initialConnect(const std::string& ip)
{
  if (socket == nullptr) return;

  if (socket->connect(ip, 53000) == sf::Socket::Status::Done)
  {
    std::cout << "Connected to server\n";

    connected = true;

    std::thread run_thread ([&]{run();});
    run_thread.detach();
  }
  else
  {
    std::cout << "Failed to connect to server\n";
  }
}

void Client::input(sf::Event event)
{
}

void Client::run()
{
  while (connected)
  {
    sf::Packet received_packet;
    sf::Packet copy_packet;
    CustomPacket packet_data;
    CustomPacketSwitch switch_data;
    CustomPacketPuzzle puzzle_data;
    CustomPacketCoinPositions coin_data(game_data->level_one->getCoins());

    auto status = socket->receive(received_packet);

    if (status == sf::Socket::Status::Disconnected)
    {
      connected = false;
      std::cout << "Clean disconnection\n";
      socket->disconnect();
      break;
    }

    copy_packet = received_packet;

    copy_packet >> packet_data;

    std::lock_guard<std::mutex>lck(mutex);

    /// Switch the type of packet that has been received and do stuff with
    /// it as necessary. Currently setup for positions with Rectangle shapes
    switch (packet_data.packet_type)
    {
      case PacketType::NONE:
        break;
      case PacketType::MESSAGE:
        break;
      case PacketType::VECTOR2F:
        vector2Receive(received_packet);
        //received_packet >> vector2f_data;
        //std::cout << vector2f_data.position.x << " " << vector2f_data.position.y << "\n";
        //sending_test->setPosition(vector2f_data.position);
        break;
      case PacketType::PUZZLE:
        puzzle_data.puzzle = &*game_data->level_one->getPuzzle();
        received_packet >> puzzle_data;
        std::cout << "puzzle received" << std::endl;
        break;
        game_data->current_state = State::GAME_PLAY;
        break;
      case PacketType::LEVEL:
        break;
      case PacketType::COIN_STATUS:
        received_packet >> coin_data;
        break;
      case PacketType::STATE:
        gameStateReceive(received_packet);
      default:
        break;
    }
  }
}

bool Client::getConnected() const { return connected; }

void Client::update()
{
  if (connected && game_data->current_state == State::GAME_PLAY)
  {
    std::lock_guard<std::mutex>lck(mutex);

    // Sending player position
    sf::Packet pos_packet;
    CustomPacketVector2f player_pos(
      game_data->players[game_data->controlled_player]->getSprite().getPosition(), Vector2fType::PLAYER_POS);
    pos_packet << player_pos;
    socket->send(pos_packet);

    sf::Packet box_packet;
    CustomPacketVector2f box_pos(game_data->level_one->getBox()->getMin(), Vector2fType::BOX_POS);
    box_packet << box_pos;
    socket->send(box_packet);

    sf::Packet puzzle_packet;
    CustomPacketPuzzle puzzle(&*game_data->level_one->getPuzzle());
    puzzle_packet << puzzle;
    socket->send(puzzle_packet);

    sf::Packet coin_packet;
    CustomPacketCoinPositions coin_data(game_data->level_one->getCoins());
    coin_packet << coin_data;
    socket->send(coin_packet);


    //std::cout << socket->send(packet);
  }
}

void Client::sendStateUpdate(State state)
{
  std::lock_guard<std::mutex>lck(mutex);
  sf::Packet packet;
  CustomPacketState state_data (state);

  packet << state_data;
  socket->send(packet);
}

const std::unique_ptr<sf::TcpSocket>& Client::getSocket() const
{
  return socket;
}

void Client::vector2Receive(sf::Packet& received)
{
  CustomPacketVector2f vector2f_data;
  received >> vector2f_data;

  switch (vector2f_data.vector2f_type)
  {
    case Vector2fType::NONE:
      break;
    case Vector2fType::PLAYER_POS:
      game_data->players[game_data->other_player]->getSprite().setPosition(vector2f_data.position);
      game_data->players[game_data->other_player]->setMin();
      game_data->players[game_data->other_player]->calculateMax();
      break;
    case Vector2fType::BOX_POS:
      game_data->level_one->getBox()->setPosition(vector2f_data.position);
      game_data->level_one->getBox()->setMin();
      game_data->level_one->getBox()->calculateMax();
      break;
    default:
      break;
  }
}

void Client::gameStateReceive(sf::Packet& received)
{
  CustomPacketState state_data;
  received >> state_data;

  game_data->received_state_change = true;

  game_data->received_state = state_data.state;
}
