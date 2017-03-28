#include "DesertMap.hpp"

#include <iostream>

DesertMap::DesertMap(Ogre::SceneManager * sceneMgr) : _sceneMgr(sceneMgr) { }

DesertMap::~DesertMap() {}

void DesertMap::create()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(1, -1, 0));

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("LightingNode");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Creating the ground
  Ogre::Plane plane1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("ground_mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane1, 200, 200, 1, 1, true, 1, 20, 20, Ogre::Vector3::UNIT_Z);
  Ogre::Entity* ground_ent = _sceneMgr->createEntity("ground_ent", "ground_mesh");
  ground_ent->setMaterialName("Ground");
  Ogre::SceneNode* node_ground = _sceneMgr->createSceneNode("ground_node");
  node_ground->attachObject(ground_ent);
  _sceneMgr->getRootSceneNode()->addChild(node_ground);
}

void DesertMap::destroy()
{
  // TODO
  std::cout << "Destroying desert map...\n";
}
