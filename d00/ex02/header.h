#ifndef _HEADER_H_
#define _HEADER_H_

typedef struct s_art t_art;
struct s_art {
	char *name;
	int price;
};

int searchPrice(t_art **arts, int n, char *name);

#endif /* _HEADER_H_ */
