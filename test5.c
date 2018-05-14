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

int main(int argc, char *argv[])
{
    print_proj_head();
    /*initialize buffer for saving file data*/
	char buffer[MAX_LINE][MAX_COL];
    memset(buffer, 0, sizeof(char) * MAX_LINE * MAX_COL);

    /*read file into buffer*/
	if(ERROR == readFile(buffer, "../Sample000111x.txt"))
    {
        __my_debug("read file error");
    }

    /*create trie tree, and save buffer data into it*/
    TRIE_NODE* root = createBinaryTree(buffer);
    if(NULL == root)
    {
        __my_debug("create trie tree error");
    }

    /*write sorted data into result_sort.txt*/
    if(ERROR == sortAndWriteFile(root, "result_sort.txt"))
    {
        __my_debug("sort and wright file error");
    }
    printf("data has been sorted, and saved in sort_result.txt\n\n");

    /*perform prefix matching*/
    if(ERROR == prefixMatch(root))
    {
        __my_debug("prefix matching error");
    }

    /*destroy the trie tree*/
    
    if(ERROR == trie_destroy(root, 0))
    {
        __my_debug("trie destroy error");
    }

	return 0;
}
