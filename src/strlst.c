#include "lzw_p8.h"

void			fill_str_with_binary(char **str, int binary, int nb_bit)
{
	int 		mask;
	int 		i;

	i = 0;
	while (nb_bit > 0)
	{
		mask = 0;
		mask = (mask ^ 1) << (nb_bit - 1);
		if (mask & binary)
			(*str)[i] = '1';
		else
			(*str)[i] = '0';
		nb_bit--;
		i++;
	}
}

static void		fill_str(char **str, int nb_bit) {
	int 		i;

	i = 0;
	while (nb_bit > 0)
	{
		(*str)[i] = '1';
		nb_bit--;
		i++;
	}
}

void 			add_to_strlst(t_strlst **lst, int word_index, int nb_bit)
{
	t_strlst	*nouvel_element;
	t_strlst	*tmp;

	nouvel_element = (t_strlst *)malloc(sizeof(t_strlst));
	nouvel_element->str = (char *)malloc(sizeof(char) * (nb_bit + 1));
	if (word_index == -1)
		fill_str(&(nouvel_element->str), nb_bit);
	else
		fill_str_with_binary(&(nouvel_element->str), word_index, nb_bit);
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

void 			print_strlst(t_strlst *list) {
	t_strlst 	*tmp;

	tmp = list;
	while (tmp) {
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}