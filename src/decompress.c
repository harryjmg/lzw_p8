#include "lzw_p8.h"

static int 		puis(int n, int p) {
	if (p == 0)
		return (1);
	if (p == 1)
		return (n);
	return (n * puis(n, p - 1));
}

static int 		max_val(nb_bits) {
	return (puis(2, nb_bits) - 1);
}


void			decompress(char *src_file_name, char *dest_file_name) {
	t_dico		*dico;
	char 		*word = "";
	char 		*entry = "";
	int 		bits_to_read, c;
	char 		code[2];
	FILE 		*src_ptr, *dst_ptr;

	src_ptr = fopen(src_file_name, "r");
	if (src_ptr == NULL) {
		printf("Error : src_file cannot be opened\n");
		return ;
	}
	dst_ptr = fopen(dest_file_name, "w");
	if (dst_ptr == NULL) {
		printf("Error : dest_file cannot be opened");
		return ;
	}
	init_dico(&dico);
	bits_to_read = 8;
	fread(&code, 1, 1, src_ptr);
	c = code[0];
	word = char_to_string(c);
	fwrite(word, 1, 1, dst_ptr);
	while (fread(&code, 1, 1, src_ptr) > 0) {
		c = abs(code[0]);
		if (c == max_val(bits_to_read))
			bits_to_read++;
		else {
			if (c > max_val(bits_to_read - 1) && is_entry_in_dico(dico, c))
				entry = get_word_in_dico(dico, c);
			else if (c > max_val(bits_to_read - 1) && is_entry_in_dico(dico, c) == 0)
				entry = string_and_char(word, word[0]);
			else
				entry = char_to_string(c);
			fwrite(entry, 1, strlen(entry), dst_ptr);
			add_to_dico(&dico, string_and_char(word, entry[0]), 0);
			word = strdup(entry);
		}
	}
}