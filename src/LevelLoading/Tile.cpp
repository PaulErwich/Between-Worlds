//
// Created by reece on 31/03/2023.
//

#include "Tile.h"

Tile::Tile(sf::Texture &_texture, int x, int y, int textureNum, int _layer_number) :
  GameObject("", sf::Vector2f(x, y)), layer_number(_layer_number)
{
  texture = std::make_unique<sf::Texture>(_texture);

  // Read in texture ID number that will be used for tile
  if (textureNum != -1)
  {
    int left = 0, top = 0;

    for (int l = 0; l < textureNum; l++)
    {
      left++;
      if (left == 11)
      //if (left == 16)
      {
        left = 0;
        top++;
      }
    }

    // Set the tiles width and height
    sf::IntRect texture_rect(left * 32, top * 32,
                             32, 32);

    // Player sprite values
    float scale = 1.25f;
    sprite->setTexture(*texture);
    sprite->setTextureRect(texture_rect);
    sprite->setScale(scale, scale);
    sprite->setPosition(x * 32 * scale, y * 32 * scale);


    width = sprite->getGlobalBounds().width;
    height = sprite->getGlobalBounds().height;

    setMin();
    calculateMax();
  }
}