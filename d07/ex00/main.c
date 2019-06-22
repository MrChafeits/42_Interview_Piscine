#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int is_sorted(register struct s_art **arts) {
    register int i;

    if (arts == 0 || *arts == 0 || arts[1] == 0)
        return 1;
    for (i = 0; arts[i + 1] != 0; i++)
        if (strcmp(arts[i]->name, arts[i + 1]->name) > 0)
            return 0;
    return 1;
}

int main(void)
{
    struct s_art **arts;
    int n = 0, i;

    arts = getArts(); //parsing the file and put it in an array
    while (arts[n])
        n++;

    /*-------------------
      launch your test here
      --------------------*/
    clock_t start, stop;

    //sort the array
    start = clock();
    heapSort(arts, n);
    stop = clock();
    printf("usr heapSort clocks(%lu) approx_time(%f)\n", stop-start, (double)(stop-start)/CLOCKS_PER_SEC);
    if (is_sorted(arts)) {
        puts("Array is sorted");
    } else {
        puts("Array is not sorted");
    }

    struct s_art **arr = getArts();
    start = clock();
    int ret = heapsort(arr, n, sizeof(*arr), artcmp);
    stop = clock();
    printf("stdlib heapsort(%d) clocks(%lu) approx_time(%f)\n",ret, stop-start, (double)(stop-start)/CLOCKS_PER_SEC);
    if (is_sorted(arts)) {
        puts("Array is sorted");
    } else {
        puts("Array is not sorted");
    }
    if (0) {
        //print sorted array
        for (i = 0; arts[i]; i++) {
            printf("%s => %d\n", arts[i]->name, arts[i]->price);
        }
    }
    for (i = 0; i < n; i++) {
        free(arts[i]->name);
        free(arts[i]);
        free(arr[i]->name);
        free(arr[i]);
    }
    free(arts);
    free(arr);

    return (0);
}



// Function used for the test
// Don't go further :)

#define FILENAME "art.txt"

char	*readFile(void)
{
    char *fcontent = NULL;
    int size = 0;
    FILE *fp;

    if (NULL == (fp = fopen(FILENAME, "r")))
        return (NULL);
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    if (NULL == (fcontent = calloc(sizeof(char) , (size + 1))))
        return (NULL);
    fread(fcontent, 1, size, fp);
    fclose(fp);
    return (fcontent);
}

char	**split(char *str, char *delimiter){
    char **tab;
    int count;
    int a;
    int pos;
    int len_delimiter;
    int len_substring;

    len_delimiter = strlen(delimiter);
    len_substring = 0;
    count = 0;
    //first counting the number of substring
    for (int i = 0; str[i]; i++){
        if (strncmp(str + i, delimiter, len_delimiter) == 0) {
            if (len_substring > 0){
                len_substring = 0;
                count += 1;
            }
            i += len_delimiter - 1;
        } else {
            len_substring += 1;
        }
    }
    if (len_substring > 0){
        count += 1;
    }
    if (NULL == (tab = calloc(sizeof(char *) , (count + 1))))
        return (NULL);
    tab[(a = 0)] = NULL;
    len_substring = 0;
    pos = 0;
    //then get the substring :)
    for (int i = 0; str[i]; i++){
        if (strncmp(str + i, delimiter, len_delimiter) == 0) {
            if (len_substring > 0){
                tab[(a++)] = strndup(str + pos, len_substring);
                len_substring = 0;
            }
            i += len_delimiter - 1;
            pos = i + 1;
        } else {
            len_substring += 1;
        }
    }
    if (len_substring > 0){
        tab[(a++)] = strndup(str + pos, len_substring);
    }
    tab[a] = NULL;
    return (tab);
}

void	getArts_leave(void){
    dprintf(STDERR_FILENO, "failed to load the file.\n");
    exit(0);
}

struct s_art *getArts_createStruct( char *line ){
    struct s_art *piece;
    char **tab;

    if (NULL == (piece = calloc(1, sizeof(struct s_art))))
        return (NULL);
    if (NULL == (tab = split(line, " => ")))
        return (NULL);
    if (tab[0] != NULL)
        piece->name = strdup(tab[0]);
    else
        return (NULL);
    if (tab[1] != NULL)
        piece->price = atoi(tab[1]);
    else
        return (NULL);

    for (int i = 0; tab[i] ; i++){
        free(tab[i]);
    } free(tab);

    return (piece);
}

struct s_art **getArts(void)
{
    char *file;
    struct s_art **art;
    int art_size;
    int	art_index;

    dprintf(STDOUT_FILENO, "loading the file... ");
    if (NULL == (file = readFile()))
        getArts_leave();

    //creating the array
    art_size = 0;
    for (int i = 0; file[i]; i++){
        if (file[i] == '\n')
            art_size += 1;
    }
    if (NULL == (art = calloc(sizeof(struct s_art *) , (art_size + 1))))
        getArts_leave();
    art[(art_index = 0)] = NULL;

    //filling the array
    char **tab = split(file, "\n");
    struct s_art *tmp;
    for(int i = 0; tab[i]; i++){
        tmp = getArts_createStruct(strdup(tab[i]));
        if (tmp)
            art[(art_index++)] = tmp; 
    }
    art[(art_index)] = NULL;

    for (int i = 0; tab[i] ; i++){
        free(tab[i]);
    } free(tab); free(file);

    dprintf(STDOUT_FILENO, "finish!\n");
    return (art);
}
