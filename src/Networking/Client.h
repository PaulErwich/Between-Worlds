//
// Created by perwi on 10/03/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <mutex>
#include <thread>
#include <iostream>

#include "CustomPacket.h"
#include "../GameObjects/GameObject.h"



class GameData;

class Client
{
 public:
  Client(GameData* _game_data);

  void initialConnect(const std::string& ip);
  void input(sf::Event event);
  void run();

  bool getConnected() const;

  void update();

  void sendStateUpdate(State state);

  const std::unique_ptr<sf::TcpSocket>& getSocket() const;

  void vector2Receive(sf::Packet& received);
  void gameStateReceive(sf::Packet& received);

 private:
  std::unique_ptr<sf::TcpSocket> socket;

  std::mutex mutex;

  GameData* game_data;

  bool connected;
};

#endif // SFMLGAME_CLIENT_H
