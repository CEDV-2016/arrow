#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>

class CameraManager : public Ogre::Singleton<CameraManager>
{
public:
  CameraManager( Ogre::SceneManager * sceneMgr );

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);

  void initCamera();
  void moveCamera();

  // Inherited from Ogre::Singleton.
  static CameraManager& getSingleton ();
  static CameraManager* getSingletonPtr ();

protected:
  Ogre::SceneManager* _sceneMgr;
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
};
