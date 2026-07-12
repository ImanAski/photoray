#include "scene.h"
#include <stdio.h>

void scene_init(Scene *scene)
{
    scene->component_count = 0;
    scene->connection_count = 0;

    scene->selected = NULL;
    scene->dragging = false;
}

Component *scene_add(Scene *scene, Component component)
{
    if (scene->component_count >= MAX_COMPONENTS)
        return NULL;

    scene->components[scene->component_count] = component;

    return &scene->components[scene->component_count++];
}

void scene_connect(Scene *scene,
                   Component *from,
                   int out_port,
                   Component *to,
                   int in_port)
{
    if (scene->connection_count >= MAX_CONNECTIONS)
        return;

    scene->connections[scene->connection_count++] =
        (Connection){
            .from = from,
            .from_port = out_port,
            .to = to,
            .to_port = in_port,
        };
}

void scene_render(Scene *scene,
                  SDL_Renderer *renderer,
                  TTF_Font *font)
{
    // draw wires first
    for (int i = 0; i < scene->connection_count; i++) {

      Connection *c = &scene->connections[i];


        float x1 = c->from->x + c->from->w;
        float y1 = c->from->y + c->from->h / 2.0f;

        float x2 = c->to->x;
        float y2 = c->to->y + c->to->h / 2.0f;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }

    // draw components
    for (int i = 0; i < scene->component_count; i++) {
        drawComponent(renderer, font, scene->components[i]);
    }
}
