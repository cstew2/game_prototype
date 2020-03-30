#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL_ttf.h>

#include "menu.h"

menu *menu_init(game_state *state, char *title, char *subtitle)
{
	menu *m = calloc(1, sizeof(menu));

	TTF_Font* sans24 = TTF_OpenFont("Sans.ttf", 24);
	TTF_Font* sans16 = TTF_OpenFont("Sans.ttf", 16);
	SDL_Colour black = {0, 0, 0, 255};
	SDL_Surface *titlesur = TTF_RenderText_Solid(sans24, title, black);
	SDL_Surface *subsur = TTF_RenderText_Solid(sans16, subtitle, black);
	
	m->title = SDL_CreateTextureFromSurface(state->sdl->renderer, titlesur);
	m->sub = SDL_CreateTextureFromSurface(state->sdl->renderer, subsur);
	
	SDL_FreeSurface(titlesur);
	SDL_FreeSurface(subsur);
	TTF_CloseFont(sans24);
	TTF_CloseFont(sans16);
	
	m->entries = calloc(3, sizeof(menu_entry *));
	m->entries[0] = menu_entry_init(state, "Start Game", "Sans.ttf", 20, 0x000000FF, main_game_loop, state);
	m->entries[1] = menu_entry_init(state, "Options", "Sans.ttf", 20, 0x000000FF, NULL, NULL);
	m->entries[2] = menu_entry_init(state, "Quit", "Sans.ttf", 20, 0x000000FF, game_term, state);
	
	return m;
}

void menu_term(menu *m)
{
	for(int i=0; i < m->entry_count; i++) {
		menu_entry_term(m->entries[i]);
	}
	free(m);
}

menu_entry *menu_entry_init(game_state *state, char *text, char *font, int size, uint32_t colour,
			    void (*click)(game_state *), void *arg)
{
	menu_entry *m = calloc(1, sizeof(menu_entry));
	
	TTF_Font* ttf = TTF_OpenFont(font, size);
	SDL_Surface *s = TTF_RenderText_Solid(ttf, text, (SDL_Colour){
			        .r=(colour & 0xFF000000) >> 24,
				.g=(colour & 0x00FF0000) >> 16,
				.b=(colour & 0x0000FF00) >> 8});
	m->tex = SDL_CreateTextureFromSurface(state->sdl->renderer, s);
	SDL_FreeSurface(s);
	TTF_CloseFont(ttf);
	
	m->click = click;
	m->arg = arg;
	return m;
}

void menu_entry_term(menu_entry *m)
{
	SDL_DestroyTexture(m->tex);
	free(m);
}

void draw_menu(menu *m, game_state *state)
{
	
	
}

void menu_loop(menu *m, game_state *state)
{
	SDL_RenderClear(state->sdl->renderer);
	SDL_SetRenderDrawColor(state->sdl->renderer, 255, 255, 255, 255);

	int w = 0;
	int h = 0;
	
	//draw title
	SDL_QueryTexture(m->title, NULL, NULL, &w, &h);
	SDL_RenderCopy(state->sdl->renderer,
		       m->title,
		       NULL,
		       &(SDL_Rect){10,
				       10,
				       w,
				       h});

	
	
	//draw menu
	draw_menu(m, state);
		
	SDL_RenderPresent(state->sdl->renderer);
}
