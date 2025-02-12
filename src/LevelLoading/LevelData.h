//
// Created by perwi on 07/03/2023.
//

#ifndef SFMLGAME_LEVELDATA_H
#define SFMLGAME_LEVELDATA_H

#include <SFML/Graphics.hpp>
#include "../tinyxml2/tinyxml2.h"
#include <map>
#include <vector>
#include "../GameObjects/GameObject.h"
#include "Tile.h"
#include "../GameObjects/Collectible.h"
#include "../GameObjects/Puzzle.h"
#include "../GameObjects/Door.h"
#include "../GameObjects/Switch.h"
#include "../GameObjects/Pressureplate.h"
#include "../GameObjects/PushableObject.h"

class GameData;

class LevelData
{
 public:
  LevelData(const char* file_path, sf::RenderWindow& game_window);
  ~LevelData() = default;

  bool loadLevel(const char* file_path);
  void updateLevel(float dt);

  bool loadPuzzles(const char* file_path);

  bool textureLevel();
  void render(GameData& game_data);
  void loadDoors();
  void loadSpawnPoints();

  void prepareLevel(GameData& game_data);

  std::vector<std::unique_ptr<Tile>>& getTiles() { return tile_layer; };

  std::vector<std::unique_ptr<Door>>& getDoors() { return doors; };

  std::unique_ptr<PushableObject>& getBox() { return level_box; }

  std::vector<std::unique_ptr<Collectible>>& getCoins() { return coins; }


  const std::unique_ptr<Puzzle>& getPuzzle() const;

 private:
  int width;
  int height;

  int tile_width;
  int tile_height;

  tinyxml2::XMLDocument file;

  std::vector<std::vector<int>> csv_layers;

  std::vector<std::unique_ptr<Tile>> tile_layer;

  std::vector<sf::Vector2f> coin_positions;
  std::vector<std::unique_ptr<Collectible>> coins;

  std::vector<std::pair <std::string, sf::Vector2f>> puzzlePositions;
  std::unique_ptr<Puzzle> puzzle;

  std::map<std::string, sf::Vector2f> spawn_points;

  sf::Texture layerTexture;
  sf::Texture door_texture;

  sf::RenderWindow &window;

  std::vector<std::unique_ptr<Door>> doors;

  std::string pressure_filename = "Data/Images/tiles_packed.png";

  std::unique_ptr<PushableObject> level_box;
  sf::Vector2f box_position;
};

#endif // SFMLGAME_LEVELDATA_H
