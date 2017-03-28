#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameStatesManager.hpp"
#include "InputManager.hpp"

// Clase abstracta de estado básico.
// Definición base sobre la que extender
// los estados del juego.
class GameState {

 public:
  GameState() {}

  // Gestión básica del estado.
  virtual void enter () = 0;
  virtual void exit () = 0;
  virtual void pause () = 0;
  virtual void resume () = 0;

  // Gestión básica para el tratamiento
  // de eventos de teclado y ratón.
  virtual void keyPressed (const OIS::KeyEvent &e) = 0;
  virtual void keyReleased (const OIS::KeyEvent &e) = 0;

  virtual void mouseMoved (const OIS::MouseEvent &e) = 0;
  virtual void mousePressed (const OIS::MouseEvent &e,
			     OIS::MouseButtonID id) = 0;
  virtual void mouseReleased (const OIS::MouseEvent &e,
			      OIS::MouseButtonID id) = 0;

  // Gestión básica para la gestión
  // de eventos antes y después de renderizar un frame.
  virtual bool frameStarted (const Ogre::FrameEvent& evt) = 0;
  virtual bool frameEnded (const Ogre::FrameEvent& evt) = 0;

  // Gestión básica de transiciones.
  void changeState (GameState* state) {
    GameStatesManager::getSingletonPtr()->changeState(state);
  }
  void pushState (GameState* state) {
    GameStatesManager::getSingletonPtr()->pushState(state);
  }
  void popState () {
    GameStatesManager::getSingletonPtr()->popState();
  }

  void restartState (GameState* state) {
    GameStatesManager::getSingletonPtr()->restartState(state);
  }
};
