#include "lzw_p8.h"

int 			need_more_bits(int n_needed, int nb_bits) {
	int 		n;

	n = 1;
	while (nb_bits) {
		n *= 2;
		nb_bits--;
	}
	if (n_needed > n - 1)
		return (1);
	return (0);	
}
