#include "PlayState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"
#include "SoundFXManager.hpp"

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
  // TODO Migrate the creation of the scene to a MapManager

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
