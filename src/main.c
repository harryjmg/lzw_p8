/*
**		Projet Compresseur / Decompresseur
**		Algorithme LZW, 2016 May
**		L2 Algorithmie Paris 8, GUEGUEN Harry
**
*/

#include "lzw_p8.h"

static int			usage_exit(char *str) {
	printf("Usage : %s [0:compress, 1:decompress] [data]\n", str);
	return (1);
}

int					main(int ac, char **av)
{
	int				option;

	// ______________ Bad usages _____
	if (ac != 3)
		return usage_exit(av[0]);
	option = atoi(av[1]);
	if (option != 1 && option != 0)
		return usage_exit(av[0]);

	// ______________ Do da job ______
	if (option == 0)
		compress(av[2]);
	else
		decompress(av[2]);
	return (0);
}