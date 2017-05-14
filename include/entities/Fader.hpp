#pragma once

#include "OgreMaterialManager.h"
#include "OgreOverlayManager.h"
#include "OgreTechnique.h"
#include "OgreBlendMode.h"
#include <string>

#include "Enumerations.hpp"

class Fader
{
public:
     static constexpr float FADE_DURATION = 0.5f;

     Fader( std::function<void ()> callback = nullptr );
     ~Fader(void);

     void startFadeIn( double duration = FADE_DURATION );
     void startFadeOut( double duration = FADE_DURATION );
     void fade( double timeSinceLastFrame );
     void setNextMap( enumerations::Maps newMap );

protected:

     const std::string& _overlay_name  = "Overlays/Fader";
     const std::string& _material_name = "Materials/OverlayMaterial";

     double _alpha;
     double _current_dur;
     double _total_dur;
     Ogre::TextureUnitState *_tex_unit;
     Ogre::Overlay *_overlay;

     enumerations::Maps _newMap;
     std::function<void ()> _callback;

     enum _fadeop
     {
          FADE_NONE,
          FADE_IN,
          FADE_OUT,
     } _fadeop;
};
