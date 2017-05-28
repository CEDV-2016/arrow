#include "Game.hpp"
#include "SoundFXManager.hpp"
#include <stdlib.h>     /* rand */

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
  SoundFXManager::getSingletonPtr()->load("arrow_yes.wav")->play();
  _dartboards_left--;
}

void Game::shootBall()
{
  std::stringstream sound_name;
  sound_name.str("");
  int random = rand()%2 + 1;
  sound_name << "arrow" << random << ".wav";

  SoundFXManager::getSingletonPtr()->load( sound_name.str() )->play();
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
  return _balls_left;
}

void Game::win()
{
  SoundFXManager::getSingletonPtr()->load("arrow_giggle.wav")->play();
}

void Game::lose()
{
  SoundFXManager::getSingletonPtr()->load("arrow_ouch.wav")->play();
}
