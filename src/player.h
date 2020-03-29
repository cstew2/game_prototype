#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "render.h"

typedef struct {
	SDL_Texture *sprite;
	int width;
	int height;
	
	float x;
	float y;
	float vel;

	bool up;
	bool down;
	bool left;
	bool right;

	float direction;
	float power;
	
	uint32_t shot_colour;

	float fuel;
}player;

player *player_init(sdl_state *state, int x, int y, float vel, uint32_t colour);
int player_term(player *p);

void player_draw(sdl_state *state, player *p);

#endif
