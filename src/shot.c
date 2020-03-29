#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shot.h"

#include "shapes.h"
#include "util.h"

shot *shot_init(sdl_state *state, player *owner)
{
	shot *s = calloc(1, sizeof(shot));

	int size = mini(16 * state->xscale, 16 * state->yscale);
	int radius = size/2 - 1;

	uint32_t *bitmap = calloc(size * size, sizeof(uint32_t));
	draw_circle(bitmap, owner->shot_colour, size, size/2, size/2, radius);
	
	SDL_Surface *temp = SDL_CreateRGBSurfaceFrom((void *)bitmap,
						     size,
						     size,
						     32,
						     4*size,
						     0xFF000000,
						     0x00FF0000,
						     0x0000FF00,
						     0x000000FF);
	if(!temp) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	
	s->sprite = SDL_CreateTextureFromSurface(state->renderer, temp);
	free(bitmap);
	if(!s->sprite) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	
	s->width = size;
	s->height = size;
	
       	s->out = false;
	s->owner = owner;
	
	s->x = owner->x + owner->width/2;
	s->y = owner->y + owner->height/2;
	s->xvel = cosf(owner->direction) * owner->power;
	s->yvel = sinf(owner->direction) * owner->power;
	
	return s;
}

int shot_term(shot *s)
{
	SDL_DestroyTexture(s->sprite);
	free(s);
	
	return 0;
}

void shot_out(sdl_state *state, shot *s)
{
	if(s->x < 0 || s->x > state->window_width ||
	   s->y < 0 || s->y > state->window_height ){
		s->out = true;
	}
}

void shot_normal_update(shot *s, float delta)
{
	s->x -= s->xvel * delta;
	s->y -= s->yvel * delta;
}

void shot_draw(sdl_state *state, shot *s)
{
	SDL_RenderCopy(state->renderer,
			       s->sprite,
			       NULL,
			       &(SDL_Rect){s->x,
					   s->y,
					   s->width,
					   s->height});
}
