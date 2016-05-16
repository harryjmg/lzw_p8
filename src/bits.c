#include "lzw_p8.h"

int 			need_more_bits(t_dico *dico, int nb_bits) {
	t_dico		*tmp;
	int			i;
	int 		n;

	tmp = dico;
	i = 0;
	while (tmp){
		tmp = tmp->next;
		i++;
	}
	n = 1;
	while (nb_bits) {
		n *= 2;
		nb_bits--;
	}
	if (i == n - 1)
		return (1);
	return (0);	
}
