#include "Timer.hpp"

Timer::Timer()
{
  _started_at = 0;
  _paused_at = 0;
  _started = false,
  _paused = false;
}

Timer::~Timer() {}

Ogre::String Timer::getGameplayTime()
{
  Ogre::String time = "";
  clock_t total_cycles = _started_at - clock();
  int total_seconds = ((float)total_cycles) / CLOCKS_PER_SEC;

  int seconds_remaining = -total_seconds;

  // Calculate minutes (no need to calculate hours) (I hope)
  int minutes = 0;
  while ( seconds_remaining >= 60 )
  {
    minutes++;
    seconds_remaining -= 60;
  }

  int seconds = seconds_remaining;

  time.append( Ogre::StringConverter::toString( minutes ) );
  time.append(".");
  if ( seconds < 10)
  {
    time.append( Ogre::StringConverter::toString( 0 ) );
    time.append( Ogre::StringConverter::toString( seconds ) );
  }
  else
  {
    time.append( Ogre::StringConverter::toString( seconds ) );
  }

  return time;
}

void Timer::start()
{
  _started = true;
  _paused = false;
  _started_at = clock();
}

void Timer::pause()
{
  if ( !_paused )
  {
    _paused = true;
    _paused_at = clock();
  }
}

void Timer::resume()
{
  if( _paused )
  {
    _paused = false;
    _started_at += clock() - _paused_at;
  }
}

void Timer::stop()
{
  _started = false;
}
