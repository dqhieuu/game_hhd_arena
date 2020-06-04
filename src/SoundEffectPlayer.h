#ifndef SOUND_EFFECT_PLAYER_H
#define SOUND_EFFECT_PLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include "ISoundEffectPlayer.h"
#include "SoundEffect.h"
#include "string"

class SoundEffectPlayer : public ISoundEffectPlayer {
   public:
    SoundEffectPlayer();
    virtual void setVolume(int volume);
    virtual void loadSoundEffect(std::string name, std::string path);
    virtual void play(std::string name, int loops = 0, int time = -1);
    virtual void stop(int channel = -1);
    virtual void stop(std::string name);
    virtual void free(std::string name);
    virtual void free();
   private:
    int getUniqueChannelId();
    int mPlayerVolume;
    int mChannelIndex;
    std::unordered_map<std::string, SoundEffect> storage;
};

#endif