#include "lzw_p8.h"

static void		write_more_bits_signal(int nb_bits)
{
	while (nb_bits > 0)
	{
		printf("1");
		nb_bits--;
	}
}

static void		write_binary(int number, int nb_bit) 
{
	int 		mask;

	while (nb_bit > 0)
	{
		mask = 0;
		mask = (mask ^ 1) << (nb_bit - 1);
		if (mask & number)
			printf("1");
		else
			printf("0");
		nb_bit--;
	}
}

static void		write_code(t_dico *dico, char *mot, int nb_bit)
{
	t_dico		*tmp;

	tmp = dico;
	while (dico)
	{
		if (strcmp(dico->mot, mot) == 0)
		{
			write_binary(dico->index, nb_bit);
			return ;
		}
		dico = dico->next;
	}
	return ;
} 

void			compress(char *text) {
	t_dico		*dico;
	int			i = 0, bits_written;
	char		*word = "";

	dico = NULL;
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
			write_code(dico, word, bits_written);
			free(word);
			revive_word(word, text[i]);
		}
		i++;
	}
	write_code(dico, word, bits_written);
	printf("\n");
}