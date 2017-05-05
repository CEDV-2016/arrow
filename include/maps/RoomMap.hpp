#pragma once

#include "Map.hpp"

class RoomMap : public Map
{
public:
  RoomMap(Ogre::SceneManager * sceneMgr);
  ~RoomMap();

  void create();
  void destroy();

private:
  Ogre::SceneManager * _sceneMgr;
};
