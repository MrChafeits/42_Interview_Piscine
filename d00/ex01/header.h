#ifndef _HEADER_H_
#define _HEADER_H_

typedef struct s_art t_art;
struct s_art {
	char *name;
	int price;
};

void sortArts(t_art **arts);

#endif /* _HEADER_H_ */
