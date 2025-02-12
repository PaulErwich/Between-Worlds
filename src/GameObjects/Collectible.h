//
// Created by l3-symes on 07/03/2023.
//

#ifndef SFMLGAME_COLLECTIBLE_H
#define SFMLGAME_COLLECTIBLE_H
#include "GameObject.h"
#include <SFML/Audio.hpp>
#include "Character.h"

class Collectible: public GameObject
{
 public:
  Collectible(const std::string& filename, sf::Vector2f pos);

  void update(float dt) override;

  void init() override;
  void loadAudio(const std::string& filepath);
  void onCollision();


 private:

sf::SoundBuffer collectible_buffer;
sf::Sound collectible_sound;
sf::Clock gem_animation_tick;


int score = 0;
int gems_collected = 0;

sf::IntRect gem_texture_sheet;
};

#endif // SFMLGAME_COLLECTIBLE_H
