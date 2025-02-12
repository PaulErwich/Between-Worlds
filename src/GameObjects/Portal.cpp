//
// Created by luria on 29/04/2023.
//

#include "Portal.h"
#include "../Other/AnimationHelper.h"
Portal::Portal(const std::string& filename, sf::Vector2f pos) :
  GameObject(filename,pos)
{
  sprite->setScale(sf::Vector2f(3.0f, 3.0f));
  currentFrame = sf::IntRect(0,0,32,32);
  sprite->setTextureRect(sf::IntRect(currentFrame));

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;
  //sprite->scale(sf::Vector2f(10.0f, 10.0f));

  if (!portalShader.loadFromFile("Data/Shaders/portaly.glsl", sf::Shader::Fragment))
  {
    std::cout << "failed to load shader\n";
  }
  //portalShader.setUniform("resolution", sf::Vector2f(300.0f, 300.0f));
  noise.loadFromFile("Data/Images/noise.jpg");
  portalShader.setUniform("texture1", noise);
  portalShader.setUniform("resolution", sf::Vector2f((sprite->getPosition().x + sprite->getGlobalBounds().width)*0.5f,(sprite->getPosition().y + sprite->getGlobalBounds().height)*0.5f));


}
void Portal::update(float dt)
{
  portalShader.setUniform("time", clock.getElapsedTime().asSeconds());
  //portalShader.setUniform("resolution", sf::Vector2f(sprite->getPosition().x + sprite->getGlobalBounds().width,sprite->getPosition().y + sprite->getGlobalBounds().height));
  //sf::Vector2f center = sprite->getPosition() + sf::Vector2f(sprite->getGlobalBounds().width / 2.f, sprite->getGlobalBounds().height / 2.f);


  // Do animation

  AnimationHelper::DoAnimation(*sprite, updateRate,
                               currentFrame, &clock, IDLE);

  GameObject::update(dt);
}
void Portal::render(sf::RenderWindow& window)
{
  window.draw(*sprite);
  //GameObject::render(window);
}
