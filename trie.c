/*************************************************************************
*File Name : trie.c
*Author : Zheng Qinwen
*CreateDate : Thu 10 May 2018 10:40:16 PM
*Reversion : v1.1
*Description : c files of trie tree data structures and related 
				operations
*Copyright : Fiberhome
*OtherInfo : None
*ModifyLog : None
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "gttypes.h"
#include "myfile.h"

/*
 *  hash map for trie tree
 * */
int hstrie(char in)
{
	switch(in)/*hash map '0'=>0 '1'=>1 'x'=>2*/
	{
		case '0': /*key -> '0', value->0*/
			return 0;
		case '1': /*key -> '1', value->1*/
			return 1;
		case 'x': /*key -> 'x', value->2*/
			return 2;
		default: /*input character is not '0', '1'
                        or 'x', wrong*/
			printf("wrong input, please input 0, 1 or x\n");
            //__my_debug("wrong input, 
            //        please input 0, 1, or x");
            return -1;
            break;
	}
}

/*
 *  create trie tree
 * */
TRIE_NODE* trie_create()
{
    /*apply for memory for root node*/
	TRIE_NODE *root = (TRIE_NODE*)malloc(sizeof(TRIE_NODE));
	if(NULL == root)
	{
        __my_debug("aplly memory error");
		return NULL;
	}
	memset(root, 0, sizeof(TRIE_NODE));/*memory clear*/
	return root;
}

/*
 *  insert words into trie tree
 * */
int trie_insert(char *word, TRIE_NODE *root)
{
    /*length of words*/
	int len = strlen(word);
	
    /*current node in loop*/
    TRIE_NODE *cur = root;

	for(int i = 0; i <= len - 1; i++)/*traverse all 
                                       character in words*/
	{
		if(word[i] == '\n')/*break when words end*/
			break;
		int indhash = hstrie(word[i]);/*value after mapping*/
		if(NULL == cur->next[indhash])/*when node is not 
                                        in trie tree*/
		{
			/*apply memory for new node*/
            TRIE_NODE *newNode = (TRIE_NODE*)malloc(sizeof(TRIE_NODE));
			if(NULL == newNode)
            {
                __my_debug("apply memory error");
                return ERROR;
            }
            memset(newNode, 0, sizeof(TRIE_NODE));/*clear memory*/

            /*assign for new node*/
			newNode->val = word[i];
			cur->next[indhash] = newNode;	
		}
		cur = cur->next[indhash];/*pointer jump to next node*/
	}

    /*wrods end, mark new wrods*/
	cur->isword = 1;
	return OK;
}

/*
 *  travers trie tree, sort data, ande save it in buffer
 * */
int trie_travers(char hd_buf[MAX_LINE][MAX_COL], char buf[MAX_COL], 
        TRIE_NODE *node, int indx, int* row)
{
    /*no infomation in node, return*/
    if(NULL == node)
        return OK;

    TRIE_NODE* curr_p = node;/*current pointer*/
    if(node->isword)/*visit the last character in words*/
    {
        strcpy(hd_buf[(*row)], buf);
        (*row)++;
    }
    for(int i = 0; i < MAX_NODE; i++)/*visit all data in trie tree*/
    {
        if(NULL != node->next[i])/*find next node*/
        {
            buf[indx] = node->next[i]->val;
            if(ERROR == trie_travers(hd_buf, 
                        buf, 
                        node->next[i], 
                        indx + 1, 
                        row))
            {
                __my_debug("traverse error");
                return ERROR;
            }
        }
    }
     
    return OK;
}

/*
 *  destroy the trie tree
 * */
int trie_destroy(TRIE_NODE *node, int indx)
{
    /*current node is null, return*/
    if(NULL == node)
        return OK;

    TRIE_NODE* curr_p = node;/*current node*/
    
    int flag = 0;/*flag, that used to mark if 
                   the child node is empty*/
    for(int i = 0; i < MAX_NODE; i++)/*marking*/
    {
        if(NULL != node->next[i])
        {
            flag = 1;
        }
    }
    if(flag)/*if child node is empty, free node*/
    {
        free(curr_p);
        return OK;
    }
    
    for(int i = 0; i < MAX_NODE; i++)/*if child node is not
                                empty, jump into child node*/
    {
        if(NULL != node->next[i])
        {
            if(ERROR == trie_destroy(node->next[i], 
                        indx + 1))
            {
                __my_debug("node destroy error");
                return ERROR;
            }
        }
    } 
    return OK;
}

/*
 *  create trie tree, using buffer data
 * */
TRIE_NODE* createBinaryTree(char buffer[MAX_LINE][MAX_COL])
{
	TRIE_NODE* root = trie_create();/*initialize root node*/
    if(NULL == root)
    {
        __my_debug("trie create error");
        return NULL;
    }

    for(int i = 0; i < MAX_LINE; i++)/*insert all words 
                                       in buffer*/
    {
        
        if(ERROR == trie_insert(buffer[i], 
                    root))
        {
            __my_debug("insert words error");
            return NULL;
        }
    }
    return root;
}

