/*************************************************************************
*File Name : heap.c
*Author : Zheng Qinwen
*CreateDate : Mon 28 May 2018 10:40:16 PM
*Reversion : v1.1
*Description : c files of heap operation
*Copyright : Fiberhome
*OtherInfo : None
*ModifyLog : None
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gttypes.h"
#include "heap.h"
#include "trie.h"

int initHeap(HEAPSQ *HBT, int MS)
{
   if (MS <= 0)// size of heap < 0
   {
        __my_debug("length < 0\n");
        return ERROR;
   }
   HBT->heap = malloc(MS * sizeof(ElemType));//applymemory for heap

   if(NULL == HBT->heap)
   {
       __my_debug("malloc error\n");
       return ERROR;
   }

   HBT->MaxSize = MS;
   HBT->len = 0;
}

void clearHeap(HEAPSQ* HBT)
{
    int i;
    for (i = 0; i < HBT->len; i++)//free all node
    {
        free(HBT->heap[i]);
    }
    if (HBT->heap != NULL)
    {
        free(HBT->heap);
        HBT->len = 0;
        HBT->MaxSize = 0;
    }
}

int emptyHeap(HEAPSQ* HBT)//determine heap is empty
{
    if (HBT->len == 0)
        return 1;
    else
        return 0;

}

int insertHeap(HEAPSQ* HBT, ElemType x)
{
    int i;
    if (HBT->len == HBT->MaxSize)// no memory in heap, expand space
    {
        ElemType *p;
        p = realloc(HBT->heap, 2 * HBT->MaxSize * sizeof(ElemType));
        if (NULL == p)
        {
            __my_debug("no memory in heap\n");
            return ERROR;
        }
        printf("expand memory\n");
        HBT->heap = p;
        HBT->MaxSize = 2 * HBT->MaxSize;
    }
    HBT->heap[HBT->len] = x; //add new data to heap
    HBT->len++; //length add
    i = HBT->len - 1; //i points to the element to be adjusted
    while (i != 0)
    {
        int j = (i - 1) / 2; //j is childs of i
        if (x->val <= HBT->heap[j]->val)
            break;
        HBT->heap[i] = HBT->heap[j]; 
        i = j; 
    }
    HBT->heap[i] = x;

}


ElemType deleteHeap(HEAPSQ* HBT)
{
    ElemType temp, x;
    int i, j;
    if (HBT->len == 0)
    {
        __my_debug("堆已空，退出运行！\n");
        return NULL;
    }
    temp = HBT->heap[0];
    HBT->len--;
    if (HBT->len == 0) 
        return temp;
    x = HBT->heap[HBT->len];// x is the top element 
    i = 0; 
    j = 2 * i + 1;// j is child of i
    while (j <= HBT->len - 1)//adjust element layer by layer
    {
        if (j < HBT->len - 1 && HBT->heap[j]->val < HBT->heap[j+1]->val)
            j++;
        if (x->val >= HBT->heap[j]->val)
            break;
        HBT->heap[i] = HBT->heap[j];
        i = j; 
        j = 2 * i + 1;

    }
    HBT->heap[i] = x; 
    return temp;
}

int expantionHeap(HEAPSQ *HBT, TRIE_NODE *root)
{
    ElemType newnode_1;
    ElemType newnode_2;
    if (HBT->len == 0)
    {
        __my_debug("堆已空，退出运行！\n");
        return ERROR;
    }
    ElemType currnode = deleteHeap(HBT);//currnode is the top element

    //find the indx and bumflag of curr node 
    int bumflag = 0;
    int i, indx, maxindx;
    int maxval = 0;
    for (i = 0; i < MAX_NODE; i++)
    {
        if(1 == currnode->flag[i])
        {
            indx = i;
        }
        bumflag += currnode->flag[i];
    }

    while (1 == bumflag)//loop until there is at least 2 perfix in node
    {
        if(ERROR == transNode(currnode, root))
        {
            __my_debug("error in transenode\n");
            return ERROR;
        }

        for (i = 0; i < MAX_NODE; i++)
        {
            if(1 == currnode->flag[i])
            {
                indx = i;
            }
            bumflag += currnode->flag[i];
        }
    }

    // initial newnode
    newnode_1 = (ElemType)malloc(sizeof(HEAP_NODE));
    if(NULL == newnode_1)
    {
        __my_debug("malloc error\n");
        return ERROR;
    }
    memcpy(newnode_1, currnode, sizeof(HEAP_NODE));
    
    newnode_2 = (ElemType)malloc(sizeof(HEAP_NODE));
    if(NULL == newnode_2)
    {
        __my_debug("malloc error\n");
        return ERROR;
    }
    memcpy(newnode_2, currnode, sizeof(HEAP_NODE));

    //caculate maxnode val and indx
    for (i = 0; i < MAX_NODE; i++)
    {
        if(1 == currnode->flag[i])
        {
            TRIE_NODE *cp;
            if(ERROR == prefixMatchNode(root, currnode->buf[i], &cp))
            {
                __my_debug("match node error\n");
                return ERROR;
            }
            if(cp->mycount > maxval)
            {
                maxval = cp->mycount;
                maxindx = i;
            }
        }
    }

    //assignment for new node
    for (i = 0; i < MAX_NODE; i++)
    {
        //__my_debug("%s\n", newnode_1->buf[i]);
        if (maxindx == i)
        {
            newnode_1->flag[i] = 0;    
        }
        else
        {
            newnode_2->flag[i] = 0;
        }
        newnode_2->val = maxval;
        newnode_1->val = currnode->val - maxval;
    }
    
    //add new node to heap
    insertHeap(HBT, newnode_1);
    insertHeap(HBT, newnode_2);
}

/*
 *  trans node with one prefix to 3 prefix
 * */
