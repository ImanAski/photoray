#include "component.h"

void drawText(SDL_Renderer *renderer,
                     TTF_Font *font,
                     const char *text,
                     float x,
                     float y)
{
    SDL_Color color = {255,255,255,255};

    SDL_Surface *surface = TTF_RenderText_Blended(
        font,
        text,
        0,
        color
    );

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FRect dst = {
        x,
        y,
        (float)surface->w,
        (float)surface->h
    };

    SDL_RenderTexture(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}


void drawComponent(SDL_Renderer *r, TTF_Font *font, Component c) {
  SDL_FRect body = {
    c.x,
    c.y,
    c.w,
    c.h
  };

  SDL_FRect header = {
    c.x,
    c.y,
    c.w,
    28
  };

  SDL_SetRenderDrawColor(r, 45, 45, 55, 255);
  SDL_RenderFillRect(r, &body);

  SDL_SetRenderDrawColor(r, 70, 90, 100, 255);
  SDL_RenderFillRect(r, &header);

  drawText(r, font, c.name, c.x + 8, c.y + 5);
  drawText(r, font, c.sub, c.x + 8, c.y + 40);

  /* ports */
    SDL_FRect left = {
        c.x - 4,
        c.y + c.h/2 - 4,
        8,
        8
    };

    SDL_FRect right = {
        c.x + c.w - 4,
        c.y + c.h/2 - 4,
        8,
        8
    };

    SDL_SetRenderDrawColor(r, 255,220,0,255);
    SDL_RenderFillRect(r, &left);
    SDL_RenderFillRect(r, &right);
};
