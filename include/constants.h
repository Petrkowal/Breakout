#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT "data/lvl/breakout.lvl"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 960

#define B_WIDTH WIN_WIDTH / 20
#define B_HEIGHT WIN_HEIGHT / 30
#define OFFSET_TOP B_WIDTH
#define B_OFFSET_TOP B_HEIGHT * 4 + B_WIDTH * 2
#define BALL_R WIN_WIDTH / 100
#define BALL_START_V 10
#define BALL_MAX_V 30

#define FPS 60
#define FONT "data/font/acknowledge-tt-brk.ttf"

#define PATH_LEFT "data/audio/left.wav"
#define PATH_RIGHT "data/audio/right.wav"
#define PATH_TOP "data/audio/top.wav"
#define PATH_PADDLE "data/audio/paddle.wav"
#define PATH_RED "data/audio/red.wav"
#define PATH_ORANGE "data/audio/orange.wav"
#define PATH_BROWN "data/audio/brown.wav"
#define PATH_YELLOW "data/audio/yellow.wav"
#define PATH_GREEN "data/audio/green.wav"
#define PATH_BLUE "data/audio/blue.wav"

#define A_LEFT 0
#define A_RIGHT 1
#define A_TOP 2
#define A_PADDLE 3
#define A_RED 4
#define A_ORANGE 5
#define A_BROWN 6
#define A_YELLOW 7
#define A_GREEN 8
#define A_BLUE 9


#ifdef __cplusplus
}
#endif

#endif /* CONSTANTS_H */

