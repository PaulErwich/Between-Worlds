#ifndef SFMLGAME_HELPER_H
#define SFMLGAME_HELPER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Helper
{
  public:
  ///  @brief Generate a text and place it at given position
  /// \param varName: Text variable name
  /// \param string: The string that will be displayed
  /// \param font: Font
  /// \param color: Text colour
  /// \param pos: Position where it will be placed
  /// \param characterSize: Size of the letters
  static void Generate(sf::Text& varName, const std::string string, sf::Font& font, const sf::Color& color, sf::Vector2f pos, int characterSize)
  {
    varName.setString(string);
    varName.setFont(font);
    varName.setFillColor(color);
    varName.setPosition(pos);
    varName.setCharacterSize(characterSize);
  }


  ///  @brief Generate a sprite.
  /// \param sprite: Sprite variable
  /// \param texture: Texture variable
  /// \param filename: file name / Path
  /// \param pos: position
  /// \param scale: scale
  static void Generate(sf::Sprite& sprite, sf::Texture& texture, const std::string& filename, sf::Vector2f pos, sf::Vector2f scale)
  {
    if (!texture.loadFromFile(filename))
    {
      std::cout << "Failed to load texture " + filename << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(scale);
  }

  static bool ClickedOnButton(sf::Event& event, sf::RectangleShape& button)
  {
    if ((float)event.mouseButton.x > button.getPosition().x &&
        (float)event.mouseButton.x < button.getPosition().x + button.getGlobalBounds().width &&
        (float)event.mouseButton.y > button.getPosition().y &&
        (float)event.mouseButton.y < button.getPosition().y + button.getGlobalBounds().height)
    {
      return true;
    }
    return false;
  }

/// @brief Check if the mouse is inside the text bounds
/// \param event: mouse event click
/// \param text: Text variable
/// \return Bool
  static bool ClickedOnText(sf::Event& event, sf::Text& text)
  {
    if ((float)event.mouseButton.x > text.getPosition().x &&
        (float)event.mouseButton.x < text.getPosition().x + text.getGlobalBounds().width &&
        (float)event.mouseButton.y > text.getPosition().y &&
        (float)event.mouseButton.y < text.getPosition().y + text.getGlobalBounds().height)
    {
      return true;
    }
    return false;
  }
  /// @brief Check if the mouse is inside the text bounds
  /// \param event: mouse event click
  /// \param text: Text variable
  /// \return Bool
  static bool InsideText(sf::Event& event, sf::Text& text)
  {
    if ((float)event.mouseMove.x > text.getPosition().x &&
        (float)event.mouseMove.x < text.getPosition().x + text.getGlobalBounds().width &&
        (float)event.mouseMove.y > text.getPosition().y &&
        (float)event.mouseMove.y < text.getPosition().y + text.getGlobalBounds().height)
    {
      return true;
    }
    return false;
  }

  /// @brief Get text center position
  /// \param text: text variable
  /// \param screenSizeX: window size X
  /// \return int
  static int GetTextCenter(sf::Text& text, int screenSizeX)
  {
    return screenSizeX - (text.getGlobalBounds().width * 0.5f);
  }

  static int Randomize(int min, int max)
  {
    int value = min + rand() / (RAND_MAX / (max - min));
    return value;
  }

  static void InsideButton(sf::Event& event, sf::RectangleShape& button, sf::Color color, sf::Text& text, sf::Color textColor)
  {
    sf::Color temp = button.getFillColor();
    if ((float)event.mouseMove.x > button.getPosition().x &&
        (float)event.mouseMove.x < button.getPosition().x + button.getGlobalBounds().width &&
        (float)event.mouseMove.y > button.getPosition().y &&
        (float)event.mouseMove.y < button.getPosition().y + button.getGlobalBounds().height)
    {
      text.setFillColor(sf::Color::Black);
      button.setFillColor(sf::Color::White);
    }
    else
    {
      button.setFillColor(color);
      text.setFillColor(textColor);
    }
  }
};


#endif // SFMLGAME_HELPER_H
