#pragma once

#include <ctime>
#include <time.h>  /* CLOCKS_PER_SEC */
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

  clock_t _started_at;
  clock_t _paused_at;

  bool _started;
  bool _paused;
};
