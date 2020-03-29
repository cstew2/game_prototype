#include <stdlib.h>
#include <string.h>

#include "menu.h"

menu *menu_init()
{
	menu *m = calloc(1, sizeof(menu));
	
	m->menu = calloc(3, sizeof(menu_entry*));
	m->menu[0] = menu_entry_init("Start Game", NULL);
	m->menu[1] = menu_entry_init("Options", NULL);
	m->menu[2] = menu_entry_init("Quit", NULL);
	
	return m;
}

void menu_term(menu *m)
{
	menu_entry_term(m->menu[0]);
	menu_entry_term(m->menu[1]);
	menu_entry_term(m->menu[2]);
	free(m);
}

menu_entry *menu_entry_init(char *text, void (*click)(void *))
{
	menu_entry *m = calloc(1, sizeof(menu_entry));

	strcpy(m->text, text);
	m->click = click;

	return m;
}

void menu_entry_term(menu_entry *m)
{
	free(m->text);
	free(m);
}

