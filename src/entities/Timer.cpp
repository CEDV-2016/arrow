#include "Timer.hpp"

Timer::Timer()
{
  _startedAt = 0;
  _pausedAt = 0;
  _started = false,
  _paused = false;
}

Timer::~Timer() {}

Ogre::String Timer::getGameplayTime()
{
  Ogre::String time = "";
  clock_t total_time = _startedAt - clock();

  return time;
}

void Timer::start()
{
  _started = true;
  _paused = false;
  _startedAt = clock();
}

void Timer::pause()
{
  if ( !_paused )
  {
    _paused = true;
    _pausedAt = clock();
  }
}

void Timer::resume()
{
  if( _paused )
  {
    _paused = false;
    _startedAt += clock() - _pausedAt;
  }
}

void Timer::stop()
{
  _started = false;
}
