#pragma once

#include <Ogre.h>
#include <vector>

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

  // Inherited from Ogre::Singleton.
  static MapManager& getSingleton ();
  static MapManager* getSingletonPtr ();

private:
  std::map<MapsEnum, MapPtr> _maps;

  MapsEnum _currentMap;

  Ogre::SceneManager * _sceneMgr;

  void initMaps();
};
