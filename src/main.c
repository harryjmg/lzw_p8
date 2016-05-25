/*
**		Projet Compresseur / Decompresseur
**		Algorithme LZW, 2016 May
**		L2 Algorithmie Paris 8, GUEGUEN Harry
**
*/

#include "lzw_p8.h"

static int			usage_exit(char *str) {
	printf("Usage : %s [0:compress, 1:decompress] [src_file] [dest_file]\n", str);
	return (-1);
}

int					main(int ac, char **av)
{
	if (ac != 4)
		return usage_exit(av[0]);
	if (av[1][0] == '0')
		compress(av[2], av[3]);
	else if (av[1][0] == '1')
		decompress(av[2], av[3]);
	else
		return usage_exit(av[0]);
	return (0);
}