/*
 *  sort data in trie, and write data into file
 * */
int sortAndWriteFile(TRIE_NODE* root, const char *fileName)
{ 
    /*initialize temp buffer*/
    char buf[MAX_COL];
    memset(buf, 0, sizeof(char) * MAX_COL);

    /*initialize 2 dementional buffer, 
             that used to save sorted data in trie tree*/
    char hd_buf[MAX_LINE][MAX_COL];
    memset(hd_buf, 0, sizeof(char) * MAX_LINE * MAX_COL);
   
    /*initialize temp parameter*/
    int a = 0;

    /*save trie tree data into 2 dementional buffer*/
    if(ERROR == trie_travers(hd_buf, 
                buf, 
                root, 
                0, 
                &a))
    {
        __my_debug("travers tree error");
        return ERROR;
    }

    /*write data into file*/
    if(ERROR == writeFile(hd_buf, 
                "sort_result5.txt"))
    {
        __my_debug("write file error");
        return ERROR;
    }
    return OK;
}

/*
 *  prefixmatch for input string in console
 * */
int prefixMatch(TRIE_NODE* root)
{

    printf("please enter prefix string, only 0, 1, x:\n");
    printf("if you want to exit, please enter 'e'\n");
    /*initialize temp buffer*/
    char buf[MAX_COL];
    memset(buf, 0, sizeof(char) * MAX_COL);

    /*initialize 2 dementional buffer, 
             that used to save sorted data in trie tree*/
    char hd_buf[MAX_LINE][MAX_COL];
    memset(hd_buf, 0, sizeof(char) * MAX_LINE * MAX_COL);
 
    /*
     * input 0-1 data in console
     * */
    char input[MAX_COL];
    scanf("%s", input);

    TRIE_NODE* curp = root;/*current node*/
    while(0 != strcmp(input, "e"))/*did not receive the exit instruction
                                        continue to enter*/
    {
        curp = root;
        int i;
        for(i = 0; i <= strlen(input) - 1; i++)/*loop all 
                                    character in input string*/
        {
            int index = hstrie(input[i]);/*hash maping input character*/
            if(-1 == index)/*input wrong number, out of 0, 1, x*/
            {
                printf("please input right 01x number!\n");
                break;
            }
            if(NULL != curp->next[index])/*child node exeists, and equle
                                            to input character, jump into next
                                            node*/
            {
                curp = curp->next[index];
            }
            else/*no matching string in trie tree*/
            {
                printf("no matching string in data\n");
                return OK;
            }
        }
        if(strlen(input) == i)/*enter complete, break*/
        {
            break;
        }
        scanf("%s", input);
    }
    if(0 == strcmp(input, "e"))/*if enter 'e' to exit
                                 , print info*/
    {
        printf("matching exit\n");
        return OK;
    }

    printf("find string\n");
    printf("do you want to print all matching string?y(yes), n(no): \n");

    /*
     * input instructions to determine whether to print string
     * */
    char in[MAX_COL];
    int a = 0;
    scanf("%s", in);
    while(0 != strcmp(in, "e"))/*did not recive quite instruction, continue*/
    {
        /*travers all string with same prefix*/
        if(ERROR == trie_travers(hd_buf, buf, curp, 0, &a))
        {
            __my_debug("travers error");
            return ERROR;
        }

        if(0 == strcmp(in, "y") || 0 == strcmp(in, "yes"))/*print finding string*/
        {
            FILE *fp = fopen("result.txt", "w");
            /*print the string, with same prefix*/
            for(int i = 0; i < a; i++)
            {
                //printf("%s%s\n", input, hd_buf[i]);
                fprintf(fp, "%s%s\n", input, hd_buf[i]);
            }
            fclose(fp);
            break;
        }
        else if(0 == strcmp(in, "n") || 0 == strcmp(in, "no"))/*did not print string, break*/
        {
            break;
        }
        else/*did not enter right info*/
        {
            printf("please input yes or no: \n");
        }
        scanf("%s", in);
    }

    /*
     *  input instruction determine whether write info to file
     * */

    memset(in, 0, MAX_COL);
    printf("do you want to save matching string to a file? y(yes), n(no): \n");
    while(0 != strcmp(in, "e"))/*did not recive quite instruct
                                 , continue*/
    {
        if(0 == strcmp(in, "y") || 0 == strcmp(in, "yes"))/*save data to file, break*/
        {
            FILE *fp = fopen("result.txt", "w");
            if(NULL == fp)
            {
                __my_debug("open file error");
                return ERROR;
            }
            /*print the string, with same prefix*/
            for(int i = 0; i < a; i++)
            {
                fprintf(fp, "%s%s\n", input, hd_buf[i]);
            }
            fclose(fp);
            break;
        }
        else if(0 == strcmp(in, "n") || 0 == strcmp(in, "no"))/*did not save, break*/
        {
            break;
        }
        else/*did not enter right instruction*/
        {
            printf("please input yes or no: \n");
        }
        scanf("%s", in);
    }

    printf("matching complete\n");
    return OK;

}