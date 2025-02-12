//
// Created by 44749 on 10/03/2023.
//

#ifndef SFMLGAME_CHARACTER_H
#define SFMLGAME_CHARACTER_H

#include "GameObject.h"
#include "../Other/AnimationHelper.h"
#include <SFML/Audio.hpp>

class Character : public GameObject
{
 public:
  Character(std::string filename, sf::Vector2f pos, sf::RenderWindow& game_window);
  void update(float dt) override;
  sf::Vector2f updatePosition(float timeDelta);
  void movePosition(sf::Vector2f newPosition);
  void setVelocity(sf::Vector2f& velocity);
  float getMovementSpeed() const;
  void setMovementSpeed(float speed);
  AnimationState getCurrentState(){return currentAnimState;}
  void MovePlayer(float dt);
  void move(float x, float y, float dt, float max_velocity, float min_velocity, float acceleration, float deceleration);
  void pushing();
  void interacting();

  void loadAudio();
  void key_pressed(sf::Event event);
  void key_released(sf::Event event);

  void calculate_gravity();
  void animationSprites();

  bool getGrounded() const { return isGrounded; }
  void setGrounded(bool grounded) { isGrounded = grounded; }

  void groundCharacter() { isGrounded = true; velocity.y = 0; }

  void setTexture(sf::Texture& _texture);

 private:
  bool playing = false;

  sf::RenderWindow& window;
  sf::Vector2f velocityVector = {0, 0};
  sf::SoundBuffer jump_buffer;
  sf::Sound jump_sound;
  sf::SoundBuffer footsteps_buffer;
  sf::Sound footsteps_sound;



  float movementSpeed = 300;
  float normalSpeed = 300;
  float pushingSpeed = 80;
  bool isGrounded = false;

  sf::Clock idle_animation_tick;
  sf::IntRect current_texture_sheet;
  sf::Clock jump_animation_tick;
  float gravity = 8;

  float jumpForce = 150;

  //sf::Vector2f characterVelo;
  sf::Vector2f newPos;

  //Animation
  AnimationState currentAnimState = IDLE;
  sf::IntRect currentFrame;
  float updateRate = 0.15f;

  //Textures
  sf::Texture spriteSheet;
};

#endif // SFMLGAME_CHARACTER_H
