#pragma once

#include <vector>

#include <Ogre.h>
#include <OgreSingleton.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Fader.hpp"
#include "Map.hpp"
#include "RoomMap.hpp"
#include "Enumerations.hpp"

class MapManager : public Ogre::Singleton<MapManager>
{
public:
  typedef std::shared_ptr<Map> MapPtr;

  MapManager( Ogre::SceneManager * sceneMgr );
  ~MapManager();

  void changeMap(enumerations::Maps id, bool fade);
  void loadMap();
  void fadeOut( std::function<void ()> callback = nullptr );
  void fadeIn ( std::function<void ()> callback = nullptr );
  void destroyAllMaps();
  void update( Ogre::Real deltaT );

  // Inherited from Ogre::Singleton.
  static MapManager& getSingleton ();
  static MapManager* getSingletonPtr ();

private:
  std::map<enumerations::Maps, MapPtr> _maps;

  enumerations::Maps _currentMap, _nextMap;
  Fader * _fader;
  Ogre::SceneManager * _sceneMgr;

  OgreBulletDynamics::DynamicsWorld * _world;
  OgreBulletCollisions::DebugDrawer * _debugDrawer;

  void initMaps();
};
