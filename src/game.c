#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

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
	
	game_state *state = calloc(1, sizeof(game_state));
	state->quit = false;

	state->sdl = sdl_init();
	if(!state->sdl) {
		return NULL;
	}
	
	state->arena = arena_init(state->sdl, 32, 32);
	if(!state->arena) {
		return NULL;
	}

	state->player_count = 1;
	state->players = calloc(state->player_count, sizeof(player));
	state->players[0] = player_init(state->sdl,
					20,
					20,
					0.25,
					0xFF0000FF);
	if(!state->players[0]) {
		return NULL;
	}
	
	state->shot_max = 128;
	state->shots = calloc(state->shot_max, sizeof(shot));
	state->shot_start = 0;
	state->shot_end = 0;
	
	state->effect_count = 0;
	
	return state;
}

int game_term(game_state *state)
{
	sdl_term(state->sdl);
	arena_term(state->arena);

	for(int i=0; i < state->player_count; i++) {
		player_term(state->players[i]);
	}
	free(state->players);

	for(int i=0; i < state->effect_count; i++) {
		effect_term(state->effects[i]);
	}	

	while(1) {
		int idx = (state->shot_start) % state->shot_max;
		if(idx == state->shot_end) {
			break;
		}
		shot_term(state->shots[idx]);
		state->shot_start++;
	}
	free(state->shots);
	
	free(state);
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
	SDL_SetRenderDrawColor(state->sdl->renderer, 255, 255, 255, 255);
	
	//draw background
	SDL_RenderCopy(state->sdl->renderer,
		       state->arena->background,
		       NULL,
		       NULL);

	//draw enviromental elements
	for(int i=0; i < state->effect_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
			       state->effects[i]->sprite,
			       NULL,
			       &(SDL_Rect){state->effects[i]->x,
					       state->effects[i]->y,
					       state->effects[i]->width,
					       state->effects[i]->height});
	}
	
	//draw players
	for(int i=0; i < state->player_count; i++) {
		player_draw(state->sdl, state->players[i]);
	}
	
	//draw shots
	for(int i=0; i < state->shot_max; i++) {
		int idx = (state->shot_start + i) % state->shot_max;
		if(idx == state->shot_end) {
			break;
		}
		shot_draw(state->sdl, state->shots[idx]);
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
			case SDLK_w:
				state->players[0]->up = true;
				break;
			case SDLK_a:
				state->players[0]->left = true;
				break;
			case SDLK_s:
				state->players[0]->down = true;
				break;
			case SDLK_d:
				state->players[0]->right = true;
				break;
			case SDLK_SPACE:
				state->shots[state->shot_end] = shot_init(state->sdl, state->players[0]);
				state->shot_end = (state->shot_end + 1) % state->shot_max;
				break;
			default:
				break;
			}
		}
		else if(event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				state->players[0]->up = false;
				break;
			case SDLK_a:
				state->players[0]->left = false;
				break;
			case SDLK_s:
				state->players[0]->down = false;
				break;
			case SDLK_d:
				state->players[0]->right = false;
				break;
			case SDLK_SPACE:
				
				break;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			int x;
			int y;
			SDL_GetMouseState(&x, &y);

			if(event.button.button == SDL_BUTTON_LEFT) {
				state->players[0]->direction = atan2(y - state->players[0]->y,
								     x - state->players[0]->x);
			}	
		}
	}
	
	return 0;	
}

int update(game_state *state)
{
	float ticks = SDL_GetTicks();
	float delta = state->last_ticks - ticks;
		
	SDL_UpdateWindowSurface(state->sdl->window);

	//update 
	if(state->players[0]->up) {
		state->players[0]->y += state->players[0]->vel * delta;
	}
	if(state->players[0]->down) {
		state->players[0]->y -= state->players[0]->vel * delta;
	}
	if(state->players[0]->left) {
		state->players[0]->x += state->players[0]->vel * delta;
	}
	if(state->players[0]->right) {
		state->players[0]->x -= state->players[0]->vel * delta;
	}

	for(int i=0; i < state->shot_max; i++) {
		int idx = (state->shot_start + i) % state->shot_max;
		if(idx == state->shot_end) {
			break;
		}
		shot_out(state->sdl, state->shots[idx]);
		shot_normal_update(state->shots[idx] , delta);
	}

	while(1) {
		int idx = (state->shot_start) % state->shot_max;
		if(idx == state->shot_end) {
			break;
		}
		if(state->shots[idx]->out) {
			shot_term(state->shots[idx]);
			state->shot_start++;
		}
		else{
			break;
		}
	}
	
	state->last_ticks = SDL_GetTicks();
	
	return 0;	
}
