#ifndef __SHOT_H__
#define __SHOT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "render.h"

typedef enum {
	NORMAL, BOUNCING, FUNCTION, SPLIT
}shot_type;

typedef struct {
	shot_type type;
	player *owner;

	float xvel;
	float yvel;
	float x;
	float y;
	int width;
	int height;
	SDL_Texture *sprite;
}shot;

shot *shot_init(sdl_state *state, player *owner, shot_type type, char *filename);
int shot_term(shot *s);

void shot_normal_update(shot *s, float delta);

#endif
