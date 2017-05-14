#include "MapManager.hpp"

template<> MapManager* Ogre::Singleton<MapManager>::msSingleton = 0;

MapManager::MapManager(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _currentMap = enumerations::Maps::NONE;
  _fader = new Fader( std::bind(&MapManager::loadMap, this) );

  Ogre::AxisAlignedBox worldBounds = Ogre::AxisAlignedBox( Ogre::Vector3 (-100, -100, -100), Ogre::Vector3 (100,  100,  100) );
  Ogre::Vector3 gravity = Ogre::Vector3( 0, -9.8, 0 );
  _world = new OgreBulletDynamics::DynamicsWorld( _sceneMgr, worldBounds, gravity );

  _debugDrawer = new OgreBulletCollisions::DebugDrawer();
  _debugDrawer->setDrawWireframe( true );
  Ogre::SceneNode *node = _sceneMgr->getRootSceneNode()->createChildSceneNode("debugNode", Ogre::Vector3::ZERO);
  node->attachObject(static_cast <Ogre::SimpleRenderable *>( _debugDrawer ));

  _world->setDebugDrawer(_debugDrawer);
  _world->setShowDebugShapes(true); // to paint green wires around physic bodies

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
  _maps[ enumerations::Maps::ROOM ] = MapPtr( new RoomMap( _sceneMgr, _world ) );
  // Here will go the declaration of the rest of the maps the game is using
}

void MapManager::stepSimulation(Ogre::Real deltaT)
{
  _fader->fade( deltaT );
  _world->stepSimulation( deltaT );
}

/*
* This function is called from outside and starts the fade to black.
* Once the fade is completed, it will automatically callback the load
* of the new map and then fade in again.
*/
void MapManager::changeMap(enumerations::Maps newMap)
{
  _nextMap = newMap;
  _fader->setNextMap(newMap);
  _fader->startFadeOut();
}


void MapManager::loadMap()
{
  if ( _currentMap != enumerations::Maps::NONE )
  {
    _maps[ _currentMap ]->destroy();
  }
  
  _maps[ _nextMap ]->create();

  _currentMap = _nextMap;

  _fader->startFadeIn();
}


void MapManager::destroyAllMaps()
{
  enumerations::Maps key;

  for( auto it = _maps.begin(); it != _maps.end(); ++it )
  {
    key = it->first;
    _maps[ key ]->destroy();
  }
}
