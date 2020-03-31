#include <stdlib.h>

#include <SDL2/SDL.h>

#include "game.h"

game_state *game_init()
{
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
	
	state->player_count = 2;
	state->players = calloc(state->player_count, sizeof(player));
	state->players[0] = player_init(state->sdl,
					20,
					20,
					0.25,
					0xFF0000FF,
					0);
	
	state->players[1] = player_init(state->sdl,
					460,
					460,
					0.25,
					0x00FF00FF,
					1);
	if(!state->players[0] || !state->players[1]) {
		return NULL;
	}

	state->object_count = 1;
	size_t vertex_count = 4;
	point *vertices = calloc(vertex_count, sizeof(point));
	vertices[0] = (point){100, 0};
	vertices[1] = (point){120, 20};
	vertices[2] = (point){20, 120};
	vertices[3] = (point){0, 100};
	
	state->objects = calloc(state->object_count, sizeof(object));
	state->objects[0] = object_init(state->sdl, object_reflect, object_polygon, 0xBB1530FF,
					200, 200, vertices, vertex_count);
	free(vertices);
	
	state->shot_max = 128;
	state->shots = calloc(state->shot_max, sizeof(shot));
	state->shot_start = 0;
	state->shot_end = 0;
	
	state->effect_count = 0;
	
	return state;
}

void game_term(game_state *state)
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
}

void main_game_loop(game_state *state)
{
	while(!state->quit) {
		input(state);
		update(state);
		render(state);
	}
}

void render(game_state *state)
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
		effect_draw(state->sdl, state->effects[i]);
	}
	
	//draw players
	for(int i=0; i < state->player_count; i++) {
		player_draw(state->sdl, state->players[i]);
	}

	//draw objects
	for(int i=0; i < state->object_count; i++) {
		object_draw(state->sdl, state->objects[i]);
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
}

void input(game_state *state)
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
				player_aim(state->players[0], x, y);
			}	
		}
	}
}

void update(game_state *state)
{
	float ticks = SDL_GetTicks();
	float delta = state->last_ticks - ticks;
		
	SDL_UpdateWindowSurface(state->sdl->window);

	//update players
	for(int i=0; i < state->player_count; i++) {
		player_move(state->sdl, state->players[i], delta);
	}
	
	//update shots
	for(int i=0; i < state->shot_max; i++) {
		int idx = (state->shot_start + i) % state->shot_max;
		if(idx == state->shot_end) {
			break;
		}
		
		shot_out(state->sdl, state->shots[idx]);
       		shot_update(state->shots[idx], state->objects, state->object_count,
			    state->players, state->player_count, delta);

		
		for(int j=0; j < state->player_count; j++) {
			if(shot_player_collide(state->shots[idx], state->players[j])) {
				printf("Player %i wins\n", state->shots[idx]->owner->num);
			}
		}
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
}
