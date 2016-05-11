/*
**		DECOMPRESSEUR LZW
**		dictionnaire de base : table ascii (256 entrees)
**		Auteur : Harry Gueguen
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct 		s_dico
{
	int				index;
	char			*mot;
	struct s_dico 	*next;
}					t_dico;

static void		reinit_mot(char *mot, char c)
{
	char		*nouveau_mot;

	nouveau_mot = (char *)malloc(sizeof(char) * 2);
	nouveau_mot[0] = c;
	nouveau_mot[1] = 0;
	mot = strdup(nouveau_mot);
}

static void		ecrire_code(t_dico *dico, char *mot)
{
	t_dico		*tmp;

	tmp = dico;
	while (dico)
	{
		if (strcmp(dico->mot, mot) == 0)
		{
			printf("_code : %d\n", dico->index);
			return ;
		}
		dico = dico->next;
	}
	return ;
}

static int 		est_dans_dico(t_dico *dico, char *mot)
{
	t_dico 		*tmp;

	tmp = dico;
	while (tmp)
	{
		if (strcmp(tmp->mot, mot) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void		ajouter_au_dico(t_dico **dico, char *mot, int base)
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

static char 	*char_to_string(char c)
{
	char 		*string;

	string = (char *)malloc(sizeof(char) * 2);
	string[0] = c;
	string[1] = 0;
	return (string);
}

static void		init_dico(t_dico **dico)
{
	t_dico		*tmp;
	int 		i;

	i = 0;
	while (i < 256)
	{
		ajouter_au_dico(dico, char_to_string(i), i);
		i++;
	}
}

static char		*mot_et_lettre(char *mot, char lettre)
{
	char		*nouveau_mot;

	nouveau_mot = (char *)malloc(sizeof(char) * (strlen(mot) + 2));
	nouveau_mot = strcpy(nouveau_mot, mot);
	nouveau_mot[strlen(mot)] = lettre;
	nouveau_mot[strlen(mot) + 1] = 0;
	return (nouveau_mot);
}

static void		show_dico(t_dico *dico)
{
	int 		n;

	n = dico->index;
	printf("dico size : %d\n", n);
}

int				main(int ac, char **av)
{
	t_dico		*dico;
	char		*text = "TOBEORNOTTOBEORTOBEORNOT";
	int 		i = 0;
	char		*mot = ""; // Pouvez vous m'expliquer pourquoi mot[] = "" ne fonctionne pas ?

	dico = NULL;
	init_dico(&dico);
	while (text[i] != 0)
 	{
 		if (est_dans_dico(dico, mot_et_lettre(mot, text[i])))
			mot = mot_et_lettre(mot, text[i]);
 		else
 		{
 			ajouter_au_dico(&dico, mot_et_lettre(mot, text[i]), 0);
 			ecrire_code(dico, mot);
 			free(mot);
 			reinit_mot(mot, text[i]);
 		}
 		i++;
 	}
 	ecrire_code(dico, mot);
 	return (0);
}