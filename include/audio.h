#ifndef AUDIO_H
#define AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL_mixer.h>
#include "constants.h"

    void init_audio();
    void play_audio(int sound);
    void play_audio_by_color(char color);
    void clean_audio();

#ifdef __cplusplus
}
#endif

#endif /* AUDIO_H */

