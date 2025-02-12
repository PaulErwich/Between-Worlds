//
// Created by luria on 29/04/2023.
//

#ifndef SFMLGAME_PORTAL_H
#define SFMLGAME_PORTAL_H

#include "GameObject.h"
class Portal : public GameObject
{
 public:
  Portal(const std::string& filename, sf::Vector2f pos);
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
  bool active = true;
  sf::IntRect currentFrame;
  float updateRate = 0.15f;

  sf::Shader portalShader;
  sf::Clock clock;
  sf::RenderTexture portalTexture;
  sf::Sprite portalSprite;
  sf::RectangleShape box;
  sf::Texture noise;
};

#endif // SFMLGAME_PORTAL_H
