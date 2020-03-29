#ifndef __SHOT_H__
#define __SHOT_H__

#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "player.h"
#include "render.h"

typedef struct {
	SDL_Texture *sprite;
	int width;
	int height;
	
	bool out;
	player *owner;

	float xvel;
	float yvel;
	float x;
	float y;
}shot;

shot *shot_init(sdl_state *state, player *owner);
int shot_term(shot *s);

void shot_out(sdl_state *state, shot *s);
void shot_normal_update(shot *s, float delta);

void shot_draw(sdl_state *state, shot *s);

#endif
