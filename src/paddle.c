#include "paddle.h"

void update_paddle(Game* game) { // Moves paddle
    SDL_GetMouseState(&game->paddle.x, NULL); // Directly puts mouse x pos to paddle x
    if (game->paddle.x - B_WIDTH < B_WIDTH) // Doesn't allow paddle to go through left border
        game->paddle.x = 2 * B_WIDTH;
    if (game->paddle.x + B_WIDTH > WIN_WIDTH - B_WIDTH) // Same, right border
        game->paddle.x = WIN_WIDTH - (2 * B_WIDTH);
    game->paddle.rect.x = game->paddle.x - game->paddle.rect.w / 2; }

void paddle_collision(Game* game) {
    // ball - paddle collision check
    if (SDL_GetTicks() > game->paddle.time + 500) {
        if (game->ball.rect.x < game->paddle.rect.x + game->paddle.rect.w &&
                game->ball.rect.x + game->ball.rect.w > game->paddle.rect.x &&
                game->ball.rect.y < game->paddle.rect.y + game->paddle.rect.h &&
                game->ball.rect.y + game->ball.rect.h > game->paddle.rect.y) {
            game->paddle.time = SDL_GetTicks();
            // ball touches paddle - calculate new vector
            game->ball.vec_y = -fabsf(game->ball.vec_y);
            if (game->ball.velocity > BALL_MAX_V)
                game->ball.velocity = BALL_MAX_V;
            else
                game->ball.velocity *= 1.05;
            float div = game->ball.x - game->paddle.x;
            div /= game->paddle.rect.w / 2;
            float angle = ((60 * div) + 90) * M_PI / 180;
            game->ball.vec_x = -cosf(angle);
            game->ball.vec_y = -sinf(angle);
            play_audio(A_PADDLE);
        }
    }
    }