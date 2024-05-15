#ifndef PADDLE_H
#define PADDLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <math.h>

#include "audio.h"
#include "typedefs.h"
#include "constants.h"

    void update_paddle(Game* game);
    void paddle_collision(Game* game);

#ifdef __cplusplus
}
#endif

#endif /* PADDLE_H */

