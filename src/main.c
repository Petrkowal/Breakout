#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "constants.h"
#include "game.h"



int main(int argc, char** argv)  {
    Game *game;
    init_game(&game, argc, argv);
    Graphics *g;
    init_sdl(&g);
    init_audio();

    loop(game, g, argc, argv);
    game_cleanup(game);
    clean_audio();
    graphics_cleanup(g);
    return (EXIT_SUCCESS);
}

