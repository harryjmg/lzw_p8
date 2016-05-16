#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct 		s_dico
{
	int				index;
	char			*mot;
	struct s_dico 	*next;
}					t_dico;

int 			need_more_bits(t_dico *dico, int nb_bits);
void			compress(char *text);
void			init_dico(t_dico **dico);
int 			is_in_dico(t_dico *dico, char *mot);
void			add_to_dico(t_dico **dico, char *mot, int base);
char			*string_and_char(char *mot, char lettre);
void			revive_word(char *mot, char c);
char 			*char_to_string(char c);
void			decompress(char *code);
char 			*get_word_in_dico(t_dico *dico, int c);
int 			is_entry_in_dico(t_dico *dico, int c);