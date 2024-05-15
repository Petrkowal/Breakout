#ifndef GAME_H
#define GAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"

#include "ball.h"
#include "brick.h"
#include "paddle.h"

#include "typedefs.h"
#include "constants.h"

    void init_game(Game** g, int argc, char **argv);
    void reset_game(Game *g);
    void collisions(Game * game);
    void handle_events(Game* game, Graphics * g);
    void game_loop(Game * game);
    void loop(Game* game, Graphics* g, int argc, char** argv);
    void game_cleanup(Game* g);

#ifdef __cplusplus
}
#endif

#endif /* GAME_H */

