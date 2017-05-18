#include "MyOverlayManager.hpp"

template<> MyOverlayManager* Ogre::Singleton<MyOverlayManager>::msSingleton = 0;

MyOverlayManager::MyOverlayManager()
{
  _ogreOverlayMgr = Ogre::OverlayManager::getSingletonPtr();
  _overlay = _ogreOverlayMgr->getByName("HUD");
  _overlay->hide();
}

MyOverlayManager::~MyOverlayManager() {}

void MyOverlayManager::createHUD()
{
  _overlayElement = _ogreOverlayMgr->getOverlayElement("nameTextArea");
  _overlayElement->setCaption("");

  _overlayElement = _ogreOverlayMgr->getOverlayElement("dianaTextArea");
  _overlayElement->setCaption("");

  _overlayElement = _ogreOverlayMgr->getOverlayElement("arrowTextArea");
  _overlayElement->setCaption("");

  _overlayElement = _ogreOverlayMgr->getOverlayElement("timerTextArea");
  _overlayElement->setCaption("");

  _overlay->show();
}


void MyOverlayManager::setPlayerName(std::string name)
{
  _overlayElement = _ogreOverlayMgr->getOverlayElement("nameTextArea");
  _overlayElement->setCaption( Ogre::String( name ) );
}

void MyOverlayManager::setTime(Ogre::String time)
{
  _overlayElement = _ogreOverlayMgr->getOverlayElement("timerTextArea");
  _overlayElement->setCaption( time );
}
void MyOverlayManager::setArrowsLeft(std::string arrows_left)
{
  _overlayElement = _ogreOverlayMgr->getOverlayElement("arrowTextArea");
  _overlayElement->setCaption( Ogre::String( arrows_left ) );
}

void MyOverlayManager::setDianasLeft(std::string dianas_left)
{
  _overlayElement = _ogreOverlayMgr->getOverlayElement("dianaTextArea");
  _overlayElement->setCaption( Ogre::String( dianas_left ) );
}

MyOverlayManager*
MyOverlayManager::getSingletonPtr ()
{
  return msSingleton;
}

MyOverlayManager&
MyOverlayManager::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}
