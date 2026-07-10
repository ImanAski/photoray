#ifndef PARSER_H
#define PARSER_H

#define MAX_COMPONENT 32

typedef struct
{
  char type[32];
  char label[64];


  float x;
  float y;
} Component;

typedef struct
{
    Component components[MAX_COMPONENTS];
    int count;
} Scene;

#endif
