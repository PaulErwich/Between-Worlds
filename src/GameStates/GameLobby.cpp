//
// Created by MLG Erwich on 02/03/2023.
//

#include "GameLobby.h"
#include "../Other/Helper.h"

GameLobby::GameLobby()
{
  state = State::GAME_LOBBY;
}

GameLobby::GameLobby(State _state, GameData& _game_data) :
  GameStateBase(_state, _game_data)
{
}

bool GameLobby::init()
{
  if (!bgShader.loadFromFile("Data/Shaders/bgShader.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  if (!logoShader.loadFromFile("Data/Shaders/FogBG.glsl", sf::Shader::Fragment))
  {
    std::cout << "Failed to load shader\n";
  }
  if (!backgroundTexture.loadFromFile("Data/Images/emptyBG.png"))
  {
    std::cout << "Failed to load background\n";
  }
  Background.setTexture(backgroundTexture);
  logoBG.setTexture(backgroundTexture);

  bgShader.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x * 0.5f, game_data->window->getSize().y * 0.5f + 20.0f));
  logoShader.setUniform("resolution", sf::Vector2f(game_data->window->getSize().x, game_data->window->getSize().y+300.0f));
  logoShader.setUniform("scale", 0.5f);
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Failed to load font";
    return false;
  }
  middleX = game_data->window->getSize().x * 0.5f;
  middleY = game_data->window->getSize().y * 0.5f;

  gameLogoTexture = std::make_unique<sf::Texture>();
  gameLogoTexture->loadFromFile("Data/Images/BetweenWorldsPlanes.png");

  gameLogo = std::make_unique<sf::Sprite>();
  gameLogo->setTexture(*gameLogoTexture);
  gameLogo->setScale(0.4f, 0.4f);
  gameLogo->setPosition(middleX - gameLogo->getGlobalBounds().width * 0.5f, -10);
  spriteList.push_back(gameLogo.get());


  Helper::Generate(joinText, "Join Server", font, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0, 0), 60);
  joinText.setPosition(sf::Vector2f(middleX - (joinText.getGlobalBounds().width * 1.5f), middleY + 140.0f));
  textList.push_back(&joinText);

  Helper::Generate(hostText, "Host Server", font, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0,0), 60);
  hostText.setPosition(sf::Vector2f(middleX + (hostText.getGlobalBounds().width * 0.5f), middleY + 140.0f));
  textList.push_back(&hostText);

  Helper::Generate(selectionSprite, selectionTexture, "Data/Images/selection.png", sf::Vector2f(-100,-100), sf::Vector2f(0.6f,0.6f));
  spriteList.push_back(&selectionSprite);

  textBox = std::make_unique<sf::RectangleShape>();
  textBox->setSize(sf::Vector2f(350.f,70.0f));
  textBox->setFillColor(sf::Color::White);
  textBox->setPosition(sf::Vector2f(middleX - textBox->getGlobalBounds().width * 0.5f, joinText.getPosition().y - textBox->getGlobalBounds().height * 2 + 40));

  Helper::Generate(ipText, "Enter IP", font, sf::Color::Black,sf::Vector2f(0,0), 40);
  textList.push_back(&ipText);

  Helper::Generate(waitingText, "Waiting for host!", font, sf::Color(135.0f, 101.0f, 62), sf::Vector2f (-100,-100), 60);

  Helper::Generate(connectionText, "", font, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0,0), 30);
  connectionText.setPosition(sf::Vector2f(middleX, middleY));

  lobbyBox = std::make_unique<sf::RectangleShape>();
  lobbyBox->setSize(sf::Vector2f(500.0f, 200.0f));
  lobbyBox->setFillColor(sf::Color::White);
  lobbyBox->setPosition(sf::Vector2f(middleX - lobbyBox->getGlobalBounds().width * 0.5f, middleY - lobbyBox->getGlobalBounds().height * 0.5f));

  startButton = std::make_unique<sf::RectangleShape>();
  startButton->setSize(sf::Vector2f(200.0f, 60.0f));
  startButton->setFillColor(sf::Color(135.0f, 101.0f, 62));
  startButton->setPosition(sf::Vector2f(lobbyBox->getPosition().x + lobbyBox->getGlobalBounds().width - startButton->getGlobalBounds().width, lobbyBox->getPosition().y + lobbyBox->getGlobalBounds().height + 20.0f));

  returnButton = std::make_unique<sf::RectangleShape>();
  returnButton->setSize(sf::Vector2f(200.0f, 60.0f));
  returnButton->setFillColor(sf::Color(135.0f, 101.0f, 62));
  returnButton->setPosition(sf::Vector2f(lobbyBox->getPosition().x, lobbyBox->getPosition().y + lobbyBox->getGlobalBounds().height + 20.0f));

  Helper::Generate(playerJoined, "", font, sf::Color(135.0f, 101.0f, 62, 0), sf::Vector2f(0,0), 30);

  lobbyMainText = std::make_unique<sf::Text>();
  Helper::Generate(*lobbyMainText, "Host Server", font, sf::Color(135.0f, 101.0f, 62), sf::Vector2f(0,0), 60);
  lobbyMainText->setPosition(middleX - lobbyMainText->getGlobalBounds().width * 0.5f,lobbyBox->getPosition().y - lobbyMainText->getGlobalBounds().height - 80.0f);

  returnText = std::make_unique<sf::Text>();
  Helper::Generate(*returnText, "Return", font, sf::Color::White, sf::Vector2f(0,0), 30);
  returnText->setPosition(returnButton->getPosition().x + returnButton->getGlobalBounds().width * 0.5f - returnText->getPosition().x - returnText->getGlobalBounds().width * 0.5f, startButton->getPosition().y + startButton->getGlobalBounds().height * 0.5f - returnText->getPosition().y + returnText->getGlobalBounds().height * 0.5f - 30.0f);

  startText  = std::make_unique<sf::Text>();
  Helper::Generate(*startText, "Start", font, sf::Color::White, sf::Vector2f(0,0), 30);
  startText->setPosition(startButton->getPosition().x + startButton->getGlobalBounds().width * 0.5f - startText->getPosition().x - startText->getGlobalBounds().width * 0.5f, startButton->getPosition().y + startButton->getGlobalBounds().height * 0.5f - startText->getPosition().y + startText->getGlobalBounds().height * 0.5f - 30.0f);


  if (!otherplayerTexture.loadFromFile("Data/Images/Whisper.png"))
  {
    std::cout<<"did not load texture"<<std::endl;
  }

  return GameStateBase::init();
}

