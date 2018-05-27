#ifndef _GTTYPES_H_
#define _GTTYPES_H_

#define MAX_NODE 3 /*max number of child node*/
#define MAX_COL 91 /*max colum in input file*/
#define MAX_LINE 128 /*max row in inout file*/

#define OK 1
#define ERROR 0

#define NO_MATCH 2

//#define TRUE 1
//#define FALSE 0

#define BOOL int
#define TRUE 1
#define FALSE 0

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

/*
 *  define heap node
 * */
typedef struct tagHEAP_NODE{
    int flag[MAX_NODE];
    char buf[MAX_NODE][MAX_COL];
    int val;
}HEAP_NODE;

typedef HEAP_NODE* ElemType;

typedef struct tagHEAPSQ //定义堆的顺序存储类型
{
    ElemType* heap; //定义指向动态数组空间的指针
    int len; //定义保存堆长度的变量,即数组长度，数组下标从0开始
    int MaxSize;    //用于保存初始化时所给的动态数组空间的大小
}HEAPSQ;


#endif


