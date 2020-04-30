#ifndef LOCATOR_H
#define LOCATOR_H

#include "IMusicPlayer.h"
#include "IRenderer.h"
#include "ISoundEffectPlayer.h"
#include "MusicPlayer.h"
#include "Renderer.h"
#include "SoundEffectPlayer.h"

class Locator {
   public:
    static IMusicPlayer* getMusicPlayer();
    static ISoundEffectPlayer* getSoundEffectPlayer();
    static IRenderer* getRenderer();
    static void provide(IMusicPlayer* service);
    static void provide(ISoundEffectPlayer* service);
    static void provide(IRenderer* service);

   private:
    static IMusicPlayer* mMusicPlayer;
    static ISoundEffectPlayer* mSoundEffectPlayer;
    static IRenderer* mRenderer;
};

#endif