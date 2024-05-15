#include "brick.h"

void load_bricks_from_file(Game* game, int argc, char**argv) {
    char input[255];
    strcpy(input, INPUT);
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file")) {
            strcpy(input, argv[++i]);
        }
    }
    int len = strlen(input);
    if (len <= 3 || strcmp(input + len - 4, ".lvl")) {
        strcat(input, ".lvl");
    }

    FILE* f = fopen(input, "r");
    if (f == NULL) {
        printf("Couldn't load input file \"%s\"\n", input);
        return;
    }

    int x, y, hp;
    char c;
    game->bricks = malloc(sizeof (Brick));
    fscanf(f, "%d;", &hp);
    if (hp > 0 && hp <= 9)
        game->hp = hp;
    for (int i = 0; fscanf(f, "%d %d %d %c;", &x, &y, &hp, &c) == 4; i++) {
        if (x >= 0 && x < 18 && y >= 0 && y <= 10 && hp > 0 && hp < 1000 &&
                (c == 'r' || c == 'g' || c == 'b' || c == 'o' || c == 'w' || c == 'y')) {
            game->bricks = (Brick*) realloc(game->bricks, sizeof (Brick) * (i + 1));
            game->bricks[i].x = x;
            game->bricks[i].y = y;
            game->bricks[i].color = c;
            game->bricks[i].rect.x = B_WIDTH + game->bricks[i].x * B_WIDTH;
            game->bricks[i].rect.y = OFFSET_TOP + B_WIDTH + game->bricks[i].y * B_HEIGHT + B_HEIGHT * 4;
            game->bricks[i].rect.w = B_WIDTH;
            game->bricks[i].rect.h = B_HEIGHT;
            game->bricks[i].hp = hp;
            game->brick_count = i + 1;
        }
    }
    fclose(f);
}

void pop_brick(Game* game, int idx) { // Removes brick by index, reallocates memory
    for (int i = 0; i < game->brick_count; i++) {
        if (i == idx) {
            for (; i < game->brick_count - 1; i++) {
                game->bricks[i] = game->bricks[i + 1];
            }
            game->bricks = (Brick*) realloc(game->bricks, sizeof (Brick) * (--game->brick_count));
            break;
        }
    }
    if (game->brick_count < 1)
        game->game_over = 1;
}

bool brick_hit(Game* game, int idx) { // Decrement brick hp, if hp < 1, removes brick
    play_audio_by_color(game->bricks[idx].color);
    game->score++;
    if (--game->bricks[idx].hp <= 0) {
        pop_brick(game, idx);
        return true;
    }
    return false;
}

bool rect_collision(Ball* ball, Brick* brick) {
    return (ball->rect.x < brick->rect.x + brick->rect.w &&
            ball->rect.x + ball->rect.w > brick->rect.x &&
            ball->rect.y < brick->rect.y + brick->rect.h &&
            ball->rect.y + ball->rect.h > brick->rect.y);
}

void brick_collision(Game* game) {
    char dir = '0';
    int ball[6] = {// To make the code readable; R = right side, ...
        game->ball.x, // center x
        game->ball.y, // center y
        game->ball.rect.x + game->ball.rect.w, // 2 - R
        game->ball.rect.x, // 3 - L
        game->ball.rect.y, // 4 - U
        game->ball.rect.y + game->ball.rect.h // 5 - D
    };
    for (int i = 0; i < game->brick_count; i++) {
        if (rect_collision(&game->ball, &game->bricks[i])) {
            float dx = 1000, dy = 1000;
            int brick[6] = {// Static array to make the code readable
                game->bricks[i].rect.x + game->bricks[i].rect.w / 2, // center x
                game->bricks[i].rect.y + game->bricks[i].rect.h / 2, // center y
                game->bricks[i].rect.x + game->bricks[i].rect.w, // 2 - R
                game->bricks[i].rect.x, // 3 - L
                game->bricks[i].rect.y, // 4 - U
                game->bricks[i].rect.y + game->bricks[i].rect.h // 5 - D
            };
            dx = (game->ball.vec_x > 0) ? (ball[2] - brick[3]) : (ball[3] - brick[2]); // Calculates (x) length of overlapping ball - brick
            dy = (game->ball.vec_y < 0) ? (ball[4] - brick[5]) : (ball[5] - brick[4]); // Calculates (y) length of overlapping ball - brick


            if (dir == '0') {
                if (fabsf(dx) > fabsf(dy)) { // vertically
                    if (dy < 0) { // ball under brick
                        if (game->ball.vec_y < 0)
                            dir = 'd';
                        else {
                            if (game->ball.vec_x < 0)
                                dir = 'r';
                            else
                                dir = 'l';
                        }
                    } else { // ball above brick
                        if (game->ball.vec_y > 0)
                            dir = 'u';
                        else {
                            if (game->ball.vec_x > 0)
                                dir = 'l';
                            else
                                dir = 'r';
                        }
                    }
                } else { // horizontally
                    if (dx > 0) { // ball on left
                        if (game->ball.vec_x > 0)
                            dir = 'l';
                        else {
                            if (game->ball.vec_y < 0)
                                dir = 'd';
                            else
                                dir = 'u';
                        }
                    } else { // ball on right
                        if (game->ball.vec_x < 0)
                            dir = 'r';
                        else {
                            if (game->ball.vec_y < 0)
                                dir = 'd';
                            else
                                dir = 'u';
                        }
                    }
                }
            }

            if (brick_hit(game, i)) // Updates hp, if hp < 1, destroys brick. Returns true if brick destroyed
                i--;
        }
    }
    ball_bounce(game, dir);
}