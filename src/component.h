#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define MAX_COMPONENTS 1024

typedef struct Component Component;

typedef enum {
  COMPONENT_LASER,
  COMPONENT_FIBER,
} ComponentType;

typedef void (*ComponentRenderFn)(Component *component, SDL_Renderer *renderer, TTF_Font *font);

typedef struct Component {
  float x, y;
  float w, h;
  
  const char *name;
  const char *sub;

  int input_count;
  int output_count;

  ComponentType type;
  
  void *data;

  ComponentRenderFn render;
} Component;


void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, float x, float y);
void drawComponent(SDL_Renderer *r, TTF_Font *font, Component c);

#endif
