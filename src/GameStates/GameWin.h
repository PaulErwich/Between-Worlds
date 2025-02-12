//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMEWIN_H
#define SFMLGAME_GAMEWIN_H

#include "GameStateBase.h"

class GameWin : public GameStateBase
{
 public:
  GameWin();
  GameWin(State _state, GameData& _game_data);

  bool init() override;
  void onEnter() override;
  void onExit() override;
  void keyboard_input(sf::Event event) override;
  void mouse_input(sf::Event event) override;
  State update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
  sf::Sprite background_;
  sf::Texture backgroundTexture;
  sf::Text winText_, exitText, playAgainText;
  //Font
  sf::Font font;
  int middleX;
  int middleY;

  sf::Sprite selectionSprite;
  sf::Texture selectionTexture;

  std::vector<sf::Text> classTexts;

};

#endif // SFMLGAME_GAMEWIN_H
