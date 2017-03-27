#pragma once

#include "Map.hpp"

class DesertMap : public Map
{
public:
  DesertMap(Ogre::SceneManager * sceneMgr);
  ~DesertMap(); 

  void create();
  void destroy();

private:
  Ogre::SceneManager * _sceneMgr;
};
