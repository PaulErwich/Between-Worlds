//
// Created by 44749 on 10/03/2023.
//
#include "Character.h"
#include <cmath>
#include "../Other/AnimationHelper.h"

Character::Character(
  std::string filename, sf::Vector2f pos, sf::RenderWindow& game_window) :
  GameObject(filename, pos), window(game_window)
{
  //Setting up player
  sprite->scale(2.0f, 2.0f);

  Helper::Generate(*sprite, spriteSheet, filename, pos, sprite->getScale());
  currentFrame = sf::IntRect(0,0,32,34);
  sprite->setTextureRect(sf::IntRect(currentFrame));

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  setMin();
  calculateMax();

  loadAudio();

}


void Character::update(float dt)
{

  newPos = updatePosition(dt);
  calculate_gravity();
  // LeftRightMove unnecessary
  velocityVector = velocity;

  //Check isGrounded for jump animation
  if (!isGrounded)
  {
    currentAnimState = JUMPING;
  }
  else
  {
    if(velocity.x == 0)
    {
      currentAnimState = IDLE;
    }
  }


  //Temp ground
  /*if (newPos.y + height >= window.getSize().y *0.5f)
  {
    isGrounded = true;
    velocity.y = 0;
  }*/



  sprite->setPosition(updatePosition(dt));
  // move player
  setMin();
  calculateMax();
  //animationSprites();
  MovePlayer(dt);
  pushing();
  interacting();


  AnimationHelper::DoAnimation(*sprite, updateRate,
    currentFrame, &idle_animation_tick, currentAnimState);
}

sf::Vector2f Character::updatePosition(float dt)
{
  sf::Vector2f normalisedVector;
  float length = sqrt((velocityVector.x * velocityVector.x) + (velocityVector.y * velocityVector.y));

  if(length != 0)
    normalisedVector = sf::Vector2f(velocityVector.x / length, velocityVector.y / length);
  sf::Vector2f  newPosition = sprite->getPosition() + ((normalisedVector * movementSpeed) * dt);

  //sprite->move(normalisedVector * movementSpeed * dt)

  //sf::Vector2f newPosition = sprite->getPosition() + ((normalisedVector * movementSpeed) * dt);

  return newPosition;
}

void Character::key_pressed(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
    {
      if (!playing)
      {
        footsteps_sound.setLoop(true);
        footsteps_sound.play();
        playing = true;
      }
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      footsteps_sound.stop();
    }
  }
}

void Character::key_released(sf::Event event)
{
  if (event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
    {
      footsteps_sound.stop();
      playing = false;
    }
  }
}

void Character::calculate_gravity()
{
  if (!isGrounded)
  {
    velocity.y = velocity.y + gravity;
  }
}
void Character::MovePlayer(float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -30)
  {
    move(-60, 0, dt, 80.f, 1.f, 3.f, .93f);
    sprite->setScale(-2.0f, 2.0f);
    sprite->setOrigin(sprite->getGlobalBounds().width / 2.0f, 0);
    if (isGrounded)
    {
      currentAnimState = MOVING_LEFT;
      updateRate = 0.1f;
    }
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
           sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 30)
  {
    move(60, 0, dt, 80.f, 1.f, 3.f, .93f);
    sprite->setScale(2.0f, 2.0f);
    sprite->setOrigin(sf::Vector2f(0,0));
    if (isGrounded)
    {
      currentAnimState = MOVING_RIGHT;
      updateRate = 0.1f;
    }
  }
  else
  {
    if (isGrounded)
    {
      velocity.x = 0;
      currentAnimState = IDLE;
      updateRate = 0.22f;
    }
  }
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) ||
      (sf::Joystick::isButtonPressed(0, 1) && isGrounded))
  {
    jump_sound.play();
    isGrounded = false;
    velocity.y = -1.5 * jumpForce;
    updateRate = 0.24f;
  }
}

void Character::loadAudio()
{
  if (!jump_buffer.loadFromFile("Data/Sounds/Jumpsfx.wav"))
  {
    std::cout << "audioerror";
  }
  else
  {
    jump_sound.setBuffer(jump_buffer);
  }

  if (!footsteps_buffer.loadFromFile("Data/Sounds/steps_chain.ogg"))
  {
    std::cout << "audioerror";
  }
  else
  {
    footsteps_sound.setBuffer(footsteps_buffer);
  }
}

void Character::pushing()
{
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && isGrounded) ||
      (sf::Joystick::isButtonPressed(0, 0) && isGrounded))
  {
    movementSpeed = pushingSpeed;

    //Animation not set up yet
    currentAnimState = PUSHING;
  }
  else
  {
    movementSpeed = normalSpeed;
  }
}

void Character::interacting()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
  {
    std::cout << "interacting" << std::endl;

    //Animation not set up yet
    currentAnimState = INTERACTING;
  }
}

void Character::move(
  float x, float y, float dt, float max_velocity, float min_velocity,
  float acceleration, float deceleration)
{
  velocity.x *= deceleration;


  if (std::abs(velocity.x) < min_velocity)
  {
    velocity.x = 0.f;
  }
  sprite->move(velocity * dt);

  velocity.x += x * acceleration;

  if (std::abs(velocity.x) > max_velocity)
  {
    velocity.x = max_velocity * ((velocity.x < 0.f) ? -1.f : 1.f);
  }

}

void Character::setTexture(sf::Texture& _texture)
{
  sprite->setTexture(_texture);
  sprite->setScale(1, 1);

  sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;
  setMin();
  calculateMax();
}
