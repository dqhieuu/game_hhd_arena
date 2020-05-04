#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include "SoundEffect.h"
#include "ISoundEffectPlayer.h"
#include "SoundEffectPlayer.h"

SoundEffectPlayer::SoundEffectPlayer() {
    mChannelIndex = 0;
    mPlayerVolume = 100;
}

void SoundEffectPlayer::setVolume(int volume) {
    if(0 <= volume && volume <= 100)
        mPlayerVolume = volume;
}

void SoundEffectPlayer::loadSoundEffect(SoundEffect& effect) {
    Mix_Chunk* effectLoaded = Mix_LoadWAV(effect.path.c_str());
    if (effectLoaded != nullptr) {
        effectLoaded->volume = 128 * mPlayerVolume / 100; 
        int chunkId = getUniqueChannelId();
        storage[chunkId] = effectLoaded;
        effect.id = chunkId;
    } else
        std::cout << "Error: Loading sound effect " << effect.path << " failed, Mix_LoadWAV: " << Mix_GetError() << "\n";
}
void SoundEffectPlayer::play(int id, int channel, int loops, int time) {
    if (id != -1)
        Mix_PlayChannelTimed(channel, storage[id], loops, time);
}

int SoundEffectPlayer::getUniqueChannelId() {
    mChannelIndex++;
    return mChannelIndex;
}