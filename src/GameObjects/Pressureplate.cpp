//
// Created by l3-symes on 21/04/2023.
//

#include "Pressureplate.h"
Pressureplate::Pressureplate(const std::string& filename, sf::Vector2f pos, bool _colour) :
  PuzzlePiece(filename, pos), colour(_colour)
{
  //Setting the Pressure plate to be Blue or Red
  if (colour)
  {
    rect_not_active = sf::IntRect(108, 126, 18, 18);
    rect_active = sf::IntRect (126, 126, 18, 18);
  }

  sprite->setTextureRect(rect_not_active);

  sprite->setScale(2.222, 2.222);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  setMin();
  calculateMax();
  loadAudio("Data/Sounds/click_sound_1.wav");
}

void Pressureplate::init()
{

}

void Pressureplate::activate()
{
  if (!active)
  {
    pressureplate_sound.play();
  }
  active = true;
  sprite->setTextureRect(rect_active);

  linked_door->disableDoor();
}

void Pressureplate::deactivate()
{
  active = false;
  sprite->setTextureRect(rect_not_active);

  linked_door->enableDoor();
}

void Pressureplate::loadAudio(const std::string& filepath)
{
  if (!pressureplate_buffer.loadFromFile(filepath))
  {
    std::cout << "audioerror";
  }
  else
  {
    pressureplate_sound.setBuffer(pressureplate_buffer);
  }
}

void Pressureplate::update(float dt)
{

}