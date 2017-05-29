#pragma once

#include <string>

class Game
{
public:

  Game();
  ~Game ();

  void hitDartboard();
  void shootBall();
  void setPlayerName(std::string name);

  int getDartboartdsLeft();
  int getBallsLeft();
  std::string getPlayerName();

  void win();
  void lose();

private:

  static const int NUM_DARTBOARDS = 5;
  static const int NUM_BALLS = 8;

  int _dartboards_left;
  int _balls_left;
  std::string _player_name;
};
