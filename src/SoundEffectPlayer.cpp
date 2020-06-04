#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <unordered_map>


#include "SoundEffectPlayer.h"

SoundEffectPlayer::SoundEffectPlayer() {
    mChannelIndex = 0;
    mPlayerVolume = 100;
}

void SoundEffectPlayer::setVolume(int volume) {
    if(0 <= volume && volume <= 100)
        mPlayerVolume = volume;
}

void SoundEffectPlayer::loadSoundEffect(std::string name, std::string path) {
    if(!storage.count(name)) {
        Mix_Chunk* effectLoaded = Mix_LoadWAV(path.c_str());
        if (effectLoaded != nullptr) {
            Mix_VolumeChunk(effectLoaded, 128 * mPlayerVolume / 100); 
            int chunkId = getUniqueChannelId();
            storage.emplace(name, SoundEffect(effectLoaded, chunkId));
        } else
            std::cout << "Error: Loading sound effect " << path << " failed, Mix_LoadWAV: " << Mix_GetError() << "\n";
    }
}
void SoundEffectPlayer::play(std::string name, int loops, int time) {
    if (storage.count(name))
        if(Mix_PlayChannelTimed(storage[name].id, storage[name].chunk, loops, time)==-1) {
                printf("Error: Mix_PlayChannel: %s\n",Mix_GetError());
        }
}

void SoundEffectPlayer::free(std::string name) {
    if(storage.count(name)) {
        if(storage[name].chunk != nullptr)
            Mix_FreeChunk(storage[name].chunk);
        storage.erase(name);
    }
}

void SoundEffectPlayer::free() {
    for(auto& elem: storage) {
        Mix_FreeChunk(elem.second.chunk);
    }
    storage.clear();
}

void SoundEffectPlayer::stop(int id) {
    Mix_HaltChannel(id);
}

void SoundEffectPlayer::stop(std::string name) {
    Mix_HaltChannel(storage[name].id);
}

int SoundEffectPlayer::getUniqueChannelId() {
    mChannelIndex++;
    return mChannelIndex;
}