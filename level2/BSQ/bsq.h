#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int    rows;
	int    cols;
	char   empty;
	char   obstacle;
	char   full;
	char **grid;
} t_map;

#endif
