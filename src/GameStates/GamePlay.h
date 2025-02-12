//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMEPLAY_H
#define SFMLGAME_GAMEPLAY_H

#include "GameStateBase.h"
#include "../GameObjects/Switch.h"
#include "../GameObjects/Puzzle.h"
#include "../GameObjects/Pressureplate.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/Portal.h"


#include "../LevelLoading/LevelData.h"

#include "../Camera/Camera.h"

//#include "Collectible.h"
#include <vector>

class GamePlay : public GameStateBase
{
 public:
  GamePlay();
  GamePlay(State _state, GameData& _game_data);

  bool init() override;
  void onEnter() override;
  void onExit() override;
  void keyboard_input(sf::Event event) override;
  void keyboard_release(sf::Event event) override;
  void mouse_input(sf::Event event) override;
  State update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void spawn();
  void loadAudio(const std::string& filepath);


 private:
  sf::Text life_text;
  sf::Text life_text2;
  sf::Font font;
  sf::SoundBuffer death_buffer;
  sf::Sound death_sound;

  //std::unique_ptr<LevelData> level_test;

  std::unique_ptr<Camera> camera;
  bool WallCollisions();
  int life = 3;

  void PushBlock(float dt);

  //std::unique_ptr<GameObject> end_point;

  // bg
  sf::Texture bgTexture;
  sf::Sprite bgSprite;

  // portal
  std::unique_ptr<Portal> portalBlue;
  //std::unique_ptr<Portal> portalRed;

};

#endif // SFMLGAME_GAMEPLAY_H
