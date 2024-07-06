#include <SDL.h>
#include "ball.h"
#include "pong.h"
#include <iostream>
#include <algorithm>

const int FPS = 120;
const int FRAME_DELAY = 1000 / FPS;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    int paddleY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2; 
    int ballX = SCREEN_WIDTH / 2;
    int ballY = SCREEN_HEIGHT / 2;
    Uint32 lastTime = SDL_GetTicks();
    bool gameOver = false;

    while (!quit) {
        Uint32 frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION) {
                paddleY = e.motion.y - PADDLE_HEIGHT / 2;
                paddleY = std::clamp(paddleY, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float delta = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        if (!gameOver) {
            ballX += static_cast<int>(ballVelX * delta);
            ballY += static_cast<int>(ballVelY * delta);

            if (ballY + (BALL_SIZE / 2) < 0 || ballY + (BALL_SIZE / 2) > SCREEN_HEIGHT) {
                ballVelY *= -1;
            }
            if (ballX + (BALL_SIZE / 2) < 0 || (ballX + (BALL_SIZE / 2)) > SCREEN_WIDTH) {
                gameOver = true;
            }
            if (ballX + ((BALL_SIZE / 2)) == (paddleY + PADDLE_WIDTH / 2) && (ballY + BALL_SIZE > SCREEN_WIDTH) {
                gameOver = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        drawPaddle(renderer, 25, paddleY); 
        // drawPaddle(renderer, SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2, true); 
        drawBall(renderer, ballX, ballY); 

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}