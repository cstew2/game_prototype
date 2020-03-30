#include "main.h"

#include "game.h"
#include "menu.h"

int main(int argc, char **argv)
{
	game_state *state = game_init();
	if(state == NULL) {
		return -1;
	}

	/*
	menu_init(state,
		  "Graph Wars",
		  "Or: How I Learned to Stop Worrying and Love the Maths");
	*/

	main_game_loop(state);
	
	game_term(state);
	
	return 0;
}
