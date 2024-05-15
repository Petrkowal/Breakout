#ifndef BALL_H
#define BALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "audio.h"
#include "game.h"
#include "typedefs.h"
#include "constants.h"

    void ball_reset(Game* game);
    void set_draw_coords(Game* game);
    void ball_launch(Game* game);
    void move_ball(Game* game, float vel_rem);
    void ball_bounce(Game* game, char dir);
    void border_collision(Game* game);
    void ball_dropped(Game* game);
    void bottom_collision(Game* game);
    void update_ball(Game * game, float vel_rem);

#ifdef __cplusplus
}
#endif

#endif /* BALL_H */

