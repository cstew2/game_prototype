#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"

int main(int argc, char **argv)
{
	main_game_loop();
	
	return 0;
}

game_state *game_init()
{
	if(SDL_Init(SDL_INIT_AUDIO |
		    SDL_INIT_TIMER |
		    SDL_INIT_VIDEO |
		    SDL_INIT_EVENTS |
		    SDL_INIT_GAMECONTROLLER)) {
		printf("Error initializing SDL");
		return NULL;
	}
	
	game_state *state = malloc(sizeof(game_state));
	state->quit = false;

	state->sdl = sdl_init();
	if(!state->sdl) {
		return NULL;
	}
	
	state->the_arena = arena_init(state->sdl, "./res/graph_tex.svg");
	if(!state->the_arena) {
		return NULL;
	}
	
	state->player_count = 0;
	state->shot_count = 0;
	state->effect_count = 0;
	
	
	return state;
}

int game_term(game_state *game)
{
	sdl_term(game->sdl);
	free(game);
	SDL_Quit();
	return 0;
}

int main_game_loop()
{
	game_state *state = game_init();
	if(state == NULL) {
		return -1;
	}
	while(!state->quit) {
		input(state);
		update(state);
		render(state);
	}
	game_term(state);
	return 0;
}

int render(game_state *state)
{
	SDL_RenderClear(state->sdl->renderer);

	//draw background
	SDL_RenderCopy(state->sdl->renderer,
		       state->the_arena->background,
		       &(SDL_Rect){0, 0, 256, 256},
		       &(SDL_Rect){128, 128, 256, 256});

	//draw enviromental elements
	for(int i=0; i < state->player_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
				state->players[i].sprite,
				state->players[i].pos,
				NULL);
	}
	
	//draw players
	for(int i=0; i < state->player_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
				state->players[i].sprite,
			       state->players[i].pos,
				NULL);
	}

	//draw shots
	for(int i=0; i < state->player_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
				state->players[i].sprite,
			       state->players[i].pos,
				NULL);
	}
	
	SDL_RenderPresent(state->sdl->renderer);
	return 0;
}

int input(game_state *state)
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			state->quit = true;
		}
		else if(event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				state->quit = true;
				break;
			default:
				break;
			}
		}
	}
	return 0;	
}

int update(game_state *state)
{
	SDL_UpdateWindowSurface(state->sdl->window);
	return 0;	
}
