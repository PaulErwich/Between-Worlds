//
// Created by ra2-bellchambe on 07/03/2023.
//

#include "Camera.h"

Camera::Camera(std::string filename, sf::Vector2f pos, GameData* _game_data) :
  GameObject(filename, pos), game_data(_game_data)
{

}

void Camera::init()
{
  std::cout << "INIT\n";
}

void Camera::update(float dt, sf::RenderWindow& window)
{
  //view.move(10, 0);
  followCam(dt, window);
}

void Camera::render(sf::RenderWindow& window)
{
  window.setView(view);
}

void Camera::followCam(float dt, sf::RenderWindow& window)
{

  sf::Vector2f camera_pos(game_data->players[game_data->controlled_player]->getMin().x + game_data->players[game_data->controlled_player]->getWidth() / 2, window.getSize().y / 2);

  if (camera_pos.x < window.getSize().x / 2)
  {
    camera_pos.x = window.getSize().x / 2;
  }
  else if (camera_pos.x + window.getSize().x / 2 > 40 * 90)
  {
    camera_pos.x = 40 * 90 - window.getSize().x / 2;
  }

  view.setCenter(camera_pos);
  view.setSize(window.getSize().x, window.getSize().y);
}


