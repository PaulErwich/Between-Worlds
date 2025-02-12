//
// Created by MLG Erwich on 02/03/2023.
//

#include "GameMenu.h"


GameMenu::GameMenu()
{
  state = State::GAME_MENU;
}

GameMenu::GameMenu(State _state, GameData& _game_data) :
  GameStateBase(_state, _game_data)
{

}

bool GameMenu::init()
{
  if (!menu_buffer.loadFromFile("Data/Sounds/Weaponized Smiles.wav"))
  {
    std::cout << "audioerror";
  }
  menu_music.setBuffer(menu_buffer);
  //UNCOMMENT HERE FOR MENU MUSIC
  //menu_music.play();
  clock.restart();
  if (!backgroundTexture.loadFromFile("Data/Images/emptyBG.png"))
  {
    std::cout << "Failed to load background\n";
  }
  background.setTexture(backgroundTexture);
  vignette.setTexture(backgroundTexture);

  if (!WorldTexture.loadFromFile("Data/Images/Worlds.png"))
  {
    std::cout << "Failed to load background\n";
  }

  if (!fontOpenSans.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Failed to load font";
    return false;
  }

  if (!shader.loadFromFile("Data/Shaders/bgShader.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  shader.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x * 0.5f, game_data->window->getSize().y * 0.5f));

  if (!shaderVignette.loadFromFile("Data/Shaders/vignette.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  shaderVignette.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x, game_data->window->getSize().y));
  if (!logoShader.loadFromFile("Data/Shaders/FogBG.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  logoBG.setTexture(backgroundTexture);
  logoShader.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x, game_data->window->getSize().y+300.0f));
  logoShader.setUniform("scale", 1.0f);

  windowMX = game_data->window->getSize().x * 0.5f;
  windowYX = game_data->window->getSize().y * 0.5f;

  backgroundLayer1Texture.loadFromFile("Data/Images/BetweenWorldsBehindLayer.png");
  backgroundLayer1.setTexture(backgroundLayer1Texture);
  backgroundLayer1.setScale(sf::Vector2f(0.67f,0.6f));
  backgroundLayer1.setPosition(windowMX - backgroundLayer1.getGlobalBounds().width / 2.f,
                              windowYX- backgroundLayer1.getGlobalBounds().height / 1.54f);


  backgroundLayer2Texture.loadFromFile("Data/Images/BetweenWorlds.png");
  backgroundLayer2.setTexture(backgroundLayer2Texture);
  backgroundLayer2.setScale(sf::Vector2f(0.65f,0.6f));
  backgroundLayer2.setPosition(windowMX - backgroundLayer2.getGlobalBounds().width / 2.f,
                               windowYX- backgroundLayer2.getGlobalBounds().height / 1.54f);


  //WorldTexture.loadFromFile("Data/Images/BetweenWorldsTopLayer.png");
  WorldsSprites.setTexture(WorldTexture);
  WorldsSprites.setScale(sf::Vector2f(1.7f,0.6f));
  WorldsSprites.setPosition(windowMX - WorldsSprites.getGlobalBounds().width / 2.0f,
                               10);

  if (!NoiseShader.loadFromFile("Data/Shaders/NoiseShader2D.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  NoiseShader.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x, game_data->window->getSize().y));
  NoiseShader.setUniform("texture", WorldTexture);
  //NoiseShader.setUniform("offset", sf::Vector2f(100, 10));




  Helper::Generate(gameName_, "Between Worlds", fontOpenSans, sf::Color::White, sf::Vector2f(0.0f, 0.0f), 64);
  gameName_.setPosition(sf::Vector2f(Helper::GetTextCenter(gameName_, windowMX), 50.0f));
  //textList.push_back(&gameName_);

  Helper::Generate(playText, "Play", fontOpenSans, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0.0f, 0.0f), 48);
  playText.setPosition(sf::Vector2f(Helper::GetTextCenter(playText, windowMX), Helper::GetTextCenter(playText, windowYX) + 180.0f));
  textList.push_back(&playText);

  Helper::Generate(exitText, "Exit", fontOpenSans, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0.0f, 0.0f), 48);
  exitText.setPosition(sf::Vector2f(Helper::GetTextCenter(exitText, windowMX), Helper::GetTextCenter(exitText, windowYX) + 280.0f));
  textList.push_back(&exitText);

  Helper::Generate(selectionSprite, selectionTexture, "Data/Images/selection.png", sf::Vector2f(-100,-100), sf::Vector2f(0.2f,0.2f));


  return GameStateBase::init();
}

void GameMenu::onEnter()
{
  GameStateBase::onEnter();
}

void GameMenu::onExit()
{
  GameStateBase::onExit();
}

void GameMenu::keyboard_input(sf::Event event)
{
  GameStateBase::keyboard_input(event);
}

void GameMenu::mouse_input(sf::Event event)
{
    if (Helper::InsideText(event, playText))
    {
      selectionSprite.setPosition(playText.getPosition() + sf::Vector2f(-5, 55.f));
    }
    else if (Helper::InsideText(event, exitText))
    {
      selectionSprite.setPosition(exitText.getPosition() + sf::Vector2f(-10, 55.f));
    }
    else
    {
      selectionSprite.setPosition(sf::Vector2f(-100, -100.f));
    }
    if (Helper::ClickedOnText(event, playText))
    {
      state = State::GAME_LOBBY;
    }

    if (Helper::ClickedOnText(event, exitText))
    {
      game_data->window->close();
    }
}

State GameMenu::update(float dt)
{
  logoShader.setUniform("time", clock.getElapsedTime().asSeconds());
  shader.setUniform("time", clock.getElapsedTime().asSeconds());
  NoiseShader.setUniform("time", clock.getElapsedTime().asSeconds());
  return state;
}

void GameMenu::render(sf::RenderWindow& window)
{
  window.draw(logoBG, &logoShader);
  window.draw(WorldsSprites, &NoiseShader);
  //window.draw(backgroundLayer1);
  window.draw(background, &shader);
  window.draw(backgroundLayer2);
  window.draw(vignette, &shaderVignette);
  for (TextList::const_iterator textListIt = textList.begin(), end = textList.end(); textListIt != end; ++textListIt)
  {
    window.draw(*textListIt.operator*());
  }


  window.draw(selectionSprite);
  GameStateBase::render(window);
}