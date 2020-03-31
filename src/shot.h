#ifndef __SHOT_H__
#define __SHOT_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <SDL2/SDL.h>

#include "render.h"
#include "player.h"
#include "object.h"

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
	int radius;
}shot;

shot *shot_init(sdl_state *state, player *owner);
int shot_term(shot *s);

void shot_out(sdl_state *state, shot *s);
void shot_object_collide(shot *s, object *o);
bool shot_player_collide(shot *s, player *p);
void shot_update(shot *s, object **objects, size_t object_count,
		 player **players, size_t player_count, float delta);

void shot_draw(sdl_state *state, shot *s);

#endif
