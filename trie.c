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
#include <math.h>
#include <assert.h>
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
	if (NULL == root)
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

	for (int i = 0; i <= len - 1; i++)/*traverse all 
                                       character in words*/
	{
		if (word[i] == '\n')/*break when words end*/
        {
            break;
        }	
		int indhash = hstrie(word[i]);/*value after mapping*/
		if (NULL == cur->next[indhash])/*when node is not 
                                        in trie tree*/
		{
			/*apply memory for new node*/
            TRIE_NODE *newNode = (TRIE_NODE*)malloc(sizeof(TRIE_NODE));
			if (NULL == newNode)
            {
                __my_debug("apply memory error");
                return ERROR;
            }
            memset(newNode, 0, sizeof(TRIE_NODE));/*clear memory*/

            /*assign for new node*/
			newNode->val = word[i];
            newNode->mycount = 0;
			cur->next[indhash] = newNode;
		}
        cur->mycount++;
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
    int i;

    /*no infomation in node, return*/
    if (NULL == node)
    {
        return OK;
    }

    TRIE_NODE* curr_p = node;/*current pointer*/
    if (node->isword)/*visit the last character in words*/
    {
        strcpy(hd_buf[(*row)], buf);
        (*row)++;
    }
    for (i = 0; i < MAX_NODE; i++)/*visit all data in trie tree*/
    {
        if (NULL != node->next[i])/*find next node*/
        {
            buf[indx] = node->next[i]->val;
            if (ERROR == trie_travers(hd_buf, 
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
int trie_destroy(TRIE_NODE *node)
{
    /*current node is null, return*/
    if (NULL == node)
    {
        return OK;
    }

    TRIE_NODE* curr_p = node;/*current node*/
    int i;
    int flag = 0;/*flag, that used to mark if 
                   the child node is empty*/
    for (i = 0; i < MAX_NODE; i++)/*marking*/
    {
        if (NULL != node->next[i])
        {
            flag = 1;
        }
    }
    if (flag)/*if child node is empty, free node*/
    {
        free(curr_p);
        return OK;
    }
    
    for (i = 0; i < MAX_NODE; i++)/*if child node is not
                                empty, jump into child node*/
    {
        if (NULL != node->next[i])
        {
            if (ERROR == trie_destroy(node->next[i]))
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
    int i;
	TRIE_NODE* root = trie_create();/*initialize root node*/
    if (NULL == root)
    {
        __my_debug("trie create error");
        return NULL;
    }

    for (i = 0; i < MAX_LINE; i++)/*insert all words 
                                       in buffer*/
    {
        
        if (ERROR == trie_insert(buffer[i], 
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
    if (ERROR == trie_travers(hd_buf, 
                buf, 
                root, 
                0, 
                &a))
    {
        __my_debug("travers tree error");
        return ERROR;
    }

    /*write data into file*/
    if (ERROR == writeFile(hd_buf, 
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
int prefixMatch(_in TRIE_NODE* root, _in char *matchstr
        , _out char matchbuf[MAX_LINE][MAX_COL], _out TRIE_NODE **cp)
{
    int i;
    int a = 0;
    if(NULL != *cp)
    {
        *cp = NULL;
    }

    if (NULL == root)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }

    if (NULL == matchstr)
    {
        __my_debug("input null point\n");
        return ERROR;
    }
   
    memset(matchbuf, 0, sizeof(char) * MAX_LINE * MAX_COL);

    /*initialize temp buffer*/
    char buf[MAX_COL];
    memset(buf, 0, sizeof(char) * MAX_COL);

    /*initialize 2 dementional buffer, 
             that used to save sorted data in trie tree*/
    char hd_buf[MAX_LINE][MAX_COL];
    memset(hd_buf, 0, sizeof(char) * MAX_LINE * MAX_COL);

    TRIE_NODE* curp = root;/*current node*/
    
    for (i = 0; i <= strlen(matchstr) - 1; i++)/*loop all 
                                character in input string*/
    {
        int index = hstrie(matchstr[i]);/*hash maping input character*/
        if (-1 == index)/*input wrong number, out of 0, 1, x*/
        {
            break;
        }
        if (NULL != curp->next[index])/*child node exeists, and equle
                                        to input character, jump into next
                                        node*/
        {
            curp = curp->next[index];
        }
        else/*no matching string in trie tree*/
        {
            printf("%s no matching string in data\n", matchstr);
            return OK;
        }
    }

    *cp = curp;
    
    /*travers all string with same prefix*/
    if (ERROR == trie_travers(hd_buf, buf, curp, 0, &a))
    {
        __my_debug("travers error");
        return ERROR;
    }


    FILE *fp = fopen("result.txt", "a");

    /*print the string, with same prefix*/
    for (i = 0; i < curp->mycount; i++)
    {
        if(NULL == strcpy(matchbuf[i], matchstr))
        {
            __my_debug("strcpy failed\n");
            return ERROR;
        }
        strcat(matchbuf[i], hd_buf[i]); 
        fprintf(fp, "%s\n", matchbuf[i]);
    }

    fprintf(fp, "\n");
    fclose(fp);

    printf("%s matching complete\n", matchstr);
    return OK;
}

int prefixMatchNode(TRIE_NODE *root, char *matchstr
        , TRIE_NODE **cp)
{
    int i;
    int a = 0;
    if(NULL != *cp)
    {
        *cp = NULL;
    }

    if (NULL == root)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }

    if (NULL == matchstr)
    {
        __my_debug("input null point\n");
        return ERROR;
    }

    TRIE_NODE* curp = root;/*current node*/
    
    for (i = 0; i <= strlen(matchstr) - 1; i++)/*loop all 
                                character in input string*/
    {
        int index = hstrie(matchstr[i]);/*hash maping input character*/
        if (-1 == index)/*input wrong number, out of 0, 1, x*/
        {
            break;
        }
        if (NULL != curp->next[index])/*child node exeists, and equle
                                        to input character, jump into next
                                        node*/
        {
            curp = curp->next[index];
        }
        else/*no matching string in trie tree*/
        {
            printf("%s no matching string in data\n", matchstr);
            return NO_MATCH;
        }
    }

    *cp = curp;
}


int prefixMatchBuf(TRIE_NODE *curp
        , char *matchstr
        , char matchbuf[MAX_LINE][MAX_COL])
{
    if(NULL == curp)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }
    if(NULL == matchstr)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }
   
    /*initialize temp buffer*/
    char buf[MAX_COL];
    memset(buf, 0, sizeof(char) * MAX_COL);

    /*initialize 2 dementional buffer, 
             that used to save sorted data in trie tree*/
    char hd_buf[MAX_LINE][MAX_COL];
    memset(hd_buf, 0, sizeof(char) * MAX_LINE * MAX_COL);

    int a = 0;
    int i;

    /*travers all string with same prefix*/
    if (ERROR == trie_travers(hd_buf, buf, curp, 0, &a))
    {
        __my_debug("travers error");
        return ERROR;
    }


    FILE *fp = fopen("result.txt", "a");

    /*print the string, with same prefix*/
    for (i = 0; i < curp->mycount; i++)
    {
        strcpy(matchbuf[i], matchstr);
        strcat(matchbuf[i], hd_buf[i]); 
        fprintf(fp, "%s\n", matchbuf[i]);
    }
   
    fprintf(fp, "\n");
    fclose(fp);

}

/*
 *  classification data and write it into file
 * */
int myClassification(TRIE_NODE* root, unsigned int classnum)
{
    int row = pow(3, classnum);//row of buffer
    int col = classnum;//col of buffer
    int i;

    /*clear the file*/
    FILE *fp = fopen("result.txt", "w");
    if (NULL == fp)
    {
        __my_debug("openfile failed\n");
        return ERROR;
    }
    fclose(fp);

    if (NULL == root)//input null pointer
    {
        __my_debug("input null pointer\n");
        return ERROR;
    }

    char **buffer;//used to save prefix
    char matchbuf[MAX_LINE][MAX_COL];
    TRIE_NODE *cp;
    if (ERROR == convertNum2Bina(&buffer, classnum))//generate a fixed-length prefix
    {
        __my_debug("convert failed\n");
        return ERROR;
    }
    
    for (i = 0; i <= row - 1; i++)
    {
       
        if (NO_MATCH != prefixMatchNode(root, buffer[i], &cp))
        {
            prefixMatchBuf(cp, buffer[i], matchbuf);
            addFile(matchbuf, "tempresult.txt", cp->mycount);

        }
    }

    return OK;
}

/*
 *  convert number to binary
 * */
int convertNum2Bina(char ***buf, int layers)
{
    int i;
    char **in;

    /*input layers must > 0*/
    if (layers <= 0)
    {
        __my_debug("more layer\n");
        return ERROR;
    }

    /*assign the initial 2 dementional array {0, 1, x}*/
    in = (char**)malloc(sizeof(char*) * MAX_NODE);
    if (NULL == in)
    {
        __my_debug("malloc error\n");
        return ERROR;
    }
    for (i = 0; i <= MAX_NODE - 1; i++)
    {
        in[i] = (char*)malloc(sizeof(char) * 1);
    }
    strcpy(in[0], "0");
    strcpy(in[1], "1");
    strcpy(in[2], "x");

    /*return in if input layers = 1*/
    if (1 == layers)
    {
        *buf = in;
    }

    /*extent array*/
    for (i = 1; i < layers; i++)
    {
        myExtent(in, buf, pow(3, i), i);
        in = (*buf);
    }

    return OK;
}

/*
 *  array growth
 * */
int myExtent(char **in, char ***res, int row, int col)
{
    int i, j, k;
    char* hs[MAX_NODE] = {"0", "1", "x"};
    
    if (NULL == in)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }

    *res = (char**)malloc(sizeof(char*) * MAX_NODE * row);
    if(NULL == (*res))
    {
        __my_debug("malloc error\n");
        return ERROR;
    }
    for (i = 0; i <= MAX_NODE * row - 1; i++)
    {
        (*res)[i] = (char*)malloc(sizeof(char) * (col + 1));
        if(NULL == (*res)[i])
        {
            __my_debug("malloc error\n");
            return ERROR;
        }
    }
   
    int len = 0;
    for (i = 0; i <= MAX_NODE - 1; i++)
    {
       for (j = 0; j <= row -1; j++)
       {
            strcpy((*res)[len], in[j]);
            strcat((*res)[len++], hs[i]);
       }
    }

    /*free memory*/
    for(i = 0; i < row; i++)
    {
        free(in[i]);
    }
    free(in);
}
