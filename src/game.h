#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
#include <stddef.h>

#include "render.h"

#include "arena.h"
#include "effect.h"
#include "player.h"
#include "object.h"
#include "shot.h"

typedef struct {
	bool quit;
	float last_ticks;
	sdl_state *sdl;

	float aspect_ratio;
	float x_scale;
	float y_scale;
	
	arena *arena;

	size_t effect_count;
	effect **effects;
	
	size_t player_count;
	player **players;

	size_t object_count;
	object **objects;
	
	int shot_start;
	int shot_end;
	shot **shots;
	size_t shot_max;
}game_state;

game_state *game_init();
void game_term(game_state *game);

void main_game_loop(game_state *game);

void render(game_state *state);
void input(game_state *state);
void update(game_state *state);

#endif
