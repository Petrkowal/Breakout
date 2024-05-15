#include "ball.h"

void ball_reset(Game* game) { // Resets ball
    game->ball.launched = false;
    game->ball.velocity = BALL_START_V;
    game->ball.vec_x = 1;
    game->ball.vec_y = 1;
    game->ball.x = game->paddle.x;
    game->ball.y = game->paddle.rect.y - BALL_R / 2;
    game->ball.rect.x = game->ball.x - BALL_R / 2;
    game->ball.rect.y = game->ball.y - BALL_R / 2;
}

void set_draw_coords(Game* game) { // Sets ball draw coords from ball center
    game->ball.rect.x = game->ball.x - game->ball.rect.w / 2;
    game->ball.rect.y = game->ball.y - game->ball.rect.h / 2;
}

void ball_launch(Game* game) { // Launches the ball, randomizes vector
    if (game->ball.launched == false) {

        game->ball.launched = true;

        srand(time(NULL));
        float angle = rand() % 60 - 30;
        angle = (angle + 90) * M_PI / 180;
        game->ball.vec_x = -cosf(angle);
        game->ball.vec_y = -sinf(angle);
    }
}

void move_ball(Game* game, float vel_rem) { // Moves ball
    //        game->ball.x += game->ball.vec_x * game->ball.velocity;
    //        game->ball.y += game->ball.vec_y * game->ball.velocity;
    if (vel_rem == 0) {
        game->ball.x += game->ball.vec_x;
        game->ball.y += game->ball.vec_y;
    } else {
        game->ball.x += game->ball.vec_x * vel_rem;
        game->ball.y += game->ball.vec_y * vel_rem;
    }
    set_draw_coords(game);
}

void ball_bounce(Game* game, char dir) {
    switch (dir) {
        case 'l': // bounce left -> makes x vector negative
            game->ball.vec_x = -(fabsf(game->ball.vec_x)); // fabsf = float abs (float)
            break;
        case 'r': // right -> x positive
            game->ball.vec_x = fabsf(game->ball.vec_x);
            break;
        case 'd': // down -> y pos
            game->ball.vec_y = fabsf(game->ball.vec_y);
            break;
        case 'u': // up -> y neg
            game->ball.vec_y = -(fabsf(game->ball.vec_y));
            break;
        default: break;
    }
}

void border_collision(Game* game) { // Detects border collisions, bounces the ball
    if (game->ball.x + game->ball.rect.w / 2 > WIN_WIDTH - B_WIDTH) { // Left border
        ball_bounce(game, 'l');
        play_audio(A_RIGHT);
    }
    if (game->ball.x - game->ball.rect.w / 2 < B_WIDTH) { // Top
        ball_bounce(game, 'r');
        play_audio(A_LEFT);
    }
    if (game->ball.y - game->ball.rect.h / 2 < OFFSET_TOP + B_WIDTH) { // Right
        ball_bounce(game, 'd');
        play_audio(A_TOP);
    }
}

void ball_dropped(Game* game) {
    if (--game->hp <= 0)
        game->game_over = -1;
    ball_reset(game);
}

void bottom_collision(Game* game) {
    if (game->ball.y > game->paddle.rect.y + game->paddle.rect.h * 2)
        ball_dropped(game);
}

void update_ball(Game * game, float vel_rem) {
    if (game->ball.launched == true) {

        move_ball(game, vel_rem);
        collisions(game);
    } else {
        game->ball.x = game->paddle.x;
        set_draw_coords(game);
    }
}