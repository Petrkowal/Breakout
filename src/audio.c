#include "audio.h"

Mix_Chunk *waves[10];

void init_audio() {
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(10);
    waves[0] = Mix_LoadWAV(PATH_LEFT);
    waves[1] = Mix_LoadWAV(PATH_RIGHT);
    waves[2] = Mix_LoadWAV(PATH_TOP);
    waves[3] = Mix_LoadWAV(PATH_PADDLE);
    waves[4] = Mix_LoadWAV(PATH_RED);
    waves[5] = Mix_LoadWAV(PATH_ORANGE);
    waves[6] = Mix_LoadWAV(PATH_BROWN);
    waves[7] = Mix_LoadWAV(PATH_YELLOW);
    waves[8] = Mix_LoadWAV(PATH_GREEN);
    waves[9] = Mix_LoadWAV(PATH_BLUE);
}

void play_audio(int sound) {
    Mix_PlayChannel(-1, waves[sound], 0);
}

void play_audio_by_color(char color) {
    switch (color) {

        case 'r':
            play_audio(A_RED);
            break;
        case 'o':
            play_audio(A_ORANGE);
            break;
        case 'w':
            play_audio(A_BROWN);
            break;
        case 'y':
            play_audio(A_YELLOW);
            break;
        case 'g':
            play_audio(A_GREEN);
            break;
        case 'b':
            play_audio(A_BLUE);
            break;
        default:
            play_audio(A_RED);
            break;
    }
}

void clean_audio() {
    for (int i = 0; i < 10; i++) {
        Mix_FreeChunk(waves[i]);
    }
    Mix_CloseAudio();
}