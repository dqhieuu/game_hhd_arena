#include "Locator.h"

IMusicPlayer* Locator::mMusicPlayer = new MusicPlayer();
ISoundEffectPlayer* Locator::mSoundEffectPlayer = new SoundEffectPlayer();
IRenderer* Locator::mRenderer = new Renderer();

IMusicPlayer* Locator::getMusicPlayer() { return mMusicPlayer; }
ISoundEffectPlayer* Locator::getSoundEffectPlayer() { return mSoundEffectPlayer; }
IRenderer* Locator::getRenderer() { return mRenderer; }
void Locator::provide(IMusicPlayer* service) { mMusicPlayer = service; }
void Locator::provide(ISoundEffectPlayer* service) { mSoundEffectPlayer = service; }
void Locator::provide(IRenderer* service) { mRenderer = service; }