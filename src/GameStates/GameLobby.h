//
// Created by MLG Erwich on 02/03/2023.
//

#ifndef SFMLGAME_GAMELOBBY_H
#define SFMLGAME_GAMELOBBY_H

#include "GameStateBase.h"
#include <list>

class GameLobby : public GameStateBase
{
 public:
  GameLobby();
  GameLobby(State _state, GameData& _game_data);

  bool init() override;
  void onEnter() override;
  void onExit() override;
  void keyboard_input(sf::Event event) override;
  void mouse_input(sf::Event event) override;
  State update(float dt) override;
  void render(sf::RenderWindow& window) override;
  void textEntered(sf::Event event) override;
  void loadConnections();
  void displayConnected();

 private:
  typedef std::list<sf::Sprite *> SpriteList;
  typedef std::list<sf::Text *> TextList;

  SpriteList spriteList;
  TextList textList;

  int middleX;
  int middleY;

  // Game Name
  std::unique_ptr<sf::Sprite> gameLogo;
  std::unique_ptr<sf::Texture> gameLogoTexture;

  //Font
  sf::Font font;

  // Join Text
  sf::Text joinText;
  // Host Text
  sf::Text hostText;
  // IP Text
  sf::Text ipText;
  std::string stringIP;
  sf::Text selectedChar;
  //sf::RectangleShape* textSelection;
  bool selectionActive = false;
  sf::Vector2f startingPos;
  sf::Vector2f endPos;
  std::string selectedText;
  int const BACKSPACE = 8;
  int const ESCAPE = 13;
  std::string ipTextBuffer;


  // Sprites
  // Selection sprite
  sf::Sprite selectionSprite;
  sf::Texture selectionTexture;
  sf::Texture otherplayerTexture;

  sf::Shader bgShader, logoShader;
  sf::Sprite Background, logoBG;
  sf::Texture backgroundTexture;
  sf::Clock clock;

  // scale the waves
  float scaleWaves = 1.0f;


  // Text box
  std::unique_ptr<sf::RectangleShape> textBox;

  // Lobby box
  std::unique_ptr<sf::RectangleShape> lobbyBox;
  std::unique_ptr<sf::RectangleShape> startButton, returnButton;

  std::unique_ptr<sf::Text> lobbyMainText, returnText, startText;

  bool openLobbyBox = false;
  bool loadOnce = true;
  bool clientConnected = false;
  sf::Text connectionText;
  //int playersConnected = 1;
  sf::Text playerJoined;
  float alphaAdd = 0;

  //Joined
  sf::Text waitingText;

};

#endif // SFMLGAME_GAMELOBBY_H
