#ifndef GTTYPES_H
#define GTTYPES_H

#define MAX_NODE 3 /*max number of child node*/
#define MAX_COL 91 /*max colum in input file*/
#define MAX_LINE 128 /*max row in inout file*/

#define OK 1
#define ERROR 0

#define YES 1
#define NO 0

#define __my_debug(FORMAT, ARG...) \
    printf("%s:%d %s: " FORMAT, __FILE__, __LINE__, __FUNCTION__, ##ARG)

#define print_proj_head() \
        printf("\n\n/******************************************************\n\
/*====================================================\n\
/*this is a prefix matching project, that support \n\
* saves the sorted data to fixed file and supports\n\
* interactive prefix matching at the console.\n\
/* let us begin:======================================\n\n\n\n");


/*
 * Defining a binary tree node
 * val - node value
 *  isword - mark last node in wrods
 *  next[] - saving child node
 * */
typedef struct tagTRIE_NODE{
	char val;
	int isword;
	struct tagTRIE_NODE *next[MAX_NODE];
}TRIE_NODE;

#endif


