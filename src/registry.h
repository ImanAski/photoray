#ifndef REGISTRY_H
#define REGISTRY_H

#include "component.h"

typedef struct {
  Component components[MAX_COMPONENTS];
  int count;
} Registry;

void Registry_Init(Registry *registry);

Component *Registry_Add(Registry *registry);

void Registry_Render(
    Registry *registry,
    SDL_Renderer *renderer,
    TTF_Font *font);
 
#endif
