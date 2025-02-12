//
// Created by perwi on 10/03/2023.
//

#ifndef SFMLGAME_SWITCH_H
#define SFMLGAME_SWITCH_H

#include "PuzzlePiece.h"
#include "Door.h"

class Switch : public PuzzlePiece
{
 public:
  Switch(const std::string& filename, sf::Vector2f pos);
  void init() override;
  void update(float dt) override;


  void activate() override;
  void deactivate() override;

 private:
  sf::IntRect rect_not_active = sf::IntRect(72, 56, 18, 18);
  sf::IntRect rect_active = sf::IntRect (108, 56, 18, 18);


};

#endif // SFMLGAME_SWITCH_H
