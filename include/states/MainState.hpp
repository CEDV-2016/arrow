#pragma once

#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#include "GameState.hpp"

class MainState : public Ogre::Singleton<MainState>, public GameState {
public:
  MainState() {}

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);
  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent &e);
  bool frameEnded (const Ogre::FrameEvent &e);

  static MainState& getSingleton ();
  static MainState* getSingletonPtr ();

  void createScene();
  void createGUI();

  bool newGame(const CEGUI::EventArgs &e);
  bool navigateToCredits(const CEGUI::EventArgs &e);
  bool navigateToRanking(const CEGUI::EventArgs &e);
  bool quit(const CEGUI::EventArgs &e);

private:
  Ogre::Root* _root;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  Ogre::SceneManager* _sceneManager;
  Ogre::RaySceneQuery *_raySceneQuery;
  Ogre::SceneNode *_selectedNode;


  CEGUI::OgreRenderer* renderer;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  CEGUI::Window* _main;

  bool _exit;
};