void GameLobby::onEnter()
{
  GameStateBase::onEnter();
}

void GameLobby::onExit()
{
  alphaAdd = 0;
  openLobbyBox = false;
  loadOnce = true;
  stringIP = "0.0.0.0";
  joinText.setPosition(sf::Vector2f(middleX - (joinText.getGlobalBounds().width * 1.5f), middleY + 140.0f));
  hostText.setPosition(sf::Vector2f(middleX + (hostText.getGlobalBounds().width * 0.5f), middleY + 140.0f));
  scaleWaves = 1.0f;
  GameStateBase::onExit();
}

void GameLobby::keyboard_input(sf::Event event)
{
  // Deletes the text character
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && stringIP.length() != 0)
  {
    stringIP.erase(stringIP.size() - 1);
    ipText.setString(stringIP);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    state = State::GAME_PLAY;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
  {
    clientConnected = true;
  }

  GameStateBase::keyboard_input(event);
}

void GameLobby::mouse_input(sf::Event event)
{
  // Test selection
  //  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
  //  {
  //    sf::Vector2f mousePos = game_data->Window->mapPixelToCoords(sf::Mouse::getPosition(*game_data->Window));
  //
  //    if (ipText.getGlobalBounds().contains(mousePos))
  //    {
  //      sf::Vector2f startingPos(mousePos);
  //      sf::Vector2f endPos;
  //
  //      textSelection = new sf::RectangleShape;
  //      textSelection->setFillColor(sf::Color::Blue);
  //      textSelection->setPosition(startingPos);
  //      textSelection->setSize(sf::Vector2f(0, 0));
  //      selectionActive = true;
  //
  //      sf::Vector2f selectionSize = endPos - startingPos;
  //      sf::Vector2f selectionPos  = startingPos;
  //    }
  //  }
  //  else if(event.type == sf::Event::MouseButtonReleased)
  //  {
  //    std::cout << " released " << std::endl;
  //    delete textSelection;
  //    textSelection = nullptr;
  //    selectionActive = false;
  //  }
  Helper::InsideButton(event, *startButton, sf::Color(135.0f, 101.0f, 62), *startText, sf::Color::White);
  Helper::InsideButton(event, *returnButton, sf::Color(135.0f, 101.0f, 62), *returnText, sf::Color::White);
  if (Helper::InsideText(event, joinText))
  {
    selectionSprite.setPosition(joinText.getPosition() + sf::Vector2f(-5, 55.f));
  }
  else if (Helper::InsideText(event, hostText))
  {
    selectionSprite.setPosition(hostText.getPosition() + sf::Vector2f(0, 55.f));
  }
  else
  {
    selectionSprite.setPosition(sf::Vector2f(-100, -100.f));
  }
  /// If clicked on the Join Server button
  if (Helper::ClickedOnText(event, joinText))
  {
    // Change it to the right ip to connect to the server.
    //if (stringIP == "127.0.0.1")
    {
      std::cout << "confirmed" << std::endl;

      game_data->client->initialConnect(stringIP);

      game_data->controlled_player = ControlledPlayer::PLAYER_TWO;
      game_data->other_player      = ControlledPlayer::PLAYER_ONE;
      clientConnected              = true;
      hostText.setPosition(sf::Vector2f(-100, -100));
      joinText.setPosition(sf::Vector2f(-100, -100));
      waitingText.setPosition(
        middleX - waitingText.getGlobalBounds().width * 0.5,
        textBox->getPosition().y + textBox->getGlobalBounds().height + 20.0f);
      game_data->players[game_data->other_player]->setTexture(otherplayerTexture);
    }
  }
  /// If clicked on the Host Server button
  if (Helper::ClickedOnText(event, hostText))
  {
    if (game_data->server == nullptr)
    {
      game_data->server = std::make_unique<Server>();

      std::thread server_thread ([&]{game_data->server->run();});
      server_thread.detach();

      game_data->client->initialConnect("127.0.0.1");

      game_data->controlled_player = ControlledPlayer::PLAYER_ONE;
      game_data->other_player = ControlledPlayer::PLAYER_TWO;

      if (!otherplayerTexture.loadFromFile("Data/Images/Whisper.png"))
      {
        std::cout<<"did not load texture"<<std::endl;
      }
      game_data->players[game_data->other_player]->setTexture(otherplayerTexture);

    }
    openLobbyBox = true;
  }
  if (Helper::ClickedOnButton(event, *startButton) && openLobbyBox)
  {
    std::cout << "clicked" << std::endl;
    if (game_data->server->getPlayersConnected() == 2)
    {
      game_data->client->sendStateUpdate(State::GAME_PLAY);

      state = State::GAME_PLAY;
    }
  }
  if (Helper::ClickedOnButton(event, *returnButton) && openLobbyBox)
  {
    openLobbyBox = false;
    game_data->server->shutdownServer();
    game_data->server = nullptr;
  }
  GameStateBase::mouse_input(event);
}

