#include "graphics.h"

void init_sdl(Graphics** g) {
    (*g) = malloc(sizeof(Graphics));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    TTF_Init();

    (*g)->font = TTF_OpenFont(FONT, 72);
    //        TTF_SetFontKerning(g->font, 0);
    (*g)->window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    (*g)->renderer = SDL_CreateRenderer((*g)->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    (*g)->quit = SDL_FALSE;
}

void color_from_str(SDL_Color* col, char color) {
    SDL_Color c;
    switch (color) {

        case 'r': // Red

            c.r = 210;
            c.g = 85;
            c.b = 75;
            c.a = 255;
            break;
        case 'o': // Orange

            c.r = 205;
            c.g = 110;
            c.b = 60;
            c.a = 255;
            break;
        case 'w': // broWn

            c.r = 190;
            c.g = 125;
            c.b = 50;
            c.a = 255;
            break;
        case 'y': // Yellow

            c.r = 160;
            c.g = 155;
            c.b = 40;
            c.a = 255;
            break;
        case 'g': // Green

            c.r = 70;
            c.g = 145;
            c.b = 70;
            c.a = 255;
            break;
        case 'b': // Blue

            c.r = 60;
            c.g = 80;
            c.b = 205;
            c.a = 255;
            break;
        default:
            c.r = 0;
            c.g = 0;
            c.b = 0;
            c.a = 255;
    }
    *col = c;
}

void draw_game_over(Graphics* g, bool win) {
    SDL_Rect r;
    r.x = B_WIDTH;
    r.y = OFFSET_TOP + B_WIDTH;
    r.w = WIN_WIDTH - 2 * B_WIDTH;
    r.h = WIN_HEIGHT - OFFSET_TOP - 2 * B_WIDTH;

    SDL_Color c;
    SDL_Surface *surface_score = NULL;
    if (win) {
        c.r = 0;
        c.g = 255;
        c.b = 0;

        surface_score = TTF_RenderText_Solid(g->font, "CONGRATULATIONS", c);
    } else {
        c.r = 255;
        c.g = 0;
        c.b = 0;

        surface_score = TTF_RenderText_Solid(g->font, "TRY AGAIN", c);
    }

    SDL_Texture * Score = SDL_CreateTextureFromSurface(g->renderer, surface_score);

    SDL_RenderCopy(g->renderer, Score, NULL, &r);

    SDL_RenderPresent(g->renderer); // Draw on screen

    SDL_FreeSurface(surface_score);
    SDL_DestroyTexture(Score);
}

void draw(Game* game, Graphics* g) {
    // BACKGROUND
    SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    SDL_RenderClear(g->renderer);

    // PADDLE
    SDL_SetRenderDrawColor(g->renderer, 210, 85, 75, 255);
    SDL_RenderFillRect(g->renderer, &game->paddle.rect);

    // BALL
    SDL_SetRenderDrawColor(g->renderer, 210, 85, 75, 255);
    SDL_RenderFillRect(g->renderer, &game->ball.rect);

    // BORDER
    SDL_SetRenderDrawColor(g->renderer, 142, 142, 142, 255); // Color
    for (int i = 0; i < 3; i++) {
        SDL_RenderFillRect(g->renderer, &game->borders[i]);
    }

    SDL_Rect r;
    r.h = B_HEIGHT;
    r.w = B_WIDTH;
    r.x = 0;
    r.y = game->paddle.rect.y;

    SDL_SetRenderDrawColor(g->renderer, 60, 150, 130, 255);
    SDL_RenderFillRect(g->renderer, &r);
    SDL_SetRenderDrawColor(g->renderer, 210, 85, 75, 255);
    r.x = WIN_WIDTH - r.w;
    SDL_RenderFillRect(g->renderer, &r);

    // SCORE
    char score_str[4], tmp[40];
    sprintf(tmp, "%03d", game->score);
    strncpy(score_str, tmp, 3);
    score_str[3] = '\0';

    SDL_Color c = {142, 142, 142};
    r.x = 3 * B_WIDTH;
    r.y = 0 - (OFFSET_TOP * 0.4);
    r.w = B_WIDTH * 3.5;
    r.h = OFFSET_TOP * 1.5;

    SDL_Surface * surface_score = TTF_RenderText_Solid(g->font, score_str, c);
    SDL_Texture * Score = SDL_CreateTextureFromSurface(g->renderer, surface_score);

    SDL_RenderCopy(g->renderer, Score, NULL, &r);

    SDL_FreeSurface(surface_score);
    SDL_DestroyTexture(Score);
    // --- / SCORE ---

    // HP
    char hp[2];
    sprintf(tmp, "%d", game->hp);
    hp[0] = tmp[0];
    hp[1] = '\0';

    SDL_Surface * sur_hp = TTF_RenderText_Solid(g->font, hp, c);
    SDL_Texture * Hp = SDL_CreateTextureFromSurface(g->renderer, sur_hp);

    r.x += 2 * r.w;
    r.w /= 3;
    SDL_RenderCopy(g->renderer, Hp, NULL, &r);

    SDL_FreeSurface(sur_hp);
    SDL_DestroyTexture(Hp);
    // --- / HP ---

    // BRICKS
    SDL_Color brick_c;
    for (int i = 0; i < game->brick_count; i++) {
        color_from_str(&brick_c, game->bricks[i].color);
        SDL_SetRenderDrawColor(g->renderer, brick_c.r, brick_c.g, brick_c.b, brick_c.a);
        SDL_RenderFillRect(g->renderer, &game->bricks[i].rect);
    }

    SDL_RenderPresent(g->renderer); // Render
}

void graphics_cleanup(Graphics* g) {
    SDL_DestroyRenderer(g->renderer);
    SDL_DestroyWindow(g->window);
    TTF_CloseFont(g->font);
    TTF_Quit();
    SDL_Quit();
    free(g);
    g = NULL;
}