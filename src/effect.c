#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "effect.h"

effect *effect_init(sdl_state *state, effect_type t)
{
	effect *e = calloc(1, sizeof(effect));
	e->type = t;
	
	
	
	return e;
}

int effect_term(effect *e)
{
	SDL_DestroyTexture(e->sprite);
	free(e);
	return 0;
}

void effect_normal_update(effect *e, float delta)
{
	
}

void effect_draw(sdl_state *state, effect *e)
{
		SDL_RenderCopy(state->renderer,
		       e->sprite,
		       NULL,
		       &(SDL_Rect){e->x,
				       e->y,
				       e->width,
				       e->height});
}

