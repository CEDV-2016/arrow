#include "RoomMap.hpp"

#include <iostream>

RoomMap::RoomMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
  _sceneMgr( sceneMgr ),
  _world( world )
  {}

RoomMap::~RoomMap() {}

void RoomMap::create()
{
  std::string map_file = "Scenario.mesh";

  // Creating light
  Ogre::Light *light = _sceneMgr->createLight("MainLight");
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3(-1, -1, 0) );

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("LightNode");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Creating the scenario
  // Ogre::StaticGeometry* stage = _sceneMgr->createStaticGeometry("Stage");
  // Ogre::Entity* ent_stage = _sceneMgr->createEntity( map_file );
  // stage->addEntity( ent_stage, Ogre::Vector3(0, 0, 0) );
  // stage->build();

  Ogre::Entity * room_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * room_node = _sceneMgr->createSceneNode( "Room" );
  room_node->attachObject( room_entity );
  _sceneMgr->getRootSceneNode()->addChild( room_node );

  // Creating the physic world
  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter( room_entity );

  OgreBulletCollisions::TriangleMeshCollisionShape *trackTrimesh = trimeshConverter->createTrimesh();

  OgreBulletDynamics::RigidBody *rigidTrack = new OgreBulletDynamics::RigidBody( "Room", _world );
                                    // Restitucion, friccion y masa
  rigidTrack->setShape( room_node, trackTrimesh, 0.8, 0.95, 0, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);

  // delete trimeshConverter;

}

void RoomMap::destroy()
{
  // TODO
  std::cout << "Destroying room map...\n";
}
