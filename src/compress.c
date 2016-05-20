#include "lzw_p8.h"

static void		write_more_bits_signal(int nb_bits)
{
	while (nb_bits > 0)
	{
		printf("1");
		nb_bits--;
	}
}

static void		write_into_dest(char *file_name, t_charlst *cooked) {
	FILE 		*dest_ptr;
	t_charlst 	*tmp;

	dest_ptr = fopen(file_name, "w");
	if (dest_ptr == NULL) {
		printf("Error : File cannot be opened\n");
		return ;
	}
	tmp = cooked;
	while (tmp) {
		fwrite(&(tmp->c), 1, 1, dest_ptr);
		tmp = tmp->next;
	}
}

void			compress(char *src_file_name, char *dest_file_name) {
	t_dico		*dico;
	t_strlst	*binaries;
	t_charlst	*cooked;
	int			bits_written;
	char		*word = "";
	FILE 		*src_file_ptr;
	char 		text[2];

	src_file_ptr = fopen(src_file_name, "r");
	if (src_file_ptr == NULL) {
		printf("Error : File cannot be opened\n");
		return ;
	}
	dico = NULL;
	binaries = NULL;
	cooked = NULL;
	init_dico(&dico);
	bits_written = 8;
	while (fread(&text, 1, 1, src_file_ptr) > 0) {
		if (need_more_bits(dico, bits_written)) {
			write_more_bits_signal(bits_written);
			bits_written++;
		}
		if (is_in_dico(dico, string_and_char(word, text[0])))
			word = string_and_char(word, text[0]);
		else {
			add_to_dico(&dico, string_and_char(word, text[0]), 0);
			add_to_strlst(&binaries, is_in_dico(dico, word), bits_written);
			free(word);
			revive_word(word, text[0]);
		}
	}
	add_to_strlst(&binaries, is_in_dico(dico, word), bits_written);
	binaries_to_charlst(binaries, &cooked);
	write_into_dest(dest_file_name, cooked);
}