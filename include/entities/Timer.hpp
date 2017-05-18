#pragma once

#include <ctime>
#include <Ogre.h>

class Timer
{
public:
  Timer();
  ~Timer();

  void start();
  void pause();
  void resume();
  void stop();

  Ogre::String getGameplayTime();

private:

  clock_t _startedAt;
  clock_t _pausedAt;

  bool _started;
  bool _paused;
};
