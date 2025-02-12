//
// Created by perwi on 31/03/2023.
//

#include "Puzzle.h"

Puzzle::Puzzle() : completed(false)
{
  puzzle_pieces.reserve(10);
}

Puzzle::~Puzzle()
{
  for (auto& game_object : puzzle_pieces)
  {
    delete game_object;
    game_object = nullptr;
  }
}

bool Puzzle::init()
{
  return true;
}

void Puzzle::update(float dt)
{
  for (auto& game_object : puzzle_pieces)
  {
    game_object->update(dt);
  }
}

void Puzzle::render(sf::RenderWindow& window)
{
  for (auto& game_object : puzzle_pieces)
  {
    game_object->render(window);
  }
}

void Puzzle::addPiece(PuzzlePiece* game_object)
{
  game_object->init();
  puzzle_pieces.push_back(game_object);
}

void Puzzle::setCompleted(bool _complete)
{ completed = _complete; }

bool Puzzle::getCompleted() const
{ return completed; }

void Puzzle::updatePuzzle(Puzzle* puzzle)
{

}