#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	SDL_Rect *pos;
	SDL_Texture *sprite;
}player;

player *player_init();
player *player_term();

#endif
