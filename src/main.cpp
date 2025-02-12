#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1440, 720), "Between 3 Worlds");
  window.setFramerateLimit(60);

  // Set the initial view
  sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
  window.setView(view);

  //initialise an instance of the game class
  Game game(window);

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  bool focus = true;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        game.shutServer();
        window.close();
      }

      if (event.type == sf::Event::LostFocus)
      {
        std::cout << "lost focus" << std::endl;
        focus = false;
      }

      if (event.type == sf::Event::GainedFocus)
      {
        std::cout << "gained focus" << std::endl;
        focus = true;
      }

      if (focus)
      {
        if (event.type == sf::Event::KeyPressed)
          game.keyboard_input(event);

        if (event.type == sf::Event::KeyReleased)
          game.keyboard_released(event);

        if (event.type == sf::Event::MouseButtonPressed)
          game.mouse_input(event);

        if (event.type == sf::Event::MouseMoved)
          game.mouse_input(event);

        if (event.type == sf::Event::TextEntered)
          game.textEntered(event);
      }
    }


    if (focus)
    {
      //'update' element of the game loop
      game.update(dt);

      window.clear(sf::Color::Black);

      //'render' element of the game loop
      if (window.isOpen())
      {
        game.render();
        window.display();
      }
    }

  }

  return 0;
}