int transNode(ElemType x, TRIE_NODE *root)
{
    if(NULL == x)
    {
        __my_debug("null pointer\n");
        return ERROR;
    }

    char hs[MAX_NODE] = {'0', '1', 'x'};

    int bumflag = 0;
    int i, indx;
    for (i = 0; i < MAX_NODE; i++)
    {
        if(1 == x->flag[i])
        {
            indx = i;
        }
        bumflag += x->flag[i];
    }
    assert(1 == bumflag);//make sure there is only one prefix

    char temp[MAX_COL] = {0};
    strcpy(temp, x->buf[indx]);

    int len = strlen(x->buf[indx]);
    temp[len+1] = '\0';

    //add '0' '1' 'x' to prefix
    TRIE_NODE *cp;
    for (i = 0; i < MAX_NODE; i++)
    { 
        temp[len] = hs[i];
        x->flag[i] = 1;
        strcpy(x->buf[i], temp);
        if (NO_MATCH == prefixMatchNode(root, temp, &cp))
        {
            x->flag[i] = 0;
        }    
    }
    return OK;
}

int myHeapClassification(int classnum, TRIE_NODE *root)
{
    int i, j;

    //clear the file
    FILE *fp_clear = fopen("result_myclass.txt", "w"); 
    if(NULL == fp_clear)
    {
        __my_debug("error\n");
        return ERROR;
    }
    fclose(fp_clear);
    
    //open file
    FILE *fp = fopen("result_myclass.txt", "a"); 
    if(NULL == fp)
    {
        __my_debug("error\n");
        return ERROR;
    }

    HEAPSQ heapsq;
    initHeap(&heapsq, 10);
    ElemType x;
   
    //initial first node
    ElemType firstnode = (ElemType)malloc(sizeof(HEAP_NODE));
    firstnode->val = 128;
    firstnode->flag[1] = 1;
    firstnode->flag[0] = 0;
    firstnode->flag[2] = 0;
    strcpy(firstnode->buf[1], "");
    strcpy(firstnode->buf[0], "");
    strcpy(firstnode->buf[2], "");

    insertHeap(&heapsq, firstnode);//insert first node to heap
    
    for (i = 0; i < classnum; i++)//expand node classnum times
    {
        expantionHeap(&heapsq, root);
    }

    for (i = 0; i < classnum; i++)//write ever class to file
    {
        ElemType c = (heapsq.heap)[i];
        if(NULL == c)
        {
            __my_debug("haha\n");
        }
        else
        {
            //__my_debug("val-->%d\n", c->val);
            for (j = 0; j < MAX_NODE; j++)
            {
                if (1 == c->flag[j])
                {
                    TRIE_NODE *cp;
                    char matchbuf[MAX_LINE][MAX_COL];
                    prefixMatchNode(root, c->buf[j], &cp);
                    prefixMatchBuf(cp, c->buf[j], matchbuf);
                    for(int k = 0; k < cp->mycount; k++)
                    {
                        //printf("%s%s\n", c->buf[j], matchbuf[k]);
                        fprintf(fp, "%s%s\n", c->buf[j], matchbuf[k]); 
                    }
                }
            }
            //printf("\n");
            fprintf(fp, "\n");
        
        }
    }
    fclose(fp);
    
    printf("classify success, there are %d class in file, please check result_myclass.txt\n", classnum);

    return OK;
}

void printnode(ElemType x)
{
    int i;
    for (i = 0; i < MAX_NODE; i++)
    {
        __my_debug("%d, ", x->flag[i]);
    }
    
    printf("\n");
    for (i = 0; i < MAX_NODE; i++)
    {
        __my_debug("%s, ", x->buf[i]);
    }

    printf("\n");
    __my_debug("%d, ", x->val);

    printf("\n");
    printf("\n");
}
