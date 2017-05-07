#pragma once

#include "Map.hpp"

class RoomMap : public Map
{
public:
  RoomMap( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world );
  ~RoomMap();

  void create();
  void destroy();

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