State GameLobby::update(float dt)
{
  logoShader.setUniform("time", clock.getElapsedTime().asSeconds());
  bgShader.setUniform("time", clock.getElapsedTime().asSeconds() * scaleWaves);
  //  if (selectionActive)
  //  {
  //    sf::Vector2f currentPos = game_data->Window->mapPixelToCoords(sf::Mouse::getPosition(*game_data->Window));
  //    sf::Vector2f startPos = textSelection->getPosition();
  //    textSelection->setSize(currentPos - startPos);
  //  }

  if (game_data->server != nullptr)
  {
    if (game_data->server->getPlayersConnected() == 2)
    {
      displayConnected();
      scaleWaves = 6.0f;
    }
    loadConnections();
  }
  ipText.setPosition(
    (textBox->getPosition().x + textBox->getGlobalBounds().width * 0.5f) -
      ipText.getGlobalBounds().width * 0.5f,
    textBox->getPosition().y + textBox->getGlobalBounds().height * 0.5f -
      ipText.getGlobalBounds().height);
  return state;
}

void GameLobby::render(sf::RenderWindow& window)
{
  if (!openLobbyBox)
  {
    window.draw(logoBG, &logoShader);
  }
  window.draw(Background, &bgShader);
  //  if (textSelection != nullptr)
  //  {
  //    window.draw(*textSelection);
  //  }
  if (!openLobbyBox)
  {
    window.draw(*textBox);
    for (TextList::const_iterator textListIt = textList.begin(),
                                  end        = textList.end();
         textListIt != end;
         ++textListIt)
    {
      window.draw(*textListIt.operator*());
    }
    for (SpriteList::const_iterator spriteListIt = spriteList.begin(),
                                    end          = spriteList.end();
         spriteListIt != end;
         ++spriteListIt)
    {
      window.draw(*spriteListIt.operator*());
    }
    window.draw(waitingText);
  }
  if (openLobbyBox)
  {
    window.draw(*lobbyBox);
    window.draw(*startButton);
    window.draw(*startText);
    window.draw(*lobbyMainText);
    window.draw(*returnButton);
    window.draw(*returnText);
    if (game_data->server->getPlayersConnected() == 2)
    {
      window.draw(playerJoined);
    }
    window.draw(connectionText);
  }
  GameStateBase::render(window);
}
void GameLobby::textEntered(sf::Event event)
{
  // Add the ip to the screen
  if ((std::isdigit(static_cast<char>(event.text.unicode)) || event.text.unicode == '.') && event.text.unicode != BACKSPACE && event.text.unicode != ESCAPE && stringIP.length() < 15)
  {
    stringIP += event.text.unicode;

    ipText.setString(stringIP);
  }
  GameStateBase::textEntered(event);
}

