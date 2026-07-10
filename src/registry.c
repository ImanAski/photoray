#include "registry.h"


void Registry_Init(Registry *registry) {
  registry->count = 0;
}

Component *Registry_Add(Registry *registry)
{
    if (registry->count >= MAX_COMPONENTS)
        return NULL;

    return &registry->components[registry->count++];
}

void Registry_Render(
    Registry *registry,
    SDL_Renderer *renderer,
    TTF_Font *font)
{
    for (int i = 0; i < registry->count; i++)
    {
        Component *c = &registry->components[i];

        if (c->render)
            c->render(c, renderer, font);
    }
}
