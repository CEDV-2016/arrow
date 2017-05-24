#pragma once

#include "Map.hpp"

class RoomMap : public Map
{
public:
  RoomMap( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world );
  ~RoomMap();

  void create();
  void destroy();

  void loadDartboards();
  Ogre::SceneNode * loadSingleDartboard( std::string dartboard_file );

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;

  int _dartboard_counter = 0;
};
