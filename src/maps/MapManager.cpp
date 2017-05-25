#include "MapManager.hpp"

template<> MapManager* Ogre::Singleton<MapManager>::msSingleton = 0;

MapManager::MapManager( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * pyhsicWorld )
{
  _sceneMgr = sceneMgr;
  _pyhsicWorld = pyhsicWorld;
  _currentMap = enumerations::Maps::NONE;
  _fader = new Fader();

  initMaps();
}

MapManager::~MapManager()
{
  _currentMap = enumerations::Maps::NONE;
  destroyAllMaps();

  _sceneMgr = nullptr;
  _pyhsicWorld = nullptr;
  _fader = nullptr;
}

void MapManager::initMaps()
{
  _maps[ enumerations::Maps::ROOM ] = MapPtr( new RoomMap( _sceneMgr, _pyhsicWorld ) );
  // Here will go the declaration of the rest of the maps the game is using
}

void MapManager::update( Ogre::Real deltaT )
{
  _fader->update( deltaT );
}

/*
* This function is called from outside and starts the fade to black.
* Once the fade is completed, it will automatically callback the load
* of the new map and then fade in again.
*/
void MapManager::changeMap(enumerations::Maps newMap, bool fade)
{
  _nextMap = newMap;
  _fader->setNextMap(newMap);

  if ( fade )
  {
    _fader->startFadeOut( std::bind(&MapManager::loadMap, this) );
  }
  else
  {
    loadMap();
  }
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

void MapManager::fadeOut( std::function<void ()> callback )
{
  _fader->startFadeOut( callback );
}

void MapManager::fadeIn( std::function<void ()> callback )
{
  _fader->startFadeIn( callback );
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

MapManager& MapManager::getSingleton()
{
  assert(msSingleton);
  return (*msSingleton);
}

MapManager* MapManager::getSingletonPtr()
{
  assert(msSingleton);
  return msSingleton;
}
