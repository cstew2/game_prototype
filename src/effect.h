#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <SDL2/SDL.h>

#include "render.h"

typedef enum {
	polar, hyperbolic, 
} effect_type;
	
typedef struct {
	SDL_Texture *sprite;

	int width;
	int height;
	float x;
	float y;
}effect;

effect *effect_init(sdl_state *state);
int effect_term(effect *s);

void effect_normal_update(effect *s, float delta);

void effect_draw(sdl_state *state, effect *s);


#endif
