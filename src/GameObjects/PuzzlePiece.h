//
// Created by MLG Erwich on 23/04/2023.
//

#ifndef SFMLGAME_PUZZLEPIECE_H
#define SFMLGAME_PUZZLEPIECE_H

#include "GameObject.h"
#include "Door.h"

class PuzzlePiece : public GameObject
{
 public:
  PuzzlePiece(const std::string& filename, sf::Vector2f pos);

  void setActive(bool _active) { active = _active; }
  bool getActive() const { return active; }

  virtual void activate() { active = true; }
  virtual void deactivate() { active = false; }

  void setDoor(Door* _linked_door) { linked_door = _linked_door; }

 protected:
  bool active;

  Door* linked_door = nullptr;
};

#endif // SFMLGAME_PUZZLEPIECE_H
