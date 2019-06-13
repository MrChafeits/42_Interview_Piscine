#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

#define MAXLEN 1024

typedef struct s_player t_player;

void sortarr(t_player **arr);
int numWidth(int n);
int length(t_player **arr);
int nameWidth(t_player **arr);
int scoreWidth(t_player **arr);
int is_sorted(t_player **arr);

void delet(t_player **arr)
{
	register int i;

	if (arr == 0 || *arr == 0)
		return;
	for (i = 0; arr[i] != 0; i++)
		free(arr[i]);
	free(arr);
}

int playercmp(const void *p1, const void *p2)
{
	return (*(t_player**)p2)->score - (*(t_player**)p1)->score;
}

int main(void)
{
	t_player **players = 0;
#if 1
	//if param == 0, the length of the list will be random between 1 and 1.000
	/* players = genRandomPlayers(10000); */
	players = genRandomPlayers(100);

	/*-------------------
	launch your test here
	--------------------*/
	printf("length(%d)\n", length(players));
	printf("is_sorted(%d)\n", is_sorted(players));
	/* printPlayers(players); */

	puts("doing the quick sort...");
	quickSort(players);
	printf("is_sorted(%d)\n", is_sorted(players));
	/* printPlayers(players); */
#else
	clock_t start = 0, end = 0;
	int TESTSIZE = MAXLEN;
	printf("length(%d)\n", TESTSIZE);
	delet(players);
	players = genRandomPlayers(TESTSIZE);
	/* printPlayers(players); */
	puts("stdlib qsort...");
	start = clock();
	qsort(players, TESTSIZE, sizeof(*players), playercmp);
	end = clock();
	printf("is_sorted(%d) cpu_ticks(%lu)\n", is_sorted(players), end-start);
	/* printPlayers(players); */

	puts("");
	/* delet(players); */
	/* players = genRandomPlayers(TESTSIZE); */
	/* printPlayers(players); */
	puts("doing the quickSort...");
	start = clock();
	quickSort(players);
	end = clock();
	printf("is_sorted(%d) cpu_ticks(%lu)\n", is_sorted(players), end-start);
	/* printPlayers(players); */

	puts("");
	/* delet(players); */
	/* players = genRandomPlayers(TESTSIZE); */
	/* printPlayers(players); */
	puts("sortarr...");
	start = clock();
	sortarr(players);
	end = clock();
	printf("is_sorted(%d) cpu_ticks(%lu)\n", is_sorted(players), end-start);
	/* printPlayers(players); */
#endif
	return (0);
}

int is_sorted(t_player **arr)
{
	register int i;

	for (i = 1; arr[i] != 0; i++)
		if (arr[i-1]->score < arr[i]->score)
			return 0;
	return 1;
}

int numWidth(int n)
{
	register int ret, i;

	for (i = ret = 1; i < n; i *= 10, ret++);
	return ret;
}

int scoreWidth(t_player **arr)
{
	register int ret, tmp, i;

	for (ret = tmp =i = 0; arr[i] != 0; i++) {
		tmp = numWidth(arr[i]->score);
		ret = (ret < tmp ? tmp : ret);
	}
	return ret;
}

int nameWidth(t_player **arr)
{
	register int ret, tmp, i;

	for (ret = tmp = i = 0; arr[i] != 0; i++) {
		tmp = strlen(arr[i]->name);
		ret = (tmp > ret ? tmp : ret);
	}
	return ret;
}

int length(t_player **arr)
{
	register int i;

	for (i = 0; arr[i] != 0; i++);
	return i;
}

// Function used for the test
// Don't go further :)

void printPlayers(struct s_player **players)
{
	int fw1, fw2, fw3;

	fw1 = numWidth(length(players));
	fw2 = nameWidth(players);
	fw3 = scoreWidth(players);
	printf("⭐  LEADER BOARD ⭐ \n");
	for (int i = 0; players[i]; i++) {
		printf("%*d: %-*s with %*d\n", fw1,i + 1, fw2,players[i]->name, fw3,players[i]->score);
	}
}

struct s_player **genRandomPlayers(int n){
	struct s_player **players;
	char *names[] = { "Beatriz Leroy", "Fernando Fradin", "Claud Lannoy", "Heriberto Franceschi", "Joleen Olsen", "Zula Inesta", "Keturah Bidault", "Helaine Weibel", "Elba Corre", "Terisa Uberti", "Yoshie Taupin", "Hannah Hamza", "Enid Aubree", "Kimberlie Claudel", "Clora Tisserand", "Sadie Urbanek", "Pearlene Virot", "Monique Napolitano", "Madelene Ibouroi", "Richelle Arnal", "Mathilde Bernard", "Lolita Delamare", "Irina Oberle", "Delila Kayser", "Catrina Iglesias", "Louis Barbara", "Michel Willerval", "Freda Quennesson", "Lilli Quersin", "Marlene Nelson", "Coreen Triquet", "Lyda Gombert", "Cherilyn Zemouri", "Shawnee Kanza", "Pasty Witkowski", "Omar Theron", "Wilhelmina Valles", "Valery Stein", "Angelic Hell", "Bobby Ducrocq", "Holley Gillot", "Samatha Rogier", "Vina Wasser", "Lita Benali", "Jessica Habib", "Clelia Usan", "Marquitta Quetier", "Lynetta Kevin", "Alica Wallerand", "Stephaine Zoro", "Perla Julienne", "Alease Damiens", "Jeannie Erdmann", "Stella Abed", "Iraida Collet", "Josette Wasser", "Pasquale Khoury", "Gudrun Hagege", "Yee Der", "Jae Techer", "Lizbeth Vallon", "Kamilah Garde", "Van Queiroz", "Keena Grimaud", "Corinne Ordonneau", "Candyce Duthoit", "Claris Isard", "Annamaria Pochon", "Isabel Guen", "Misha Odiot", "Natalie Stoll", "Ralph Mike", "Josefa Taha", "Brandon Issert", "Meredith Uhmann", "Lilliana Naas", "Toi Nectoux", "Leeanne Espinasse", "Marcene Montana", "Maxine Lecerf", "Zachery Erdmann", "Nena Jourdan", "Waneta Gerardin", "Penney Moro", "Amelia Karam", "Mei Onfray", "Elodia Cauvin", "Jeanne Exposito", "Ladawn Uzan", "Lorina Farmer", "Rosalyn Westrelin", "Harriet Undostres", "Adrianne Guilloux", "Man Vassal", "Tamesha Soriano", "Logan Zurita", "Kathlyn Eschenbrenner", "Laverna Rousselot", "Manda Dore", "Shelba Gloaguen" };

	srand(time(NULL));
	if (n <= 0 || n > MAXLEN){
		n = rand() % MAXLEN + 1; //generating int between 1 and 1.000
	}
	players = malloc(sizeof(struct s_player *) * (n + 1));
	for (int i = 0; i < n; i++)
	{
		players[i] = createRandomPlayer(names[rand() % 100]);
	}
	players[n] = NULL;
	return (players);
}

struct s_player *createRandomPlayer(char *name){
	struct s_player *player = malloc(sizeof(struct s_player));
	if (player){
		player->name = name;
		usleep(2);
		player->score = (rand() % 10000) / 10 * 10;
	}
	return (player);
}
