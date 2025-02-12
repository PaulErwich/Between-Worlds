//
// Created by l3-symes on 07/03/2023.
//

#include <iostream>
#include "Collectible.h"
#include "../Other/AnimationHelper.h"

Collectible::Collectible(const std::string& filename, sf::Vector2f pos)
: GameObject(filename, pos)
{
  //INITIALISE COLLECTABLE
  sprite->setScale(1.25, 1.25);

  gem_texture_sheet = {0, 0, 32, 32};
  sprite->setTextureRect(gem_texture_sheet);
  //collect_gem.play(); USE THIS TO PLAY SOUND WHEN CHARACTER COLLIDES

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;
  setMin();
  calculateMax();
}

void Collectible::init()
{

}

void Collectible::update(float dt)
{
  AnimationHelper::DoAnimation(*sprite, 0.1f, gem_texture_sheet, &gem_animation_tick, IDLE);
}

void Collectible::loadAudio(const std::string& filepath)
{
  if (!collectible_buffer.loadFromFile(filepath))
  {
    std::cout << "audioerror";
  }
  else
  {
    collectible_sound.setBuffer(collectible_buffer);
  }
}
void Collectible::onCollision()
{
  // Play audio
  collectible_sound.play();
}
