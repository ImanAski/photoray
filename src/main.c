#include <SDL3/SDL.h>
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "phoray.h"
#include "component.h"
#include "vector.h"
#include "scattering_matrix.h"
#include "matrix.h"
#include "scene.h"

int main(void)
{
    // SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    if (!TTF_Init()) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow("PhotonRay", 800, 600, 0);

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font *font =
        TTF_OpenFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf", 16);

    if (!font) {
        SDL_Log("Could not load font: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Scene
    Scene scene;
    scene_init(&scene);

    Component *laser = scene_add(&scene, (Component){
    .x = 80,
    .y = 220,
    .w = 170,
    .h = 90,
    .name = "L1",
    .sub = "1550 nm",
});

Component *splitter = scene_add(&scene, (Component){
    .x = 340,
    .y = 220,
    .w = 170,
    .h = 90,
    .name = "BS",
    .sub = "50/50",
    .input_count = 1,
    .output_count = 2,
});

Component *fiber1 = scene_add(&scene, (Component){
    .x = 620,
    .y = 120,
    .w = 170,
    .h = 90,
    .name = "F1",
    .sub = "5 m",
});

Component *fiber2 = scene_add(&scene, (Component){
    .x = 620,
    .y = 320,
    .w = 170,
    .h = 90,
    .name = "F2",
    .sub = "10 m",
});

scene_connect(&scene, laser, 0, splitter, 0);
scene_connect(&scene, splitter, 0, fiber1, 0);
scene_connect(&scene, splitter, 1, fiber2, 0);

    bool running = true;

    while (running) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
        SDL_RenderClear(renderer);

        scene_render(&scene, renderer, font);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
