//
// Created by perwi on 07/03/2023.
//

#include "LevelData.h"
#include "../Other/GameData.h"

#include <iostream>

LevelData::LevelData(const char* file_path, sf::RenderWindow& game_window) :
width(0), height(0), tile_width(0), tile_height(0), window(game_window)
{
  coin_positions.reserve(20);
  coins.reserve(20);

  loadLevel(file_path);
  textureLevel();
  loadDoors();

  puzzle = std::make_unique<Puzzle>();

  loadPuzzles(file_path);

  loadSpawnPoints();
}

bool LevelData::loadLevel(const char* file_path)
{
  if (file.LoadFile(file_path) != tinyxml2::XML_SUCCESS)
  {
    std::cout << "File didn't load\n";
    return false;
  }

  tinyxml2::XMLNode* root = file.RootElement();
  tinyxml2::XMLElement* element;

  element = file.FirstChildElement("map");

  width = element->IntAttribute("width");
  height = element->IntAttribute("height");

  tile_width = element->IntAttribute("tilewidth");
  tile_height = element->IntAttribute("tileheight");

  const char* csv;
  std::string temp;

  bool children = true;
  int i = 0;

  while(children)
  {
    csv_layers.emplace_back();

    element = root->FirstChildElement("layer");

    for (int k = 0; k < i; k++)
    {
      element = element->NextSiblingElement("layer");
    }

    csv = element->FirstChildElement("data")->GetText();
    temp = csv;
    int l = 1;

    for (int j = 0; j < width * height; j++)
    {

      if (temp[l] == '\n')
      {
        l++;
      }

      if (temp[l + 1] != '\n' && temp[l + 1] != ',' && temp[l + 2] != '\n' && temp[l + 2] != ',')
      {
        // the -48 is for Ascii conversion
        csv_layers[i].push_back(((int(temp[l]) - 48) * 100) + (int(temp[l + 1]) - 48) * 10 + (int(temp[l + 2]) - 48));
        l += 4;
      }
      else if (temp[l + 1] != '\n' && temp[l + 1] != ',')
      {
        // the -48 is for Ascii conversion
        csv_layers[i].push_back(((int(temp[l]) - 48) * 10) + (int(temp[l + 1]) - 48));
        l += 3;
      }
      else
      {
        csv_layers[i].push_back(int(temp[l]) - 48);
        l += 2;
      }
    }

    if (element->NextSiblingElement("layer") == nullptr)
    {
      children = false;
      break;
    }

    i++;
  }

  /// Coin Objects
  element = file.RootElement()->FirstChildElement("objectgroup");
  element = element->NextSiblingElement("objectgroup");
  tinyxml2::XMLElement* current = element->FirstChildElement("object");

  children = true;
  i = 0;
  while(children)
  {
    coin_positions.emplace(coin_positions.end(), sf::Vector2f(current->FloatAttribute("x") * 1.25, current->FloatAttribute("y") * 1.25));

    coins.emplace(coins.end(), std::make_unique<Collectible>("Data/Images/platformer items - free assets/animated_items.png", coin_positions.back()));

    // if no more coin objects loaded.
    if (current->NextSiblingElement("object") == nullptr)
    {
      children = false;
      break;
    }

    current = current->NextSiblingElement("object");
    i++;

  }
  return true;
}

bool LevelData::textureLevel()
{
  int texture_number = 0;

  if (!layerTexture.loadFromFile("Data/Images/TempSpriteSheet.png"))
  //if (!layerTexture.loadFromFile("Data/Images/PlatformerTileset1.png"))
  {
    std::cout << "rip\n";
    return false;
  }

  //std::pair<int, std::vector<int>> single_csv;
  std::vector<std::pair<int, int>> single_csv;
  single_csv.reserve(width * height);

  for (int i = 0; i < width * height; i++)
  {
    single_csv.push_back(std::make_pair<int, int>(0, -1));
  }

  for (int k = 0; k < 4; k++)
  {
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        texture_number = csv_layers[k][i * width + j] - 1;
        if (texture_number != -1 && single_csv[i * width + j].second == -1)
        {
          single_csv[i * width + j].second = texture_number;
          single_csv[i * width + j].first = k;
        }

      }
    }
  }

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      tile_layer.emplace_back(std::make_unique<Tile>(layerTexture, j, i, single_csv[i * width + j].second, single_csv[i * width + j].first));
    }
  }

  return true;
}

void LevelData::updateLevel(float dt)
{
  for (auto& coin : coins)
  {
    coin->update(dt);
  }

  level_box->update(dt);

  puzzle->update(dt);
}

