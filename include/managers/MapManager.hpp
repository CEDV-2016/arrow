#pragma once

#include <vector>

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Map.hpp"
#include "RoomMap.hpp"

enum MapsEnum
{
  NONE = -1,
  ROOM,
};

class MapManager : public Ogre::Singleton<MapManager>
{
public:
  typedef std::shared_ptr<Map> MapPtr;

  MapManager(Ogre::SceneManager * sceneMgr);
  ~MapManager();

  void changeMap(MapsEnum id);
  void destroyAllMaps();
  void stepSimulation(Ogre::Real deltaT);

  // Inherited from Ogre::Singleton.
  static MapManager& getSingleton ();
  static MapManager* getSingletonPtr ();

private:
  std::map<MapsEnum, MapPtr> _maps;

  MapsEnum _currentMap;

  Ogre::SceneManager * _sceneMgr;

  OgreBulletDynamics::DynamicsWorld * _world;
  OgreBulletCollisions::DebugDrawer * _debugDrawer;

  void initMaps();
};
