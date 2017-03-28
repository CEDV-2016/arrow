#include "MapManager.hpp"

template<> MapManager* Ogre::Singleton<MapManager>::msSingleton = 0;

MapManager::MapManager(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _currentMap = MapsEnum::NONE;

  initMaps();
}

void MapManager::initMaps()
{
  _maps[MapsEnum::DESERT] = MapPtr( new DesertMap( _sceneMgr ) );
  // Here will go the rest of the maps the game is using
}

// TODO implement a fade to black on changing map
void MapManager::changeMap(MapsEnum newMap)
{
  if (_currentMap != MapsEnum::NONE) _maps[_currentMap]->destroy();

  _maps[newMap]->create();

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
  _sceneMgr = nullptr;
}
