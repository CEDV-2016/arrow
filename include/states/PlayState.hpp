#pragma once

#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <string>
#include <vector>

#include "MyTimer.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "MapManager.hpp"
#include "CameraManager.hpp"
#include "ShootManager.hpp"
#include "MyPhysicsManager.hpp"
#include "MyOverlayManager.hpp"
#include "MyCollisionManager.hpp"

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
  PlayState ();

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Inherited from Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

  void createScene();
  void createHUD();

  void moveCamera();

  void setPlayerName(std::string name);

  void endGame(bool win);

protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  Ogre::RaySceneQuery *_raySceneQuery;
  Ogre::SceneNode *_selectedNode;
  CEGUI::OgreRenderer* renderer;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  CEGUI::Window* _playGUI, *_nameView, *_scoreView, *_life1View, *_life2View, *_life3View;
  Game *_game;
  MapManager * _mapManager;
  MyPhysicsManager * _physicsManager;
  MyOverlayManager * _overlayManager;
  MyCollisionManager * _collisionManager;

  std::string _name;
  MyTimer * _timer;
  CameraManager * _camManager;
  ShootManager * _shootManager;

  bool _exitGame;
  bool _evenFrame;

  //Camera movement
  Ogre::AnimationState *_animState;
  Ogre::SceneNode *cameraNode;
  Ogre::SceneNode *cameraYawNode;
  Ogre::SceneNode *cameraPitchNode;
  Ogre::SceneNode *cameraRollNode;
  Ogre::Vector3 translateVector;
  Ogre::Radian rotateScale;
  float moveScale;
  Ogre::Radian rotX;
  Ogre::Radian rotY;
  bool _moveRight, _moveLeft, _moveUp, _moveDown;
};
