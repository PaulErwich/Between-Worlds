//
// Created by reece on 31/03/2023.
//

#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include <iostream>
#include <tuple>
#include "SFML/Graphics.hpp"
#include "../GameObjects/GameObject.h"

class Tile : public GameObject
{
 public:

  Tile(sf::Texture &_texture, int x, int y, int textureNum, int _layer_number);
  ~Tile() = default;

  int getLayerNumber() const { return layer_number; }

 private:
  int layer_number;
};

#endif // SFMLGAME_TILE_H
