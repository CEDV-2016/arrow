#pragma once

#include <Ogre.h>

class CharacterManager : public Ogre::Singleton<CharacterManager>
{
public:
  CharacterManager( Ogre::SceneManager * sceneMgr );
  ~CharacterManager();

  void loadCharacter();

  Ogre::SceneNode * getSceneNode();
  Ogre::Entity * getEntity();

  void update(Ogre::Real deltaT);

  void walk();
  void shoot();
  void idle();

  // Inherited from Ogre::Singleton.
  static CharacterManager& getSingleton ();
  static CharacterManager* getSingletonPtr ();

private:
  Ogre::SceneManager * _sceneMgr;
  Ogre::SceneNode * _character_node;
  Ogre::Entity * _character_entity;

  Ogre::AnimationState *_idle_state, *_shoot_state, *_walk_state;

};
