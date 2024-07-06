#include "ball.h"

int ballVelX = 400;  
int ballVelY = 400;  

void drawPaddle(SDL_Renderer* renderer, int x, int y, bool bot) {
    SDL_Rect paddle = {x, y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, bot ? 255 : 0, 0, bot ? 0 : 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
}

void drawBall(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawFilledCircle(renderer, x, y, BALL_SIZE);
}