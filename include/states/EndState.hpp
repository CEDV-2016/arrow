#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>

#include "GameState.hpp"
#include "RankingManager.hpp"

class EndState : public Ogre::Singleton<EndState>, public GameState
{
public:
  EndState();

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

  // Heredados de Ogre::Singleton.
  static EndState& getSingleton ();
  static EndState* getSingletonPtr ();

  void createGUI();

  bool finish(const CEGUI::EventArgs &e);

  void setData(bool win, std::string name, int points);

protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  CEGUI::Window* _endGUI, *_titleView, *_nameView, *_pointsView;
  std::string _name;
  int _points;
  bool _win;
  RankingManager* _rankingManager;

  bool _exitGame;
};
