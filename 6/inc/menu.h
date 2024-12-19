#ifndef MENU_H
#define MENU_H

#define MAX_WORD_LEN 20

void print_menu(void);

int read_choice(int *choice);

int read_word(char **word);

int read_letter(char *letter);

#endif