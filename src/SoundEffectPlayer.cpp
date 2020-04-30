#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>

#include "SoundEffect.h"
#include "ISoundEffectPlayer.h"
#include "SoundEffectPlayer.h"

SoundEffectPlayer::SoundEffectPlayer() {
    mChannelIndex = 0;
}

SoundEffectPlayer::~SoundEffectPlayer() {
    Mix_AllocateChannels(0);
}
void SoundEffectPlayer::loadSoundEffect(SoundEffect& effect) {
    Mix_Chunk* effectLoaded = Mix_LoadWAV(effect.path.c_str());
    if (effectLoaded != nullptr) {
        int chunkId = getUniqueChannelId();
        storage[chunkId] = effectLoaded;
        effect.id = chunkId;
    } else
        std::cout << "Error: Sound effect not found, Mix_LoadWAV: " << Mix_GetError() << "\n";
}
void SoundEffectPlayer::play(int id, int channel, int loops, int time) {
    if (id != -1)
        Mix_PlayChannelTimed(channel, storage[id], loops, time);
}

int SoundEffectPlayer::getUniqueChannelId() {
    mChannelIndex++;
    return mChannelIndex;
}