#include "Game.hpp"

Game::Game()
{
  _dartboards_left = NUM_DARTBOARDS;
  _balls_left = NUM_BALLS;
}

Game::~Game() {}

void Game::setPlayerName(std::string name)
{
  _player_name = (name == "") ? "Arrow" : name;
}

void Game::hitDartboard()
{
  _dartboards_left--;
}

void Game::shootBall()
{
  _balls_left--;
}

std::string Game::getPlayerName()
{
  return _player_name;
}

int Game::getDartboartdsLeft()
{
  return _dartboards_left;
}

int Game::getBallsLeft()
{
  return _dartboards_left;
}
