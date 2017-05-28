#include "CharacterManager.hpp"

template<> CharacterManager* Ogre::Singleton<CharacterManager>::msSingleton = 0;

CharacterManager::CharacterManager( Ogre::SceneManager * sceneMgr )
{
  _sceneMgr = sceneMgr;
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::loadCharacter()
{
  _character_entity = _sceneMgr->createEntity( "Arrow", "Arrow.mesh" );
  _character_node = _sceneMgr->createSceneNode( "Arrow" );
  _character_node->setScale( 3.5, 3.5, 3.5 );
  _sceneMgr->getRootSceneNode()->addChild( _character_node );

  _idle_state = _character_entity->getAnimationState("Idle");
  _shoot_state = _character_entity->getAnimationState("Shoot");
  _walk_state = _character_entity->getAnimationState("Walk");

  _idle_state->setEnabled(false);
  _shoot_state->setEnabled(false);
  _walk_state->setEnabled(false);

  idle();
}

Ogre::SceneNode * CharacterManager::getSceneNode()
{
  return _character_node;
}

Ogre::Entity * CharacterManager::getEntity()
{
  return _character_entity;
}

void CharacterManager::walk()
{
  _shoot_state->setLoop(false);
  _idle_state->setLoop(false);

  _walk_state->setTimePosition(0.0);
  _walk_state->setEnabled(true);
  _walk_state->setLoop(true);
}

void CharacterManager::shoot()
{
  _walk_state->setLoop(false);

  _shoot_state->setTimePosition(0.0);
  _shoot_state->setEnabled(true);
  _shoot_state->setLoop(false);
}

void CharacterManager::idle()
{
  _walk_state->setLoop(false);

  _idle_state->setTimePosition(0.0);
  _idle_state->setEnabled(true);
  _idle_state->setLoop(true);
}

void CharacterManager::update(Ogre::Real deltaT)
{
    if (_walk_state->getEnabled() && ! _walk_state->hasEnded())
    {
      _walk_state->addTime( deltaT * 2.5f );
    }

    if (_shoot_state->getEnabled() && ! _shoot_state->hasEnded())
    {
      _shoot_state->addTime( deltaT );
    }

    if (_idle_state->getEnabled() && ! _idle_state->hasEnded())
    {
      _idle_state->addTime( deltaT );
    }
}

CharacterManager& CharacterManager::getSingleton()
{
  assert(msSingleton);
  return (*msSingleton);
}

CharacterManager* CharacterManager::getSingletonPtr()
{
  assert(msSingleton);
  return msSingleton;
}
