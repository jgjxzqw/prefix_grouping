/*************************************************************************
*File Name : test5.c
*Author : Zheng Qinwen
*CreateDate : Thu 10 May 2018 06:59:24 PM
Reversion : v1.1
Description : 
Copyright : Fiberhome
#include<stdio.h>

OtherInfo : None
ModifyLog : None
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "trie.h"
#include "myfile.h"
#include "gttypes.h"
#include "heap.h"

int main(int argc, char *argv[])
{
    /*initialize buffer for saving file data*/
	char buffer[MAX_LINE][MAX_COL];
    memset(buffer, 0, sizeof(char) * MAX_LINE * MAX_COL);

    /*read file into buffer*/
	if (ERROR == readFile(buffer, "../Sample000111x.txt"))
    {
        __my_debug("read file error\n");
        return -1;
    }

    /*create trie tree, and save buffer data into it*/
    TRIE_NODE* root = createBinaryTree(buffer);
    if (NULL == root)
    {
        __my_debug("create trie tree error\n");
        return -1;
    }

    /*write sorted data into result_sort.txt*/
    if (ERROR == sortAndWriteFile(root, "result_sort.txt"))
    {
        __my_debug("sort and wright file error\n");
        return -1;
    }
    printf("data has been sorted, and saved in sort_result.txt\n");

    //__my_debug("%d\n", TRUE);

    int i;
    /* 
    ElemType a[8];
    for(i = 0; i < 10; i++)
    {
        a[i] = (ElemType)malloc(sizeof(HEAP_NODE));
        memset(a[i], 0, sizeof(HEAP_NODE));
    
        //a[i]->val = 20 -  2 * i;
    }
    
    a[0]->val = 12;

    //for (i = 0; i < 3; i++)
    a[0]->flag[1] = 1;
    a[0]->flag[0] = 0;
    a[0]->flag[2] = 0;
    //a[0]->flag[0] = 1;
    strcpy(a[0]->buf[1], "");
    strcpy(a[0]->buf[0], "0x");
    strcpy(a[0]->buf[2], "11");
    //strcpy(a[0]->buf[0], "00");
    //strcpy(a[0]->buf[0], "01");
    
    //transeNode(b);


    a[1]->val = 3;
    a[2]->val = 1;
    a[3]->val = 124;
    a[4]->val = 25;
    a[5]->val = 153;
    a[6]->val = 465;
    a[7]->val = 13;


    for(i = 0; i < 3; i++)
    {
        __my_debug("%d\n", a[0]->flag[i]); 
        __my_debug("%s\n", a[0]->buf[i]); 
    }
    printf("\n");
    
    transNode(a[0]);
    //expantionHeap();

    for(i = 0; i < 3; i++)
    {
        __my_debug("%d\n", a[0]->flag[i]); 
        __my_debug("%s\n", a[0]->buf[i]); 
    }
    printf("\n");*/


    HEAPSQ b;
    initHeap(&b, 10);
    ElemType x;
    
    //expantionHeap(&b, root);
    
    //ElemType a = 
    ElemType a = (ElemType)malloc(sizeof(HEAP_NODE));
    a->val = 217;

    a->flag[1] = 1;
    a->flag[0] = 0;
    a->flag[2] = 0;
    //a[0]->flag[0] = 1;
    strcpy(a->buf[1], "");
    strcpy(a->buf[0], "");
    strcpy(a->buf[2], "");

    insertHeap(&b, a);

    expantionHeap(&b, root);
    expantionHeap(&b, root);
    expantionHeap(&b, root);
    
    /*for(i = 0; i < 8; i++)
    {
        insertHeap(&b, a[i]);
    }*/

    for(i = 0; i < 4; i++)
    {
        ElemType c = (b.heap)[i];
        if(NULL == c)
        {
            __my_debug("haha\n");
        }
        else
        {
            __my_debug("-->%d\n", c->val);
        }
    }

    
    if (ERROR == myClassification(root, 3))
    {
        __my_debug("classification failed\n");
        return -1;
    }

    /*destroy the trie tree*/
    if (ERROR == trie_destroy(root))
    {
        __my_debug("trie destroy error");
        return -1;
    }

	return 0;
}
