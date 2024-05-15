#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "typedefs.h"
#include "constants.h"

    void init_sdl(Graphics** g);
    void color_from_str(SDL_Color* col, char color);
    void draw_game_over(Graphics* g, bool win);
    void draw(Game* game, Graphics* g);
    void graphics_cleanup(Graphics* g);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHICS_H */

