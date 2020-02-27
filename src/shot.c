#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shot.h"

shot *shot_init(sdl_state *state, player *owner, shot_type type, char *filename)
{
	shot *s = malloc(sizeof(shot));

	SDL_Surface *temp = IMG_Load(filename);
	if(!temp) {
		printf("Can't load \"%s\"\nSDL2_Image Error: %s\n",
		       filename, IMG_GetError());
		return NULL;
	}
	s->sprite = SDL_CreateTextureFromSurface(state->renderer, temp);
	if(!s->sprite) {
		return NULL;
	}

	s->type = type;
	s->owner = owner;
	
	s->width = 5;
	s->height = 5;
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

void shot_normal_update(shot *s, float delta)
{
	s->x -= s->xvel * delta;
	s->y -= s->yvel * delta;
}
