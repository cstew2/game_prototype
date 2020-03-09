#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "game.h"

static int MAX_SHOTS = 128;

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
	
	state->the_arena = arena_init(state->sdl,
				      "./res/graph_tex.png");
	if(!state->the_arena) {
		return NULL;
	}

	state->player_count = 1;
	state->players = malloc(sizeof(player)*state->player_count);
	state->players[0] = player_init(state->sdl,
					"./res/circle.png",
					20,
					20,
					0.25);
	if(!state->players[0]) {
		return NULL;
	}
	
	
	state->shot_count = 0;
	state->shots = malloc(sizeof(shot) * MAX_SHOTS);
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
	SDL_SetRenderDrawColor(state->sdl->renderer, 255, 255, 255, 255);
	
	//draw background
	SDL_RenderCopy(state->sdl->renderer,
		       state->the_arena->background,
		       NULL,
		       NULL);

	//draw enviromental elements
	for(int i=0; i < state->effect_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
			       state->effects[i]->sprite,
			       NULL,
			       state->effects[i]->pos);
	}
	
	//draw players
	for(int i=0; i < state->player_count; i++) {
		SDL_RenderCopy(state->sdl->renderer,
			       state->players[i]->sprite,
			       NULL,
			       &(SDL_Rect){state->players[i]->x,
					   state->players[i]->y,
					   state->players[i]->width,
					   state->players[i]->height});
	}
	
	//draw shots
	for(int i=0; i < state->shot_count; i++) {
		shot_draw(state->sdl, state->shots[i]);
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
				state->shots[state->shot_count++] = shot_init(state->sdl,
									      state->players[0],
									      "./res/circle.png");
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

	for(int i=0; i < state->shot_count; i++) {
		shot_normal_update(state->shots[i], delta);
	}
       	
	state->last_ticks = SDL_GetTicks();
	
	return 0;	
}
