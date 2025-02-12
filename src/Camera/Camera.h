//
// Created by ra2-bellchambe on 07/03/2023.
//

#ifndef SFMLGAME_CAMERA_H
#define SFMLGAME_CAMERA_H
#include "../GameObjects/GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../GameObjects/Character.h"
#include "../Other/GameData.h"

class Camera : public GameObject
{
 public:
  Camera(std::string filename, sf::Vector2f pos, GameData* _game_data);
  void init() override;
  void update(float dt, sf::RenderWindow& window);
  void followCam(float dt, sf::RenderWindow& window);
  void render(sf::RenderWindow& window) override;

 private:
  sf::View view;
  GameData* game_data;
};

#endif // SFMLGAME_CAMERA_H
