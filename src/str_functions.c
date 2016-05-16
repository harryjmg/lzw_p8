#include "lzw_p8.h"

char			*string_and_char(char *mot, char lettre)
{
	char		*nouveau_mot;

	nouveau_mot = (char *)malloc(sizeof(char) * (strlen(mot) + 2));
	nouveau_mot = strcpy(nouveau_mot, mot);
	nouveau_mot[strlen(mot)] = lettre;
	nouveau_mot[strlen(mot) + 1] = 0;
	return (nouveau_mot);
}

void			revive_word(char *mot, char c)
{
	char		*nouveau_mot;

	nouveau_mot = (char *)malloc(sizeof(char) * 2);
	nouveau_mot[0] = c;
	nouveau_mot[1] = 0;
	mot = strdup(nouveau_mot);
}


char 			*char_to_string(char c)
{
	char 		*string;

	string = (char *)malloc(sizeof(char) * 2);
	string[0] = c;
	string[1] = 0;
	return (string);
}
