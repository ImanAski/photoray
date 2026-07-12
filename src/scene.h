#ifndef SCENE_H
#define SCENE_H

#include "component.h"

#define MAX_COMPONENTS 1024
#define MAX_CONNECTIONS 4096

typedef struct {
    Component *from;
    int from_port;

    Component *to;
    int to_port;
} Connection;

typedef struct {
  Component components[MAX_COMPONENTS];
  int component_count;
  
  bool dragging;
  Component *selected;
  Connection connections[MAX_CONNECTIONS];
  int connection_count;
} Scene;

void scene_init(Scene *scene);

Component *scene_add(Scene *scene, Component component);

void scene_connect(Scene *scene,
                   Component *from, int out_port,
                   Component *to, int in_port);

void scene_render(Scene *scene,
                  SDL_Renderer *renderer,
                  TTF_Font *font);

#endif
