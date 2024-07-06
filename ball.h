#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "circle.h"

const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int PADDLE_SPEED = 5;
extern int ballVelX;
extern int ballVelY;
const int BALL_SIZE = 15;

void drawPaddle(SDL_Renderer* renderer, int x, int y, bool bot = false);
void drawBall(SDL_Renderer* renderer, int x, int y);

#endif