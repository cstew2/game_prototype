#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SDL2/SDL.h>

#include "util.h"
#include "render.h"


typedef enum {
	object_bounce, object_absorb, object_reflect
}object_type;

typedef enum {
	object_line, object_circle, object_polygon
}object_shape;

typedef struct {
	SDL_Texture *sprite;
	int width;
	int height;
	
	object_type type;
	object_shape shape;	
	
	float x;
	float y;

	point *vertices;
	size_t vertex_count;

}object;

object *object_init(sdl_state *state, object_type t, object_shape s, uint32_t colour,
		    float x, float y, point *vertices, size_t vertex_count);
int object_term(object *o);

void object_draw(sdl_state *state, object *o);

#endif
