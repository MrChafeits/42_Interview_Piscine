#include <string.h>
#include <unistd.h>
#include "header.h"

/* #define HONKPRIME 16777619 */

int sumstr(char *str, int start, int end)
{
	int i, total = 0;

	for (i = start; i <= end; i++)
		total += str[i];
	return total;
}
int howManyJesus(char *bible, char *jesus)
{
	int total = 0;
	int jlen = strlen(jesus);
	int jsum = sumstr(jesus, 0, jlen - 1);
	int cur = 0, l = 0, r = 0;

	while (bible[r] && r < jlen) {
		cur += bible[r];
		r++;
	}
	for (r = r - 1; bible[r] != 0;) {
		if (jsum == cur) {
			if (strncmp(jesus, bible + l, jlen) == 0)
				total++;
			l++;
			r++;
		} else {
			l++;
			r++;
			cur -= bible[l-1];
			cur += bible[r];
		}
	}
	return total;
}
/* #define HONKPRIME 101 */
/* int howManyJesus(char *bible, char *jesus) */
/* { */
/* 	int hpat, hstr, h; */
/* 	int i, j; */
/* 	int bl, jl, total; */

/* 	if (bible == 0 || *bible == 0 || jesus == 0 || *jesus == 0) */
/* 		return -1; */
/* 	bl = strlen(bible); */
/* 	jl = strlen(jesus); */
/* 	total = 0; */
/* 	h = 1; */
/* 	for (i = 0; i < jl - 1; i++) */
/* 		h = (h * 256) % HONKPRIME; */
/* 	for (i = 0; i < jl; i++) { */
/* 		hpat = (256 * hpat + jesus[i]) % HONKPRIME; */
/* 		hstr = (256 * hstr + bible[i]) % HONKPRIME; */
/* 	} */
/* 	for (i = 0; i <= bl - jl; i++) { */
/* 		if (hpat == hstr) { */
/* 			for (j = 0; j < jl; j++) { */
/* 				if (bible[i+j] != jesus[j]) */
/* 					break; */
/* 			} */
/* 			if (j == jl) */
/* 				total++; */
/* 		} */
/* 		if (i < bl - jl) { */
/* 			hstr = (256 * (hstr - bible[i] * h) + bible[i + jl]) % HONKPRIME; */
/* 			if (hstr < 0) */
/* 				hstr = hstr + HONKPRIME; */
/* 		} */
/* 	} */
/* 	return total; */
/* } */

/* #define FNV_OFFSET 14695981039346656037ULL */
/* #define FNV_PRIME 1099511628211ULL */

/* size_t	hash(char *input, int start, int end) */
/* { */
/* 	register size_t i; */
/* 	register int j; */

/* 	for (i = FNV_OFFSET, j = start; j < end; j++) { */
/* 		i *= FNV_PRIME; */
/* 		i ^= input[j]; */
/* 	} */
/* 	return i; */
/* } */

/* int howManyJesus(char *bible, char *jesus) */
/* { */
/* 	size_t hpat, hstr; */
/* 	int i, j, bl, jl, total; */

/* 	total = 0; */
/* 	bl = strlen(bible); */
/* 	jl = strlen(jesus); */
/* 	hpat = hash(jesus, 0, jl); */
/* 	hstr = hash(bible, 0, jl); */
/* 	for (i = 0; i <= bl - jl; i++) { */
/* 		if (hpat == hstr) { */
/* 			for (j = 0; j < jl; j++) { */
/* 				if (bible[i+j] != jesus[j]) */
/* 					break; */
/* 			} */
/* 			if (j == jl) */
/* 				total++; */
/* 		} */
/* 		if (i < bl - jl) { */
/* 			hstr = (256 * (hstr - bible[i] * hpat) + bible[i+jl]) % FNV_PRIME; */
/* 	} */
/* } */
