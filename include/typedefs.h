#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        float x;
        float y;
        float vec_x;
        float vec_y;
        float velocity;
        bool launched;
        SDL_Rect rect;
    } Ball;

    typedef struct {
        int x;
        Uint32 time;
        SDL_Rect rect;
    } Paddle;

    typedef struct {
        int x;
        int y;
        int hp;
        char color;
        SDL_Rect rect;
    } Brick;

    typedef struct {
        int score;
        int hp;
        int brick_count;
        int game_over;
        bool restart;
        SDL_Rect* borders;
        Ball ball;
        Paddle paddle;
        Brick* bricks;
    } Game;

    typedef struct {
        int r;
        int g;
        int b;
    } Color;

    typedef struct {
        SDL_Window* window;
        SDL_Renderer* renderer;
        Uint32 start;
        Uint32 end;
        SDL_Event e;
        SDL_bool quit;
        Color color;
        SDL_Surface* surfaces;
        SDL_Texture* textures;
        TTF_Font*font;
    } Graphics;





#ifdef __cplusplus
}
#endif

#endif /* TYPEDEFS_H */

