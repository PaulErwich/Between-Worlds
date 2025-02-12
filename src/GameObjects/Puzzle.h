//
// Created by perwi on 31/03/2023.
//

#ifndef SFMLGAME_PUZZLE_H
#define SFMLGAME_PUZZLE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "PuzzlePiece.h"

#include "../Networking/CustomPacket.h"

class Puzzle
{
 public:
  Puzzle();
  ~Puzzle();
  bool init();
  void update(float dt);
  void render(sf::RenderWindow& window);

  void addPiece(PuzzlePiece* game_object);

  void setCompleted(bool _complete);
  bool getCompleted() const;

  std::vector<PuzzlePiece*>& getPuzzlePieces() { return puzzle_pieces; }

  void updatePuzzle(Puzzle* puzzle);

 private:
  // Need to create a map of for puzzle_test pieces / components
  // Then change packet, so it takes the state change and a component number
  // Write out what i need / want to happen then progress with plan
  std::vector<PuzzlePiece*> puzzle_pieces;

  bool completed;
};

#endif // SFMLGAME_PUZZLE_H
