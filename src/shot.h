#ifndef __SHOT_H__
#define __SHOT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum {
	normal, bouncing
}shot_type;

typedef struct {
	player *owner;
	
	SDL_Rect *pos;
	SDL_Texture *sprite;
}shot;

#endif
