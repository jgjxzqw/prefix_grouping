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

    int i, j;


    HEAPSQ b;
    initHeap(&b, 10);
    ElemType x;
    
    //ElemType a = 
    ElemType a = (ElemType)malloc(sizeof(HEAP_NODE));
    a->val = 128;

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
    expantionHeap(&b, root);
    
    for(i = 0; i < 5; i++)
    {
        ElemType c = (b.heap)[i];
        if(NULL == c)
        {
            __my_debug("haha\n");
        }
        else
        {
            __my_debug("val-->%d\n", c->val);
            for (j = 0; j < MAX_NODE; j++)
            {
                if (1 == c->flag[j])
                {
                    __my_debug("prefix-->%s\n", c->buf[j]);
                    //printnode(c);
                }
            }
        
        }
    }

    
    if (ERROR == myClassification(root, 2))
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
