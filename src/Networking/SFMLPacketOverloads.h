//
// Created by perwi on 08/03/2023.
//

#ifndef SFMLGAME_SFMLPACKETOVERLOADS_H
#define SFMLGAME_SFMLPACKETOVERLOADS_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

sf::Packet& operator << (sf::Packet& packet, const sf::Vector2f& _vector2f);

sf::Packet& operator >> (sf::Packet& packet, sf::Vector2f& _vector2f);

#endif // SFMLGAME_SFMLPACKETOVERLOADS_H
