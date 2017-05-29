#include "IntroState.hpp"
#include "MainState.hpp"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

IntroState::IntroState():
  _physicsMgr(NULL),
  _mapMgr(NULL),
  _overlayMgr(NULL),
  _cameraMgr(NULL),
  _shootMgr(NULL),
  _collisionMgr(NULL),
  _characterMgr(NULL)
{}

void
IntroState::enter ()
{
  if (_root == NULL)
  {
    _root = Ogre::Root::getSingletonPtr();
  }
  if (_sceneMgr == NULL)
  {
    _sceneMgr = _root->getSceneManager("SceneManager");
  }
  if (_camera == NULL)
  {
    _camera = _sceneMgr->createCamera("MainCamera");
  }

  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.3, 0.8, 0.8));

  // Creating and placing camera
  _camera->setPosition( Ogre::Vector3(0, 0, 10) );
  _camera->lookAt( Ogre::Vector3(0, 0, 8) );
  _camera->setNearClipDistance(0.001);
  _camera->setFarClipDistance(1000);
  _camera->setFOVy(Ogre::Degree(38));
  double width = _viewport->getActualWidth();
  double height = _viewport->getActualHeight();
  _camera->setAspectRatio(width / height);

  _sceneMgr->setAmbientLight( Ogre::ColourValue(1, 1, 1) );
  _sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  _sceneMgr->setShadowTextureCount(30);
  _sceneMgr->setShadowTextureSize(512);

  initializeManagers();
  createGUI();
  loadBackgroundImage();

  _exitGame = false;
}

void IntroState::initializeManagers()
{
  if (_physicsMgr == NULL)
  {
    _physicsMgr = new MyPhysicsManager( _sceneMgr );
  }
  if (_mapMgr == NULL)
  {
    _mapMgr = new MapManager( _sceneMgr, MyPhysicsManager::getSingletonPtr()->getPhysicWorld() );
  }
  if (_overlayMgr == NULL)
  {
    _overlayMgr = new MyOverlayManager();
  }
  if (_cameraMgr == NULL)
  {
    _cameraMgr = new CameraManager( _sceneMgr );
  }
  if (_shootMgr == NULL)
  {
    _shootMgr = new ShootManager( _sceneMgr );
  }
  if (_collisionMgr == NULL)
  {
    _collisionMgr = new MyCollisionManager( _sceneMgr );
  }
  if (_characterMgr == NULL)
  {
    _characterMgr = new CharacterManager( _sceneMgr );
  }
}

void
IntroState::exit()
{
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause ()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("SplashOverlay")->hide();
  _intro->hide();
}

void
IntroState::resume ()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("SplashOverlay")->show();
  _intro->show();
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt)
{
  MapManager::getSingletonPtr()->update( evt.timeSinceLastFrame );

  return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE)
  {
    _exitGame = true;
  }
  else if (e.key == OIS::KC_SPACE)
  {
    pushState(MainState::getSingletonPtr());
  }
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

IntroState*
IntroState::getSingletonPtr ()
{
  return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}


void IntroState::createGUI()
{
  if(_intro == NULL)
  {
    _intro = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("splash.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_intro);
  }
  else
  {
    _intro->show();
  }
  Ogre::OverlayManager::getSingletonPtr()->getByName("SplashOverlay")->show();
}

void IntroState::loadBackgroundImage()
{
  // Randmonly select background
  std::string _all_backgrounds[3] {"oil.jpg", "cubism.jpg", "glass.jpg"};
  unsigned seed = std::time(0);
  std::srand(seed);
  std::random_shuffle(&_all_backgrounds[0], &_all_backgrounds[sizeof(_all_backgrounds)/sizeof(*_all_backgrounds)]);

  Ogre::TexturePtr m_backgroundTexture = Ogre::TextureManager::getSingleton().createManual("BackgroundTexture",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,640, 480, 0, Ogre::PF_BYTE_BGR,Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
  Ogre::Image m_backgroundImage;
  m_backgroundImage.load(_all_backgrounds[0], Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  m_backgroundTexture->loadImage(m_backgroundImage);
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("BackgroundMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  material->getTechnique(0)->getPass(0)->createTextureUnitState("BackgroundTexture");
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
  _rect = new Ogre::Rectangle2D(true);
  _rect->setCorners(-1.0, 1.0, 1.0, -1.0);
  _rect->setMaterial("BackgroundMaterial");
  _rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
  _rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));
  _backgroundNode = _sceneMgr->getRootSceneNode()->createChildSceneNode("BackgroundMenu");
  _backgroundNode->attachObject(_rect);

  MapManager::getSingletonPtr()->fadeIn();
}
