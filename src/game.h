#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

#include "render.h"

#include "arena.h"
#include "player.h"
#include "shot.h"
#include "effect.h"

typedef struct {
	bool quit;
	sdl_state *sdl;
	
	arena *the_arena;

	int effect_count;
	effect *effects;
	
	int player_count;
	player *players;

	int shot_count;
	shot *shots;
}game_state;

game_state *game_init();
int game_term(game_state *game);

int main_game_loop();
int render(game_state *state);
int input(game_state *state);
int update(game_state *state);

#endif
