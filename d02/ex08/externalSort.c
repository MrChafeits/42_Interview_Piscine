#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

/* Useless facts:
 * highest score in input file is 100000,
 * distribution of numDigits:
 * 1 - 102
 * 2 - 881
 * 3 - 9006
 * 4 - 89719
 * 5 - 900282
 * 6 - 10                       ack */

static int loadData(FILE *f, int *arr, int size);
static void	quack_swack(int *arr, int len);
static void writeMem(int *mem, int len);
static void mergeFiles(int runNum);

void externalSort(char *scoreFile, char *sortedFile, int ram)
{
	FILE *score;
	int *mem, tmp, runNum=0;

	if (scoreFile == 0 || sortedFile == 0 || ram <= 1)
		return;
	mem = calloc(ram, sizeof(int));
	score = fopen(scoreFile, "r");
	if (mem == 0 || score == 0)
		return;
	do {
		tmp = loadData(score, mem, ram);
		quack_swack(mem, tmp);
		writeMem(mem, tmp);
		if (tmp > 0)
			++runNum;
	} while (tmp == ram);
	fclose(score);
	mergeFiles(runNum);
	free(mem);
}

/* ENTER IF YOU DARE */

static int loadData(FILE *f, int *arr, int size)
{
	int i = 0;

	while(i < size && fscanf(f, "%d", &(arr[i])) > 0) {
		i++;
	}
	return (i);
}

static void	quack_swack(int *arr, int len)
{
	register int i, j, piv, tmp;

	if (len < 2 || arr == 0 || *arr == 0)
		return;

	piv = arr[len / 2];
	for (i = 0, j = len - 1; ; i++, j--) {

		while (arr[i] < piv)
			i++;

		while (arr[j] > piv)
			j--;

		if (i >= j)
			break;

		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	quack_swack(arr, i);
	quack_swack(arr + i, len - i);
}

static void writeMem(int *mem, int len)
{
	int i;
	FILE *fp;
	static unsigned long n = 0;
	char filename[28];

	snprintf(filename, 28, "%010lu.dat", n);
	fp = fopen(filename, "w");
	if (fp == 0) {
		fprintf(stderr, "FATAL ERROR: unable to open file \'%s\'\n", filename);
		exit(1);
	}
	for (i = 0; i < len; i++)
		fprintf(fp, "%d\n", mem[i]);
	fclose(fp);
	++n;
}

#define OUTFILE "grannyScoresSorted.txt"
static void mergeFiles(int runNum)
{
	FILE *fp1, *fp2, *fpOut;
	int tier=0, go1=1, go2=1, orphan=0, s1=0, s2=0;
	int files[1024]={0};
	unsigned long fileNum=0, lowFileNum=0;
	char filename1[28], filename2[28], oldFilename[28];

	files[0] = runNum;
	do {
		do {
			snprintf(filename1, 28, "%010lu.dat", lowFileNum);
			snprintf(filename2, 28, "%010lu.dat", lowFileNum+1);
			fp1 = fopen(filename1, "r");
			fp2 = fopen(filename2, "r");
			fpOut = fopen(OUTFILE, "w");

			if (!fp1) {
				fprintf(stderr, "FATAL ERROR: Unable to open fp1 files for merging\n");
				fprintf(stderr, "filename1(%s)\n", filename1);
				exit(1);
			}

			if (!fp2) {
				orphan = 1;
				strcpy(filename2, oldFilename);
				fp2 = fopen(filename2, "r");

				if (!fp2) {
					fprintf(stderr, "FATAL ERROR: Unable to open fp2 files for merging\n");
					exit(1);
				}
			}

			if (!fpOut) {
				fprintf(stderr, "FATAL ERROR: Unable to open temp.dat to write merged data\n");
				exit (1);
			}

			go1 = fscanf(fp1,"%d",&s1);
			go2 = fscanf(fp2,"%d",&s2);

			while (go1 > 0 && go2 > 0) {

				if (s1 > s2) {
					fprintf(fpOut, "%d\n", s2);
					go2 = fscanf(fp2, "%d", &s2);
				} else {
					fprintf(fpOut, "%d\n", s1);
					go1 = fscanf(fp1, "%d", &s1);
				}
			}

			if (go1 > 0 && go2 < 1) {

				while (go1 > 0) {
					fprintf(fpOut, "%d\n", s1);
					go1 = fscanf(fp1, "%d", &s1);
				}

			} else if (go2 > 0 && go1 < 1) {

				while (go2 > 0) {
					fprintf(fpOut, "%d\n", s2);
					go2 = fscanf(fp2, "%d", &s2);
				}
			}
			fclose(fp1);
			fclose(fp2);
			fclose(fpOut);
			remove(filename1);
			remove(filename2);

			if (orphan) {
				rename(OUTFILE, filename2);
			} else {
				snprintf(filename1, 28, "%010lu.dat", fileNum);
				rename(OUTFILE, filename1);
				strcpy(oldFilename, filename1);
			}
			++fileNum;
			lowFileNum += 2;

		} while (lowFileNum < (unsigned)files[tier]);

		if (orphan) {
			--fileNum;
			orphan = 0;
		}

		files[++tier] = fileNum;
		fileNum = 0;
		lowFileNum = 0;

	} while (files[tier] > 1);

	if (rename("0000000000.dat", OUTFILE) < 0) {
		fputs("FATAL ERROR: unable to rename final output file\n", stderr);
		exit(1);
	}
}
