#include "lzw_p8.h"

int 			is_entry_in_dico(t_dico *dico, int c) {
	t_dico 		*tmp;

	tmp = dico->next;
	while (tmp) {
		if (tmp->index == c)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char 			*get_word_in_dico(t_dico *dico, int c) {
	t_dico 		*tmp;

	tmp = dico->next;
	while (tmp) {
		if (tmp->index == c) {
			//printf("%d %s\n", c, tmp->mot);
			return (strdup(tmp->mot));
		}
			
		tmp = tmp->next;
	}
	return (NULL);
}

void			init_dico(t_dico **dico)
{
	int 		i;

	i = 0;
	while (i < 256)
	{
		add_to_dico(dico, char_to_string(i), i);
		i++;
	}
}

int 			is_in_dico(t_dico *dico, char *mot)
{
	t_dico 		*tmp;

	tmp = dico;
	while (tmp)
	{
		if (strcmp(tmp->mot, mot) == 0)
			return (tmp->index);
		tmp = tmp->next;
	}
	return (0);
}

void			add_to_dico(t_dico **dico, char *mot, int base)
{
	t_dico 		*nouvel_element;
	t_dico		*tmp;
	int 		i;

	nouvel_element = (t_dico *)malloc(sizeof(t_dico));
	if (base != 0)
	{
		nouvel_element->mot = (char *)malloc(sizeof(char) * 2);
		nouvel_element->mot[0] = base;
		nouvel_element->mot[1] = 0;
	}
	else
		nouvel_element->mot = strdup(mot);
	nouvel_element->index = 1;
	nouvel_element->next = NULL;

	if (!(*dico))
	{
		*dico = nouvel_element;
		return ;
	}
	tmp = *dico;
	i = 1;
	while ((*dico)->next != NULL){
		*dico = (*dico)->next;
		i++;
	}
	nouvel_element->index = i;
	(*dico)->next = nouvel_element;
	tmp->index = i;
	*dico = tmp;
}