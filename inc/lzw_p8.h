#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct 			s_dico
{
	int					index;
	char				*mot;
	struct s_dico 		*next;
}						t_dico;

typedef struct 			s_strlst
{
	char 				*str;
	struct s_strlst		*next;
}						t_strlst;

typedef struct 			s_charlst
{
	char 				c;
	struct s_charlst	*next;
}						t_charlst;

int 					need_more_bits(t_dico *dico, int nb_bits);
void					compress(char *src_file_name, char *dest_file_name);
void					init_dico(t_dico **dico);
int 					is_in_dico(t_dico *dico, char *mot);
void					add_to_dico(t_dico **dico, char *mot, int base);
char					*string_and_char(char *mot, char lettre);
void					revive_word(char *mot, char c);
char 					*char_to_string(char c);
void					decompress(char *code);
char 					*get_word_in_dico(t_dico *dico, int c);
int 					is_entry_in_dico(t_dico *dico, int c);
void 					add_to_strlst(t_strlst **lst, int word_index, int nb_bit);
void 					print_strlst(t_strlst *list);
void					fill_str_with_binary(char **str, int binary, int nb_bit);
void					binaries_to_charlst(t_strlst *binaries, t_charlst **cooked);
void					add_to_charlst(t_charlst **lst, char c);
void 					print_charlst(t_charlst *lst);