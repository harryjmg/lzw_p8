#include "lzw_p8.h"

static int 		puis(int n, int p) {
	if (p == 0)
		return (1);
	if (p == 1)
		return (n);
	return (n * puis(n, p - 1));
}

static int 		read_bits(char *str, int bits_to_read) {
	int 		val;
	int 		i;

	val = 0;
	i = 0;
	while (bits_to_read > 0) {
		if (str[bits_to_read - 1] == '1')
			val = val + puis(2, i);
		bits_to_read--;
		i++;
	}
	return (val);
}

static int 		max_val(nb_bits) {
	return (puis(2, nb_bits) - 1);
}


void			decompress(char *code) {
	t_dico		*dico;
	char 		*word = "";
	char 		*entry = "";
	int 		bits_to_read, i, c;

	init_dico(&dico);
	bits_to_read = 8;
	i = 0;
	c = read_bits(code + i, bits_to_read);
	word = char_to_string(c);
	printf("%s", word);
	i += bits_to_read;
	while (code[i]) {
		c = read_bits(code + i, bits_to_read);
		if (c == max_val(bits_to_read))
			bits_to_read++;
		else {
			if (c > max_val(bits_to_read - 1) && is_entry_in_dico(dico, c))
				entry = get_word_in_dico(dico, c);
			else if (c > max_val(bits_to_read - 1) && is_entry_in_dico(dico, c) == 0)
				entry = string_and_char(word, word[0]);
			else
				entry = char_to_string(c);
			printf("%s", entry);
			add_to_dico(&dico, string_and_char(word, entry[0]), 0);
			word = strdup(entry);
		}
		i += bits_to_read;
	}
	printf("\n");
}