#include "lzw_p8.h"

static void		write_more_bits_signal(int nb_bits)
{
	while (nb_bits > 0)
	{
		printf("1");
		nb_bits--;
	}
}

void			compress(char *text) {
	t_dico		*dico;
	t_strlst	*binaries;
	t_charlst	*cooked;
	int			i = 0, bits_written;
	char		*word = "";

	dico = NULL;
	binaries = NULL;
	cooked = NULL;
	init_dico(&dico);
	bits_written = 8;
	while (text[i]) {
		if (need_more_bits(dico, bits_written)) {
			write_more_bits_signal(bits_written);
			bits_written++;
		}
		if (is_in_dico(dico, string_and_char(word, text[i])))
			word = string_and_char(word, text[i]);
		else {
			add_to_dico(&dico, string_and_char(word, text[i]), 0);
			add_to_strlst(&binaries, is_in_dico(dico, word), bits_written);
			free(word);
			revive_word(word, text[i]);
		}
		i++;
	}
	add_to_strlst(&binaries, is_in_dico(dico, word), bits_written);
	
	print_strlst(binaries);

	printf("\n");
}