#pragma once

#include <Ogre.h>

class Map
{
public:
  virtual void create() = 0;
  virtual void destroy() = 0;
};
