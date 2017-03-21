#include "PlayState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"
#include "SoundFXManager.hpp"
#include "DesertMap.hpp"
template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState()
{
  _game = new Game();
  _playGUI = NULL;
}

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createScene();
  // createGUI();

  _exitGame = false;
}

void
PlayState::exit ()
{
  _playGUI->hide();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
}

void
PlayState::resume()
{
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;

  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) pushState(PauseState::getSingletonPtr());
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
  return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PlayState::createScene()
{
  // TODO Migrate the creation of the maps to a MapManager (and make it fade to black)
  // TODO Delegate all the gameplay's logic to a GameManager (rename GameManager to GameStateManager?)

  std::shared_ptr<Map> main_map;
  main_map = std::shared_ptr<Map>( new DesertMap(_sceneMgr) );
  main_map->create();

  //Creating the player
  Ogre::Entity * entity = _sceneMgr->createEntity("Player.mesh");
  entity->setCastShadows(true);
  Ogre::SceneNode * node = _sceneMgr->createSceneNode("Player");
  node->attachObject(entity);
  node->setPosition( Ogre::Vector3::ZERO );
  _sceneMgr->getRootSceneNode()->addChild(node);
}

void PlayState::createGUI()
{
  if(_playGUI == NULL){
    //Config Window
    _playGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("play.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_playGUI);

    //Config Buttons
    CEGUI::Window* _layout = _playGUI->getChild("FrameWindow");
    _nameView = _layout->getChild("NameLabel");
  }
  else
  {
    _playGUI->show();
  }
}

void PlayState::setPlayerName(std::string name)
{

}
