#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

struct SoundEffect {
    SoundEffect(std::string path_);
    std::string path;
    int id;
};

#endif