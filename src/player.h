#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "render.h"

typedef struct {
	int num;
	
	SDL_Texture *sprite;
	int width;
	int height;
	
	float x;
	float y;
	float vel;
	int radius;

	bool up;
	bool down;
	bool left;
	bool right;

	float direction;
	float power;
	
	uint32_t shot_colour;

	float fuel;
}player;

player *player_init(sdl_state *state, int x, int y, float vel, uint32_t colour, int num);
int player_term(player *p);

void player_move(sdl_state *state, player *p, float delta);
void player_draw(sdl_state *state, player *p);
void player_aim(player *p, int x, int y);


#endif
