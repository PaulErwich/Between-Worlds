//
// Created by perwi on 03/03/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../Other/Helper.h"

enum class Side
{
  NONE,
  LEFT,
  RIGHT,
  TOP,
  BOTTOM
};

class GameObject
{
 public:
  GameObject(const std::string& filename, sf::Vector2f pos);
  ~GameObject()  = default;
  virtual void init();
  virtual void update(float dt);
  virtual void render(sf::RenderWindow& window);

  bool AABBCollision(GameObject &collider) const;
  /// Function to work out what side of object you hit
  Side sideCollision(GameObject &collider) const;

  /// Getters
  bool isVisible() const { return visible; }
  sf::Sprite& getSprite() const { return *sprite; }
  const sf::Vector2f& getVelocity() const { return velocity; }
  float getWidth() const { return width; }
  float getHeight() const { return height; }
  sf::Vector2f getMin() { return min; }
  sf::Vector2f getMax() { return max;}

  /// Setters
  void setVisible(bool _visible) { visible = _visible; }
  void setVelocity(const sf::Vector2f& _velocity){velocity = _velocity;}
  void setWidth(float _width) { width = _width; }
  void setHeight(float _height) { height = _height; }
  void setMin() { min = sprite->getPosition(); }
  void calculateMax();

  void setPosition(sf::Vector2f _pos);
  void setPosition(float x, float y);

 protected:
  std::unique_ptr<sf::Sprite> sprite;
  std::unique_ptr<sf::Texture> texture;
  sf::Vector2f min;
  sf::Vector2f max;

  bool visible = true;
  sf::Vector2f velocity = {0,0};

  float width;
  float height;

};

#endif // SFMLGAME_GAMEOBJECT_H
