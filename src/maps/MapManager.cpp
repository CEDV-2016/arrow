#include "MapManager.hpp"

template<> MapManager* Ogre::Singleton<MapManager>::msSingleton = 0;

MapManager::MapManager(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _currentMap = MapsEnum::NONE;

  Ogre::AxisAlignedBox worldBounds = Ogre::AxisAlignedBox ( Ogre::Vector3 (-100, -100, -100), Ogre::Vector3 (100,  100,  100));
  Ogre::Vector3 gravity = Ogre::Vector3( 0, -9.8, 0 );
  _world = new OgreBulletDynamics::DynamicsWorld( _sceneMgr, worldBounds, gravity );

  _debugDrawer = new OgreBulletCollisions::DebugDrawer();
  _debugDrawer->setDrawWireframe( true );
  Ogre::SceneNode *node = _sceneMgr->getRootSceneNode()->createChildSceneNode("debugNode", Ogre::Vector3::ZERO);
  node->attachObject(static_cast <Ogre::SimpleRenderable *>( _debugDrawer ));

  _world->setDebugDrawer (_debugDrawer);
  _world->setShowDebugShapes (true); // to paint green wires around physic bodies

  initMaps();
}

MapManager::~MapManager()
{
  destroyAllMaps();
  delete _debugDrawer;
  delete _world;

  _sceneMgr = nullptr;
}

void MapManager::initMaps()
{
  _maps[ MapsEnum::ROOM ] = MapPtr( new RoomMap( _sceneMgr, _world ) );
  // Here will go the declaration of the rest of the maps the game is using
}

void MapManager::stepSimulation(Ogre::Real deltaT)
{
  _world->stepSimulation( deltaT );
}

// TODO implement a fade to black on changing map
void MapManager::changeMap(MapsEnum newMap)
{
  if ( _currentMap != MapsEnum::NONE ) _maps[ _currentMap ]->destroy();

  _maps[ newMap ]->create();

  _currentMap = newMap;
}

void MapManager::destroyAllMaps()
{
  MapsEnum key;

  for( auto it = _maps.begin(); it != _maps.end(); ++it )
  {
    key = it->first;
    _maps[ key ]->destroy();
  }
}
