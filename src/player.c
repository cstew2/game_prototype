#include <stdlib.h>
#include <stdio.h>

#include "player.h"

#include "shapes.h"
#include "util.h"

player *player_init(sdl_state *state, int x, int y, float vel, uint32_t colour)
{
	player *p = calloc(1, sizeof(player));

	int size = mini(32 * state->xscale, 32 * state->yscale);
	int radius = size/2 - 2;

	uint32_t *bitmap = calloc(size * size, sizeof(uint32_t));
	draw_circle(bitmap, colour, size, size/2, size/2, radius);

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
	
	p->sprite = SDL_CreateTextureFromSurface(state->renderer, temp);
	free(bitmap);
	if(!p->sprite) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	p->width = size;
	p->height = size;
	
	p->up = false;
	p->down = false;
	p->left = false;
	p->right = false;
	
	p->x = x;
	p->y = y;
	p->vel = vel;
	p->power = 0.5;
	p->direction = M_PI/3;

	p->shot_colour = 0x000000FF;
	
	return p;
}

int player_term(player *p)
{
	SDL_DestroyTexture(p->sprite);
	free(p);
	return 0;
}

void player_draw(sdl_state *state, player *p)
{
	SDL_RenderCopy(state->renderer,
		       p->sprite,
		       NULL,
		       &(SDL_Rect){p->x,
				   p->y,
				   p->width,
				   p->height});
}