void GameLobby::loadConnections()
{
  int clientID =
    game_data->controlled_player == ControlledPlayer::PLAYER_ONE ? 1 : 2;
  std::string ipAddress = sf::IpAddress::getLocalAddress().toString();
  //std::string ipAddress = "127.0.0.1";
  if (loadOnce && openLobbyBox)
  {
    connectionText.setString(
      "Client " + std::to_string(clientID) + " : " + ipAddress + "        |  " + std::to_string(game_data->server->getPlayersConnected()) + "/2");
    connectionText.setPosition(lobbyBox->getPosition());
    playerJoined.setString("Player 2 joined");
    playerJoined.setPosition(connectionText.getPosition().x + 60.0f, connectionText.getPosition().y + connectionText.getGlobalBounds().height);
    loadOnce = false;
  }
  connectionText.setString(
    "Client " + std::to_string(clientID) + " : " + ipAddress + "        |  " + std::to_string(game_data->server->getPlayersConnected() < 2 ? game_data->server->getPlayersConnected() : 2) + "/2");
}
void GameLobby::displayConnected()
{
  if (alphaAdd < 255)
  {
    std::cout << alphaAdd << std::endl;
    playerJoined.setFillColor(sf::Color( 135.0f, 101.0f, 62,alphaAdd));
    alphaAdd += 20;
  }
}
