#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

#define CTOA(c) (((c) & 0x1f) - 1)

clock_t time_start=0, time_stop=0;
bool debug = 1;

int getmax(int arr[256])
{
    register int i, max = 0, idx = 0;

    for (i = 0; i < 256; i++) {
        if (arr[i] > max) {
            max = arr[i];
            idx = i;
        }
    }
    return idx;
}

/*
Common pairs:
TH, EA, OF, TO, IN, IT, IS, BE, AS, AT, SO, WE, HE, BY, OR, ON, DO, IF, ME, MY, UP

Common repeated pairs:
SS, EE, TT, FF, LL, MM, OO

Common triplets:
THE, EST, FOR, AND, HIS, ENT, THA

           abcdefghijklmnopqrstuvwxyz
text1.txt: zafjnpogqbktwyhcrxviumsedl
text2.txt: jzmupogbteyhcqlkdvifsraxnw
text3.txt: bqaiflsrdphcxuogywjzmktenv
*/

typedef struct s_freq t_freq;
struct s_freq {
    int c;
    double f;
};

static t_freq freq[26] = {
    {.c='e', .f=12.702},
    {.c='t', .f=9.056},
    {.c='a', .f=8.167},
    {.c='o', .f=7.507},
    {.c='i', .f=6.966},
    {.c='n', .f=6.749},
    {.c='s', .f=6.327},
    {.c='h', .f=6.094},
    {.c='r', .f=5.987},
    {.c='d', .f=4.253},
    {.c='l', .f=4.025},
    {.c='c', .f=2.782},
    {.c='u', .f=2.758},
    {.c='m', .f=2.406},
    {.c='w', .f=2.360},
    {.c='f', .f=2.228},
    {.c='g', .f=2.015},
    {.c='y', .f=1.974},
    {.c='p', .f=1.929},
    {.c='b', .f=1.492},
    {.c='v', .f=0.978},
    {.c='k', .f=0.772},
    {.c='j', .f=0.153},
    {.c='x', .f=0.150},
    {.c='q', .f=0.095},
    {.c='z', .f=0.074}
};

int strpatcmp(char *s1, char *s2)
{
    int arr[26] = {0};
    int i,j,h, l1=strlen(s1), l2=strlen(s2);
    int a1[l1], a2[l2];

    for (i = j = h = 0; i < l1; i++) {
        j = CTOA(s1[i]);
        if (arr[j] == 0)
            arr[j] = ++h;
        a1[i] = arr[j];
    }
    for (i = 0; i < 26; i++)
        arr[i] = 0;
    for (i = j = h = 0; i < l2; i++) {
        j = CTOA(s2[i]);
        if (arr[j] == 0)
            arr[j] = ++h;
        a2[i] = arr[j];
    }
    for (i = 0; i < l1 && i < l2; i++) {
        if (a1[i] != a2[i])
            return a1[i] - a2[i];
    }
    return 0;
}

int strocc(char *str, int c)
{
    register int ret;

    for (ret = 0; *str; str++)
        if (*str == c)
            ret++;
    return ret;
}
static char *neverForget_CipherBruteForce(char *words, char **dictionary);

static char *neverForgetFrequencyAnalysis(char *words, char **dictionary)
{
    t_freq cipher[26] = {{0,0}};
    int count[26] = {0};
    int decrypt[26] = {0};
    double fr, tmp;
    int i, j, k, wordlen, numletters;

    if (words == 0 || dictionary == 0 || *dictionary == 0)
        return 0;
    wordlen = strlen(words);
    numletters = 0;
    for (i = 0; i < wordlen; i++) {
        if (words[i] >= 'a' && words[i] <= 'z') {
            numletters++;
            count[CTOA(words[i])]++;
        }
    }
    for (i = 0; i < 26; i++) {
        cipher[i].c = i + 'a';
        cipher[i].f = (((double)count[i]) / ((double)numletters)) * 100.0;
        printf("cipher[%2d] = {.c=\'%c\', .f=%3.4f},\n", i, cipher[i].c, cipher[i].f);
    }
    for (i = 0; i < 26; i++) {
        //build cipher alphabet
        k = 0;
        fr = FLT_MAX;
        tmp = 0.0;
        for (j = 0; j < 26; j++) {
            tmp = fabs(freq[j].f - cipher[i].f);
            if (tmp <= fr) {
                fr = tmp;
                k = j;
            }
        }
        if (fr <= 1.5 || cipher[i].f > 12.0) {
            decrypt[i] = k + 'a';
        }
    }
    for (i = 0; i < wordlen; i++) {
        if (decrypt[CTOA(words[i])] != 0 && words[i] != ' ')
            words[i] = decrypt[CTOA(words[i])];
    }
    return words;
}

char *neverForget(char *words, char **dictionary)
{
    if (0)
        return neverForgetFrequencyAnalysis(words, dictionary);
    else if (0)
        return neverForget_CipherBruteForce(neverForgetFrequencyAnalysis(words, dictionary), dictionary);
    else
        return neverForget_CipherBruteForce(words, dictionary);
}