bool LevelData::loadPuzzles(const char* file_path)
{
  if (file.LoadFile(file_path) != tinyxml2::XML_SUCCESS)
  {
    std::cout << "File didn't load\n";
    return false;
  }

  //tinyxml2::XMLNode* root = file.RootElement();
  tinyxml2::XMLElement* element;

  element = file.RootElement()->FirstChildElement("objectgroup");
  //element = root->FirstChildElement("objectgroup");
  tinyxml2::XMLElement* current = element->FirstChildElement("object");
  // current = current->NextSiblingElement("object");

  //element->FirstChildElement("objectgroup");
  //std::cout << element << std::endl;

  bool children = true;
  int i = 0;

  while(children)
  {
    puzzlePositions.emplace(puzzlePositions.end(),std::make_pair<std::string, sf::Vector2f>(current->Attribute("name"), sf::Vector2f(current->FloatAttribute("x") * 1.25f, current->FloatAttribute("y") * 1.25f)));
    //puzzles.emplace(puzzles.end(), std::make_unique<Puzzle>(), puzzlePositions.back());
    if (current->NextSiblingElement("object") == nullptr)
    {
      children = false;
      break;
    }

    current = current->NextSiblingElement("object");
    i++;
    std::cout << puzzlePositions.back().first << " " << puzzlePositions.back().second.x / 5 * 4 / 32 << " " << puzzlePositions.back().second.y / 5 * 4 / 32 << std::endl;
  }

  int j = 0;
  for (auto& puzzle_position : puzzlePositions)
  {
    if (puzzle_position.first == "PressurePlate")
    {
      puzzle->addPiece(new Pressureplate(pressure_filename, puzzle_position.second, true));
      puzzle->getPuzzlePieces().back()->setDoor(&*doors.at(j));
      j++;
    }
    else if (puzzle_position.first == "Box")
    {
      level_box = std::make_unique<PushableObject>("Data/Images/PlatformerTileset2.png", puzzle_position.second);
      box_position = puzzle_position.second;
    }
  }

  return true;
}

void LevelData::render(GameData& game_data)
{

  for (auto& tile : tile_layer)
  {
    if (game_data.controlled_player == ControlledPlayer::PLAYER_ONE && tile->getLayerNumber() == 1)
    {
      continue;
    }
    else if (game_data.controlled_player == ControlledPlayer::PLAYER_TWO && tile->getLayerNumber() == 3)
    {
      continue;
    }

    tile->render(window);
  }

  for (auto& coin : coins)
  {
    coin->render(window);
  }

  for (auto& door : doors)
  {
    door->render(window);
  }

  level_box->render(window);

  puzzle->render(window);
}

void LevelData::loadDoors()
{
  if (!door_texture.loadFromFile("Data/Images/PlatformerTileset1.png"))
  {
    std::cout << "door texture\n";
    return;
  }

  tinyxml2::XMLElement* element = file.RootElement()->FirstChildElement("objectgroup");

  element = element->NextSiblingElement("objectgroup");
  element = element->NextSiblingElement("objectgroup");
  tinyxml2::XMLElement* current = element->FirstChildElement("object");

  doors.reserve(10);

  bool children = true;
  int i = 0;

  while (children)
  {
    doors.emplace(doors.end(), std::make_unique<Door>(door_texture, current->FloatAttribute("x") / 32,
                                                      current->FloatAttribute("y") / 32, current->FloatAttribute("height") / 32));

    std::cout << current->FloatAttribute("x") / 32 << " " <<
      current->FloatAttribute("y") / 32 << " " << current->FloatAttribute("height") / 32 << "\n";

    if (current->NextSiblingElement("object") == nullptr)
    {
      children = false;
      break;
    }

    current = current->NextSiblingElement("object");
    i++;
  }
}

void LevelData::loadSpawnPoints()
{
  tinyxml2::XMLElement* element = file.RootElement()->FirstChildElement("objectgroup");

  bool next_group = true;

  while (next_group)
  {
    std::string layer_name = element->Attribute("name");
    if (layer_name == "SpawnPoints")
    {
      next_group = false;
    }
    else
    {
      element = element->NextSiblingElement("objectgroup");
    }
  }

  tinyxml2::XMLElement* current = element->FirstChildElement("object");

  bool children = true;

  while (children)
  {
    spawn_points[current->Attribute("name")] = sf::Vector2f(current->FloatAttribute("x"),
                                                            current->FloatAttribute("y"));

    std::cout << "Spawn points: " << current->FloatAttribute("x") << " " << current->FloatAttribute("y") << "\n";

    if (current->NextSiblingElement("object") == nullptr)
    {
      children = false;
    }

    current = current->NextSiblingElement("object");
  }
}

void LevelData::prepareLevel(GameData& game_data)
{
  game_data.players[ControlledPlayer::PLAYER_ONE]->setPosition(spawn_points["Blue"]);
  game_data.players[ControlledPlayer::PLAYER_TWO]->setPosition(spawn_points["Red"]);

  for (auto& piece : puzzle->getPuzzlePieces())
  {
    piece->deactivate();
  }

  level_box->setPosition(box_position);

  for (auto& coin : coins)
  {
    coin->setVisible(true);
  }
}
const std::unique_ptr<Puzzle>& LevelData::getPuzzle() const
{
  return puzzle;
}
