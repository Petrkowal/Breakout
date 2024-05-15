#include "game.h"

void init_game(Game** game, int argc, char **argv) {
    (*game) = malloc(sizeof(Game));
    (*game)->brick_count = 0;
    (*game)->paddle.time = 0;
    (*game)->paddle.x = WIN_WIDTH / 2;
    (*game)->paddle.rect.x = (*game)->paddle.x - B_WIDTH;
    (*game)->paddle.rect.y = WIN_HEIGHT - B_HEIGHT;
    (*game)->paddle.rect.w = 2 * B_WIDTH;
    (*game)->paddle.rect.h = 0.75 * B_HEIGHT;
    (*game)->ball.x = (*game)->paddle.x;
    (*game)->ball.y = (*game)->paddle.rect.y - BALL_R / 2;
    (*game)->ball.velocity = BALL_START_V;
    (*game)->ball.vec_x = 1;
    (*game)->ball.vec_y = 1;
    (*game)->ball.launched = false;
    (*game)->ball.rect.x = (*game)->ball.x - BALL_R / 2;
    (*game)->ball.rect.y = (*game)->ball.y - BALL_R / 2;
    (*game)->ball.rect.w = BALL_R;
    (*game)->ball.rect.h = BALL_R;
    (*game)->hp = 5;
    (*game)->score = 0;
    (*game)->game_over = 0;
    (*game)->restart = false;
    (*game)->borders = (SDL_Rect*) malloc(sizeof (SDL_Rect) * 3);


    SDL_Rect r;
    r.x = 0;
    r.y = OFFSET_TOP;
    r.w = B_WIDTH;
    r.h = WIN_HEIGHT - OFFSET_TOP - B_HEIGHT / 2;
    (*game)->borders[0] = r;
    r.x = B_WIDTH;
    r.y = OFFSET_TOP;
    r.w = WIN_WIDTH - 2 * B_WIDTH;
    r.h = B_WIDTH;
    (*game)->borders[1] = r;
    r.x = WIN_WIDTH - B_WIDTH;
    r.y = OFFSET_TOP;
    r.w = B_WIDTH;
    r.h = WIN_HEIGHT - OFFSET_TOP - B_HEIGHT / 2;
    (*game)->borders[2] = r;
        
    load_bricks_from_file(*game, argc, argv);
}

void collisions(Game * game) { // Collisions check
    border_collision(game);
    brick_collision(game);
    paddle_collision(game);
    bottom_collision(game); // If the ball is dropped
}

void handle_events(Game* game, Graphics * g) { // Event handler
    while (SDL_PollEvent(&g->e))
        switch (g->e.type) {
            case SDL_QUIT: g->quit = SDL_TRUE; // Quit
                break;
            case SDL_MOUSEBUTTONDOWN: // Mouse click
                if (game->game_over == 0) {
                    ball_launch(game);
                } else {
                    game->restart = true;
                }
                break;
            default: break;
        }
}

void game_loop(Game * game) { // Main loop

    float vel_rem = 0;
    vel_rem = game->ball.velocity;
    for (int i = 0; i < (int) game->ball.velocity; i++) {
        update_ball(game, 0);
        vel_rem-=1;
    }
    update_ball(game, vel_rem);

    update_paddle(game);
}

void loop(Game* game, Graphics* g, int argc, char** argv) {
    while (!g->quit) {
        if (!game->restart) {

            if (game->game_over == 1) {
                draw_game_over(g, true);
                handle_events(game, g);
            } else if (game->game_over == -1) {
                draw_game_over(g, false);
                handle_events(game, g);
            } else {

                g->start = SDL_GetTicks();

                handle_events(game, g);
                game_loop(game);
                draw(game, g);


                g->end = SDL_GetTicks();

                int wait_for = 1000 / FPS - (g->end - g->start);
                if (wait_for > 0) {
                    SDL_Delay(wait_for);
                }
            }
        } else {

            game_cleanup(game);
            init_game(&game, argc, argv);
            game->restart = false;
        }
    }
}

void game_cleanup(Game* game) {
    free(game->bricks);
    game->bricks = NULL;
    free(game->borders);
    game->borders = NULL;
    free(game);
    game = NULL;
}