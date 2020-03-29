#include <stdlib.h>
#include <math.h>

#include "object.h"
#include "shapes.h"

object *object_init(sdl_state *state, object_type t, object_shape s, uint32_t colour,
		    float x, float y, point *vertices, size_t vertex_count)
{
	object *o = calloc(1, sizeof(object));

	float x_vals[vertex_count];
	float y_vals[vertex_count];

	for(int i=0; i < vertex_count; i++) {
		x_vals[i] = vertices[i].x;
		y_vals[i] = vertices[i].y;
	}
	
	o->width = max_arrayf(x_vals, vertex_count);
	o->height = max_arrayf(y_vals, vertex_count);

	uint32_t *bitmap = calloc(o->width * o->height, sizeof(uint32_t));
	draw_poly(bitmap, colour, o->width, o->height, vertices, vertex_count);

	SDL_Surface *temp = SDL_CreateRGBSurfaceFrom((void *)bitmap,
						     o->width,
						     o->height,
						     32,
						     4*o->width,
						     0xFF000000,
						     0x00FF0000,
						     0x0000FF00,
						     0x000000FF);
	if(!temp) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	
	o->sprite = SDL_CreateTextureFromSurface(state->renderer, temp);
	free(bitmap);
	if(!o->sprite) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	
	
	
	o->type = t;
	o->shape = s;
	o->x = x;
	o->y = y;
	memcpy(o->vertices, vertices, vertex_count);
	o->vertex_count = vertex_count;
	
	return o;
}

int object_term(object *o)
{
	SDL_DestroyTexture(o->sprite);
	free(o);
	return 0;
}

void object_draw(sdl_state *state, object *o)
{
	
}
