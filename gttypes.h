#ifndef _GTTYPES_H_
#define _GTTYPES_H_

#define MAX_NODE 3 /*max number of child node*/
#define MAX_COL 91 /*max colum in input file*/
#define MAX_LINE 128 /*max row in inout file*/

#define OK 1
#define ERROR 0

#define NO_MATCH 2

#define YES 1
#define NO 0

#define _in
#define _out

#define __my_debug(FORMAT, ARG...) \
    printf("%s:%d %s: " FORMAT, __FILE__, __LINE__, __FUNCTION__, ##ARG)

/*
 * Defining a binary tree node
 * val - node value
 *  isword - mark last node in wrods
 *  next[] - saving child node
 * */
typedef struct tagTRIE_NODE{
	char val;
	int isword;
    int mycount;
	struct tagTRIE_NODE *next[MAX_NODE];
}TRIE_NODE;

#endif


