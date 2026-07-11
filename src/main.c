#include <SDL3/SDL.h>
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "phoray.h"
#include "component.h"
#include "vector.h"

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("failed");
    return 1;
  }

  if (!TTF_Init()) {
    SDL_Log("failed to init ttf");
    return 1;
  }
  
  SDL_Window *window = SDL_CreateWindow("Title", 800, 600, 0);

  if (!window) {
    SDL_Log("failed window");
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  TTF_Font *font =
        TTF_OpenFont("/usr/share/fonts/TTF/FiraCode-Regular.ttf", 16);

  if (!font) {
    SDL_Log("Could not load font. %s", SDL_GetError());
    return 1;
    
  }

  Component laser = {
    100, 200,
    170, 90,
    "L1",
    "1550 nm"
  };

  Component fiber = {350, 200, 170, 90, "FIBER", "10 m"};

  Vector *v = create_vector(3);
  vector_set(v, 0, 1);

  Vector *v1 = create_vector(3);
  vector_set(v1, 1, 3);

  Vector *result = create_vector(3);

  vector_add(result, v, v1);

  printf("normal is %2f\n", vector_norm(result));
  printf("max: %2f, min: %2f\n", vector_max_elem(result),
         vector_min_elem(result));
  printf("distance from v: %d\n", vector_distance(result, v));
  printf("distance from v1: %d\n", vector_distance(result, v1));
  vector_print(result);
  
  
  
  bool running = true;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
	running = false;
    }
    SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
    SDL_RenderClear(renderer);

    
    drawComponent(renderer, font, laser);
    drawComponent(renderer, font, fiber);

    SDL_RenderLine(renderer,
                       laser.x + laser.w,
                       laser.y + laser.h/2,
                       fiber.x,
                       fiber.y + fiber.h/2);
    
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
