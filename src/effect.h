#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum {
	polar, hyperbolic, 
} effect_type;
	
typedef struct {
	SDL_Rect *pos;
	SDL_Texture *sprite;
}effect;

#endif
