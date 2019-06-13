#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int main(int ac, char **av)
{
	struct s_criminal **criminals;
	struct s_info     *info;
	struct s_criminal **potentialCriminals;

	if (ac != 2) {
		printf("usage: %s description\n", av[0]);
		return (EXIT_FAILURE);
	}
	criminals = getCriminals("criminals.txt");
	potentialCriminals = NULL;
	info = NULL;

	/*-------------------
	launch your test here
	--------------------*/

	sortCriminals(criminals);
	info = getInfo(av[1]);
	/* fprintf(stderr, "av[1](%s)\n", av[1]); */
	/* fprintf(stderr, "info (%d%d%d%d%d%d%d)\n", */
	/* 		info->gender, */
	/* 		info->height, */
	/* 		info->hairColor, */
	/* 		info->eyeColor, */
	/* 		info->glasses, */
	/* 		info->tattoo, */
	/* 		info->piercing); */
	potentialCriminals = findPotentialCriminals(criminals, info);
	if (potentialCriminals)
		printCriminals(potentialCriminals);
	else
		puts("could not find match");

	return (0);
}



// Function used for the test
// Don't go further :)

struct s_criminal **getCriminals(char *filename) {
	FILE				*f;
	struct s_criminal	**criminals;
	size_t 				linecap = 0;
	ssize_t 			linelen;
	int					i, size, description;
	char				*name = NULL;

	if (!(f = fopen(filename, "r"))) {
		printf("Couldn't find %s\n", filename);
		exit(1);
	}
	fscanf(f, "%d\n", &size);
	if (!(criminals = (struct s_criminal **)malloc(sizeof(struct s_criminal *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size && fscanf(f, "%d ", &description) > 0 && (linelen = getline(&name, &linecap, f)) > 0) {
		name[linelen - 1] = 0;
		if (!(criminals[i] = (struct s_criminal *)malloc(sizeof(struct s_criminal))))
			return (NULL);
		criminals[i]->name = name;
		criminals[i]->description = description;
		name = NULL;
		i++;
	}
	criminals[i] = NULL;
	return (criminals);
}

void printCriminals(struct s_criminal **criminals) {
	for (int i = 0; criminals[i]; i++) {
		printf("%d %s\n", criminals[i]->description, criminals[i]->name);
	}
}

struct s_info *getInfo(char *description) {
	int *info, tmp, i;

	if(!(info = malloc(sizeof(struct s_info))))
		return (NULL);
	bzero(info, sizeof(struct s_info));
	tmp = atoi(description);
	for (i = 6; i >= 0; i--) {
		info[i] = (tmp % 10);
		tmp /= 10;
	}
	return ((struct s_info *)info);
}
