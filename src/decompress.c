#include "lzw_p8.h"

static int 		puis(int n, int p) {
	if (p == 0)
		return (1);
	if (p == 1)
		return (n);
	return (n * puis(n, p - 1));
}

static int 		max_val(int nb_bits) {
	return (puis(2, nb_bits));
}

static int 		get_code(t_charlst **lst, int bits_to_read) {
	int 		res;
	t_charlst 	*tmp;

	res = 0;
	tmp = *lst;
	while (bits_to_read) {
		if (tmp->c == '1')
			res = (res << 1) ^ 1;
		else
			res = res << 1;
		//printf("%c", tmp->c);
		tmp = tmp->next;
		if (!tmp)
			return (-1);
		bits_to_read--;
	}
	//printf("\n");
	*lst = tmp;
	return (res);
}

void			decompress(char *src_file_name, char *dest_file_name) {
	t_dico		*dico;
	char 		*word = "";
	char 		*entry = "";
	int 		bits_to_read, c;
	char		code[3];
	FILE 		*src_ptr, *dst_ptr;
	t_charlst 	*char_to_read;
	t_charlst 	*binary_to_read;
	int 		mask, nb_bit;

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
	char_to_read = NULL;
	while (fread(&code, 1, 1, src_ptr) > 0) {
		add_to_charlst(&char_to_read, code[0]);
	}
	binary_to_read = NULL;
	int j = 0;
	while (char_to_read) {
		j++;
		nb_bit = 8;
		while (nb_bit > 0)
		{
			mask = 0;
			mask = (mask ^ 1) << (nb_bit - 1);
			if (mask & char_to_read->c)
				add_to_charlst(&binary_to_read, '1');
			else
				add_to_charlst(&binary_to_read, '0');
			nb_bit--;
		}
		char_to_read = char_to_read->next;
	} 
	c = 0;
	c = get_code(&binary_to_read, bits_to_read);
	entry = char_to_string(c);
	fwrite(entry, 1, strlen(entry), dst_ptr);
	word = char_to_string(c);
	while (binary_to_read) {
		c = 0;
		c = get_code(&binary_to_read, bits_to_read);
		if (c == -1)
		{
			return ;
		}
		
		if (c >= max_val(bits_to_read) - 1) {
			//printf("HERE");
			bits_to_read++;
		}
		
		else {
			if (c > 255 && is_entry_in_dico(dico, c))
				entry = get_word_in_dico(dico, c);
			else if (c > 255 && is_entry_in_dico(dico, c) == 0)
				entry = string_and_char(word, word[0]);
			else
				entry = char_to_string(c);
			//printf("%d\n", c);
			fwrite(entry, 1, strlen(entry), dst_ptr);
			add_to_dico(&dico, string_and_char(word, entry[0]), 0);
			
			word = strdup(entry);

		}
	
	}
}