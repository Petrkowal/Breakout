#ifndef BRICK_H
#define BRICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ball.h"
#include "audio.h"
#include "typedefs.h"
#include "constants.h"

    void pop_brick(Game* game, int idx);
    bool brick_hit(Game* game, int idx);
    bool rect_collision(Ball* ball, Brick* brick);
    void brick_collision(Game* game);
    void load_bricks_from_file(Game* game, int argc, char**argv);

#ifdef __cplusplus
}
#endif

#endif /* BRICK_H */

