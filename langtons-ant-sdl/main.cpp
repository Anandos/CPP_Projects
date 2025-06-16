//'langtons-sdl' created on 16/06/2025 by Anand Damodaran
#include <iostream>
#include <random>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "class.h"
#include <thread>
#include <chrono>

using std::cout;using std::cin;using std::endl;

int main() {
    const int win_width = 3840 / 2.3;
    const int win_height = 2160 / 2.3;

    // Window
    SDL_Window *window = SDL_CreateWindow(
        "Langton's Ant SDL",
        win_width,
        win_height,
        SDL_WINDOW_OPENGL);
    if (window == NULL) cout << "Window initialisation error " << SDL_GetError() << endl;

    // Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    // SDL Texture
    SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,
        win_width, win_height);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set renderer to black
    SDL_RenderClear(renderer);

    // Objects
    EvolutionClass evolveObj(win_width, win_height, 20, 2, 1);
    evolveObj.createGrids();
    evolveObj.antCentre();
    evolveObj.renderGrids(renderer);

    int frame = 0;
    int sleep = 1000;
    bool pause = true;
    bool running = true;
    // Main Cycle
    while (running) {
        // Do when unpaused
        if (!pause) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep)); // Pause

            // print ant position
            frame++;
            if (frame % 120) {
                cout << "Ant position: " << evolveObj.langton_x << " " << evolveObj.langton_y;
                cout << " | direction: " << evolveObj.langton_direction << endl;
            }

            SDL_SetRenderTarget(renderer, texture); // set render to texture

            // Logic loop
            evolveObj.langtons(renderer);
            evolveObj.copyGridNext();
        }

        // Input logic
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_KEY_DOWN) {
                cout << "Keydown\n";
                cout << event.key.key << " ";
                if (event.key.key == SDLK_ESCAPE || event.key.key == SDLK_Q) {
                    running = false; cout << "Quitting\n";
                }
                else if (event.key.key == SDLK_P) {
                    pause = !pause; cout << ((pause) ? "Paused\n" : "Unpaused\n");
                }
                else if (event.key.key == SDLK_R) {
                    evolveObj.restartGrids(); cout << "Restarting\n";
                    evolveObj.antCentre();
                    evolveObj.renderGrids(renderer);
                }
                else if (event.key.key == SDLK_S) {
                    sleep = (sleep == 1000) ? 0 : 1000;
                }
            }
            else if (event.type == SDL_EVENT_QUIT) {
                running = false; cout << "Window closed\n";
            }
        }

        // Render
        // evolveObj.renderGrids(renderer);
        SDL_SetRenderTarget(renderer, NULL); // set render back to screen
        SDL_RenderTexture(renderer, texture, NULL, NULL); // render texture to screen renderer

        SDL_RenderPresent(renderer); // displays what the renderer has done
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();

}

