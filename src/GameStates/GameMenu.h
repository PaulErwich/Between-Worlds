//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMEMENU_H
#define SFMLGAME_GAMEMENU_H

#include "GameStateBase.h"
#include <SFML/Audio.hpp>
#include <list>

class GameMenu : public GameStateBase
{
 public:
  GameMenu();
  GameMenu(State _state, GameData& _game_data);

  bool init() override;
  void onEnter() override;
  void onExit() override;
  void keyboard_input(sf::Event event) override;
  void mouse_input(sf::Event event) override;
  State update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
  // window size
  float windowMX;
  float windowYX;

  sf::SoundBuffer menu_buffer;
  sf::Sound menu_music;

  typedef std::list<sf::Text *> TextList;
  TextList textList;

  sf::Clock clock;

  // Background
  sf::Sprite background, logoBG;
  sf::Sprite vignette;
  sf::Sprite backgroundLayer1, backgroundLayer2;
  sf::Texture backgroundLayer1Texture, backgroundLayer2Texture;
  sf::Texture backgroundTexture;

  sf::Sprite WorldsSprites;
  sf::Texture WorldTexture;

  // Text
  sf::Font fontOpenSans;

  sf::Text gameName_;
  sf::Text playText;
  sf::Text exitText;

  // Shader test
  sf::Shader shader, shaderVignette, NoiseShader, logoShader;


  // Selection
  sf::Sprite selectionSprite;
  sf::Texture selectionTexture;
};

#endif // SFMLGAME_GAMEMENU_H
