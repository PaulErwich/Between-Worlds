//
// Created by l3-symes on 21/04/2023.
//

#ifndef SFMLGAME_PRESSUREPLATE_H
#define SFMLGAME_PRESSUREPLATE_H

#include "PuzzlePiece.h"
#include <SFML/Audio.hpp>
#include "Door.h"

class Pressureplate : public PuzzlePiece
{
 public:
  Pressureplate(const std::string& filename, sf::Vector2f pos, bool _colour);
  void init() override;
  void update(float dt) override;

  void loadAudio(const std::string& filepath);
  void onCollision();

  void activate() override;
  void deactivate() override;

 private:
  sf::SoundBuffer pressureplate_buffer;
  sf::Sound pressureplate_sound;
  bool colour;

  sf::IntRect rect_not_active = sf::IntRect(144, 126, 18, 18);
  sf::IntRect rect_active = sf::IntRect (162, 126, 18, 18);
};

#endif // SFMLGAME_PRESSUREPLATE_H