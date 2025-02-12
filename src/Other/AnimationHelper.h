//
// Created by luria on 17/03/2023.
//

#ifndef SFMLGAME_ANIMATIONHELPER_H
#define SFMLGAME_ANIMATIONHELPER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimationState.h"

class AnimationHelper
{
 public:
  static sf::Vector2f
  MoveAnimation(sf::Vector2f initialPos, sf::Vector2f finalPos, float alpha)
  {
    return initialPos + alpha * (finalPos - initialPos);
  }

  static void DoAnimation(
    sf::Sprite& sprite, float updateRate, sf::IntRect& currentFrame,
    sf::Clock* timer, AnimationState animationState)
  {
    //AnimationState lastAnimationState;
    if (timer->getElapsedTime().asSeconds() >= updateRate)
    {
      int spriteSize = 32;
      int spriteHeight = 34;
      int spriteSheetSize;
      int blankSpace;

      if (animationState == IDLE)
      {
        currentFrame.top = 0; // Top of the sheet;
        spriteSheetSize = 128;
      }
      if (animationState == MOVING_LEFT || animationState == MOVING_RIGHT)
      {
        currentFrame.top = spriteHeight;
        spriteSheetSize = 192;
      }
      if (animationState == JUMPING)
      {
        currentFrame.top = spriteHeight * 3;
        spriteSheetSize = 128;
      }
      if (animationState == INTERACTING)
      {
        currentFrame.top = spriteHeight * 3;
      }
      if (animationState == PUSHING)
      {
        //currentFrame.top = spriteHeight * 4;
      }

      currentFrame.left += spriteSize; // Top left of the sprite sheet
      currentFrame.width = spriteSize; // Sprite size
      if (currentFrame.left >= spriteSheetSize) // Max left of the sprite sheet
      {
        currentFrame.left = 0;
      }

      timer->restart();
      sprite.setTextureRect(currentFrame);
    }
  }
};

#endif // SFMLGAME_ANIMATIONHELPER_H
