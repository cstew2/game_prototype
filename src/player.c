#include <stdlib.h>
#include <stdio.h>

#include "player.h"

player *player_init(sdl_state *state, char *filename, int x, int y, float delta)
{
	player *p = malloc(sizeof(player));
	SDL_Surface *temp = IMG_Load(filename);
	if(!temp) {
		printf("Can't load \"%s\"\nSDL2_Image Error: %s\n",
		       filename, IMG_GetError());
		return NULL;
	}
	p->sprite = SDL_CreateTextureFromSurface(state->renderer, temp);
	if(!p->sprite) {
		return NULL;
	}

	p->up = false;
	p->down = false;
	p->left = false;
	p->right = false;
	
	p->width = 40;
	p->height = 40;
	p->x = x;
	p->y = y;
	p->vel = delta;
	
	return p;
}

int player_term(player *p)
{
	SDL_DestroyTexture(p->sprite);
	free(p);
	return 0;
}
