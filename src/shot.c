#include <stdlib.h>
#include <stdio.h>

#include "shot.h"

shot *shot_init(sdl_state *state, player *owner, shot_type type, char *filename, float delta)
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
	
	s->pos = malloc(sizeof(SDL_Rect));
	s->pos->w = 3;
	s->pos->h = 3;
	s->pos->x = owner->x;
	s->pos->y = owner->y;
	s->vel = delta;

	return s;
}

int shot_term(shot *s)
{
	free(s->pos);
	SDL_DestroyTexture(s->sprite);
	free(s);
	
	return 0;
}
