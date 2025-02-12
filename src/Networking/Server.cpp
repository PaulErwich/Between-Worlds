//
// Created by perwi on 17/03/2023.
//

#include "Server.h"

Server::Server() : running(false)
{
  if (listener == nullptr) listener = std::make_unique<sf::TcpListener>();

  if (listener->listen(53000) != sf::Socket::Done)
  {
    std::cout << "Port not open\n";

  }
  running = true;
}

void Server::run()
{
  std::cout << "Started running\n";

  while (running)
  {
    sf::TcpSocket& cSock = connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();

    if (listener->accept(cSock) != sf::Socket::Done)
    {
      std::cout << "Don't add client\n";

      if (!running) break;

      connections.pop_back();
      return;
    }

    std::cout << "Client connected @ " << cSock.getRemotePort() << "\n";
    playersConnected++;

    workers.emplace_back([&]
                         {
                           listen(cSock);
                           // After this function exits, we know a client disconnected

                           std::cout << "Client disconnected\n";

                           std::lock_guard<std::mutex>lck(mutex); // Guard socket list access whilst we delete disconnected client

                           for (int i = 0; i < connections.size(); i++)
                           {
                             if (connections[i]->getRemotePort() == cSock.getRemotePort())
                             {
                               connections.erase(std::next(connections.begin(), i));

                               break;
                             }
                           }
                         });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  bool receiving = true;

  sf::Packet received_packet;
  sf::Packet copy_packet;

  while (receiving)
  {
    auto status = cSocket.receive(received_packet);

    if (status == sf::Socket::Status::Disconnected)
    {
      receiving = false; // Client disconnected
      std::cout << "Disconnected\n";
    }

    copy_packet = received_packet;

    send(received_packet, cSocket);
  }
  cSocket.disconnect();
}

void Server::send(sf::Packet& packet, sf::TcpSocket& cSocket)
{
  std::lock_guard<std::mutex>lck(mutex); // Lock mutex whilst going through connections

  for (auto& connection : connections)
  {
    if (connection->getRemotePort() == cSocket.getRemotePort()) continue;

    connection->send(packet);
  }
}

void Server::shutdownServer()
{
  for (auto& socket : connections)
  {
    socket->disconnect();
  }

  // Rejoin threads to stop below error
  // "terminate called without an active exception"
  for (auto& thread : workers)
  {
    thread.join();
  }

  listener->close();
  running = false;
}
int Server::getPlayersConnected() const
{
  return playersConnected;
}
