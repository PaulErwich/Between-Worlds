//
// Created by perwi on 17/03/2023.
//

#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include <SFML/Network.hpp>
#include <mutex>
#include <thread>
#include <iostream>

#include "ServerData.h"

class Server
{
 public:
  Server();

  void run();

  void listen(sf::TcpSocket& cSocket);
  void send(sf::Packet& packet, sf::TcpSocket& cSocket);

  void shutdownServer();

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;

  std::unique_ptr<sf::TcpListener> listener;

  std::mutex mutex;

  bool running;
  int playersConnected = 0;

 public:
  int getPlayersConnected() const;

 private:
  ServerData server_data;

  // Implement into the server a view of what the game should currently look like
  // From there send out checks to ensure both players are seeing the same thing
  // Server keeps track of what is where and has priorities

  // Player one interactive takes priority over player 2 for what they see
  // Player two interactive takes priority over player 1 for what they see
  // This should ensure neither player loses progress during the level

  // Create a server data class?
  // Fill that with level data once level is selected.
  // This can be "sent" from host client
};

#endif // SFMLGAME_SERVER_H
