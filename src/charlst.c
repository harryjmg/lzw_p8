#include "lzw_p8.h"

void 			print_charlst(t_charlst *lst) {
	t_charlst 	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp) {
		printf("%c", tmp->c);
		tmp = tmp->next;
		i++;
	}
	printf("\n%d\n", i);
}

void			add_to_charlst(t_charlst **lst, char c) {
	t_charlst	*nouvel_element;
	t_charlst	*tmp;

	nouvel_element = (t_charlst *)malloc(sizeof(t_charlst));
	nouvel_element->c = c;
	nouvel_element->next = NULL;
	if (!(*lst))
	{
		*lst = nouvel_element;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	(*lst)->next = nouvel_element;
	*lst = tmp;
}

void			binaries_to_charlst(t_strlst *binaries, t_charlst **cooked) {
	t_strlst 	*tmp_binaries;
	int 		i, filled;
	char 		c;

	tmp_binaries = binaries;
	i = 0;
	filled = 0;
	c = 0;
	while (tmp_binaries)
	{
		i = 0;
		while (tmp_binaries->str[i])
		{
			if (filled == 8) {
				add_to_charlst(cooked, c);
				filled = 0;
			}
			else {
				if (tmp_binaries->str[i] == '1')
					c = (c << 1) ^ 1;
				if (tmp_binaries->str[i] == '0')
					c = (c << 1);
				filled += 1;
				i++;
			}
		}
		if (filled == 8) {
			add_to_charlst(cooked, c);
			filled = 0;
		}
		tmp_binaries = tmp_binaries->next;
	}
	if (filled < 8) {
		while (filled < 8)
		{
			c = (c << 1);
			filled++;
		}
		add_to_charlst(cooked, c);
	}
	
}
