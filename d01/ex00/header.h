#ifndef _HEADER_H_
#define _HEADER_H_

#define CS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 !?:;,.$&<>()+*-_="

typedef struct s_list t_list;
struct s_list {
	t_list *next, *prev;
	int c;
};

char *precious(int *text, int size);

#endif /* _HEADER_H_ */