static char *neverForget_CipherBruteForce(char *words, char **dictionary)
{
    int cipher[256] = {0};
    (void)freq;
    char *tofree, *msg, *token, **split;
    int i, j, k, size, wdc, wordlen, toklen;

    if (words == 0 || dictionary == 0 || *dictionary == 0)
        return 0;
    size = i = strlen(words);
    j = strspn(words, " abcdefghijklmnopqrstuvwxyz");
    debug ? printf("i(%d) j(%d)\n", i, j) : 0;
    if (j != i)
        return 0;
    tofree = msg = strdup(words); assert(msg != NULL);
    wdc = strocc(msg, ' ') + 1;
    split = calloc(wdc + 1, sizeof(*split)); assert(split != NULL);
    j = 0;
    while ((token = strsep(&msg, " ")) != NULL) {
        split[j++] = strdup(token);
    }
    token = 0;
    int dicks[j][2];
    for (i = 0; i < wdc + 1; i++) {
        dicks[i][0] = 0;
        dicks[i][1] = 0;
    }
    free(tofree);
    int blabbo;
    debug ? puts("Begin main loop") : 0;
    time_start = clock();
    while (1) {
        for (i = 0; i < wdc; i++) {
            wordlen = strlen(split[i]);
            blabbo = 0;
            for (j = 0; dictionary[j] != 0; j++) {
                if (dicks[i][1] == 1)
                    break;
                toklen = strlen(dictionary[j]);
                if (wordlen == toklen && strpatcmp(split[i], dictionary[j]) == 0) {
                    blabbo++;
                    dicks[i][0] = j;
                }
            }
            if (dicks[i][1] != 1) {
                dicks[i][1] = blabbo;
            }
            if (blabbo == 1) {
                debug ? printf("i(%d) blabbo(%d)\n", i, blabbo) : 0;
                token = dictionary[dicks[i][0]];
                for (j = 0; token[j] != 0; j++) {
                    if (cipher[(int)token[j]] == 0) {
                        debug ? printf("empty slot in cipher[%d]\n", token[j]) : 0;
                        cipher[(int)token[j]] = split[i][j];
                        debug ? printf("cipher[token[%d](%c)](%c) = split[%d][%d](%c)\n",j,token[j],cipher[(int)token[j]],i,j,split[i][j]) : 0;
                        split[i][j] = token[j];
                    } else if (cipher[(int)token[j]] != split[i][j]) {
                        if (debug) {
                            printf("cipher[token[%d](%c)](%c) != split[%d][%d](%c)\ncipher(",j,token[j],cipher[(int)token[j]],i,j,split[i][j]);
                            for (k = 'a'; k <= 'z'; k++)
                                printf("%s%c", k=='a'?"":",", cipher[k]==0?'0':cipher[k]);
                            printf(")\ni(%d) j(%d) token(%s)\n", i, j, token+j);
                        }
                    } else {
                        debug ? printf("matched slot in cipher[%d](%c)\n", token[j], cipher[(int)token[j]]) : 0;
                        split[i][j] = token[j];
                    }
                }
                debug ? printf("split[%d](%s)\n", i, split[i]) : 0;
            }
        }
        for (i = 0; i < wdc; i++) {
            debug ? printf("split[%d](%s) --> ", i, split[i]) : 0;
            for (j = 0; split[i][j] != 0; j++) {
                if (cipher[(int)split[i][j]] != 0)
                    split[i][j] = cipher[(int)split[i][j]];
            }
            debug ? printf("(%s)\n", split[i]) : 0;
        }
        for (i = 0; i < wdc + 1; i++) {
            if (dicks[i][1] != 1) {
                /* printf("stop condition not met: dicks[%d][1](%d)\n", i, dicks[i][1]); */
                break;
            }
            debug ? printf("dicks[%d][1](%4d) --> split[%d](%s)\n", i,dicks[i][1],i,split[i]) : 0;
        }
        if (wdc == i)
            break;
        time_stop = clock();
        if (((double)(time_stop-time_start)/CLOCKS_PER_SEC) >= 4.0) {
            printf("failsafe time out reached. Current progress on cipher:\n");
            for (i = 'a'; i <= 'z'; i++)
                printf("cipher[\'%c\'] = \'%c\'\n",i,cipher[i]);
            break;
        }
    }
    char *ret = calloc(strlen(words) + 1, sizeof(char)); assert(ret != NULL);
    for (i = j = 0; i < wdc; i++) {
        strcat(ret, split[i]);
        j += strlen(split[i]) + 1;
        ret[j] = ' ';
        ret[j+1] = 0;
    }
    ret[strlen(words)+1] = 0;
    fputs("Done\n", stdout);
    /* Get frequency of each character in the message */
    return ret;
}
