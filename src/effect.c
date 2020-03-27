#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "effect.h"

effect *effect_init(sdl_state *state)
{
	effect *e = malloc(sizeof(effect));

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
	
}

