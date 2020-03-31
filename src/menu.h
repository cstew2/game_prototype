#ifndef __MENU_H__
#define __MENU_H__

#include "game.h"

typedef struct {
	SDL_Texture *tex;
	void (*click)(game_state *);
	void *arg;
}menu_entry;

typedef struct {
	SDL_Texture *title;
	SDL_Texture *sub;
	menu_entry **entries;
	size_t entry_count;
	
}menu;


menu *menu_init(game_state *state, char *title, char *subtitle);
void menu_term(menu *m);
	
menu_entry *menu_entry_init(game_state *state, char *text, char *font, int size, uint32_t colour,
			    void (*click)(game_state *), void *arg);
void menu_entry_term(menu_entry *m);

void draw_menu(menu *m, game_state *state);

void menu_loop(menu *m, game_state *state);

#endif
