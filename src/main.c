#include "main.h"

#include "game.h"
#include "menu.h"

int main(int argc, char **argv)
{
	game_state *state = game_init();
	if(state == NULL) {
		return -1;
	}

	menu_init();
	
	game_term(state);
	
	return 0;
}
