#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL.h>
#include <string>
#include <cereal/archives/json.hpp>
#include <fstream>

enum Degree {
        LOW, MEDIUM, HIGH
};

struct Settings {
    SDL_Scancode buttonUp = SDL_SCANCODE_W;
    SDL_Scancode buttonDown = SDL_SCANCODE_S;
    SDL_Scancode buttonLeft = SDL_SCANCODE_A;
    SDL_Scancode buttonRight = SDL_SCANCODE_D;
    SDL_Scancode buttonJump = SDL_SCANCODE_J;
    SDL_Scancode buttonAttack = SDL_SCANCODE_K;
    SDL_Scancode buttonShoot = SDL_SCANCODE_L;
    SDL_Scancode buttonSpecialMove = SDL_SCANCODE_U;
    int musicVolume = 60;
    int effectsVolume = 40;
    Degree gameQuality = HIGH;
    bool isFullScreen = false;
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( CEREAL_NVP(buttonUp), CEREAL_NVP(buttonDown), CEREAL_NVP(buttonLeft), CEREAL_NVP(buttonRight), CEREAL_NVP(buttonJump), CEREAL_NVP(buttonAttack), CEREAL_NVP(buttonShoot), CEREAL_NVP(buttonSpecialMove), CEREAL_NVP(musicVolume), CEREAL_NVP(effectsVolume), CEREAL_NVP(gameQuality), CEREAL_NVP(isFullScreen));
    }
};



#endif