//
// Created by perwi on 19/04/2023.
//

#ifndef SFMLGAME_DOOR_H
#define SFMLGAME_DOOR_H

#include "GameObject.h"
#include "../LevelLoading/Tile.h"

class Door
{
 public:
  Door(sf::Texture& texture, int x, int y, int height);

  void enableDoor();
  void disableDoor();

  bool getEnabled() { return enabled; }

  GameObject& getCollisionBox();

  void update(float dt);
  void render(sf::RenderWindow& window);

 private:
  std::vector<std::unique_ptr<Tile>> door_tiles;

  std::unique_ptr<GameObject> collision_box;

  bool enabled;
};

#endif // SFMLGAME_DOOR_H
