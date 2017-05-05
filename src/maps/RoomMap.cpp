#include "RoomMap.hpp"

#include <iostream>

RoomMap::RoomMap(Ogre::SceneManager * sceneMgr) : _sceneMgr(sceneMgr) { }

RoomMap::~RoomMap() {}

void RoomMap::create()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(-1, -1, 0));

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("LightingNode");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Creating the scenario static geometry
  Ogre::StaticGeometry* stage = _sceneMgr->createStaticGeometry("Stage");
  Ogre::Entity* ent_stage = _sceneMgr->createEntity("Scenario.mesh");
  stage->addEntity( ent_stage, Ogre::Vector3(0, 0, 0) );
  stage->build();

}

void RoomMap::destroy()
{
  // TODO
  std::cout << "Destroying room map...\n";
}
