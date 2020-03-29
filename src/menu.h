#ifndef __MENU_H__
#define __MENU_H__

typedef struct {
	char *text;
	void (*click)(void *);
}menu_entry;

typedef struct {
	menu_entry **menu;
	size_t entries;
}menu;

menu *menu_init(void);
void menu_term(menu *m);
	
menu_entry *menu_entry_init(char *text, void (*click)(void *));
void menu_entry_term(menu_entry *m);



#endif
