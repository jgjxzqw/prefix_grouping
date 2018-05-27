#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gttypes.h"
#include "heap.h"
#include "trie.h"

int initHeap(HEAPSQ *HBT, int MS)
{
   if (MS <= 0)
   {
        __my_debug("length < 0\n");
        return ERROR;
   }
   HBT->heap = malloc(MS * sizeof(ElemType));

   if(NULL == HBT->heap)
   {
       __my_debug("malloc error\n");
       return ERROR;
   }

   HBT->MaxSize = MS;
   HBT->len = 0;
}

void clearHeap(HEAPSQ* HBT)// mem leak
{
    if (HBT->heap != NULL)
    {
        free(HBT->heap);
        HBT->len = 0;
        HBT->MaxSize = 0;

    }
}

int emptyHeap(HEAPSQ* HBT)
{
    if (HBT->len == 0)
        return 1;
    else
        return 0;

}

int insertHeap(HEAPSQ* HBT, ElemType x)
{
    int i;
    if (HBT->len == HBT->MaxSize)
    {
        ElemType *p;
        p = realloc(HBT->heap, 2 * HBT->MaxSize * sizeof(ElemType));
        if (NULL == p)
        {
            __my_debug("存储空间用完！\n");
            return ERROR;
        }
        printf("存储空间已扩展为原来的2倍！\n");
        HBT->heap = p;
        HBT->MaxSize = 2 * HBT->MaxSize;

    }
    HBT->heap[HBT->len] = x; //向堆尾添加新元素
    HBT->len++; //堆长度加1
    i = HBT->len - 1; //i指向待调整元素的位置，即其数组下标，初始指向新元素所在的堆尾位置
    while (i != 0)
    {
        int j = (i - 1) / 2; //j指向下标为i的元素的双亲
        if (x->val <= HBT->heap[j]->val)
            break;
        HBT->heap[i] = HBT->heap[j]; //将双亲元素下移到待调整元素的位置
        i = j; //使待调整位置变为其双亲位置，进行下一次循环
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
    if (HBT->len == 0) //若删除操作后堆为空则返回
        return temp;
    x = HBT->heap[HBT->len]; //将待调整的原堆尾元素暂存x中，以便放入最终位置
    __my_debug("%d\n, %d\n-->", x->val, HBT->len);
    i = 0; //用i指向待调整元素的位置，初始指向堆顶位置
    j = 2 * i + 1;//用j指向i的左孩子位置，初始指向下标为1的位置
    while (j <= HBT->len - 1)//寻找待调整元素的最终位置，每次使孩子元素上移一层，调整到孩子为空时止
    {
        if (j < HBT->len - 1 && HBT->heap[j]->val < HBT->heap[j+1]->val)//若存在右孩子且较小，使j指向右孩子
            j++;
        if (x->val >= HBT->heap[j]->val) //若x比其较小的孩子还小，则调整结束，退出循环
            break;
        HBT->heap[i] = HBT->heap[j];//否则，将孩子元素移到双亲位置
        i = j; //将待调整位置变为其较小的孩子位置
        j = 2 * i + 1;//将j变为新的待调整位置的左孩子位置，继续下一次循环

    }
    HBT->heap[i] = x; //把x放到最终位置
    return temp; //返回原堆顶元素
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
    ElemType currnode = deleteHeap(HBT);

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

    while (1 == bumflag)
    {
        //if (1 == bumflag)//only one preficurrnode in node
        //{
        if(ERROR == transNode(currnode, root))
        {
            __my_debug("error in transenode\n");
            return ERROR;
        }
        //}

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
            //maxindx = i;
            //char matchstr[MAX_COL] = currnode->buf[i];
            TRIE_NODE *cp;
            if(ERROR == prefixMatchNode(root, currnode->buf[i], &cp))
            {
                __my_debug("match node error\n");
                return ERROR;
            }
            if(cp->val > maxval)
            {
                maxval = cp->val;
                maxindx = i;
                //__my_debug("%s\n", currnode->buf[i]);    
                //__my_debug("%d\n", cp->val);    
            }
            //__my_debug("%s\n", currnode->buf[i]);    
            //__my_debug("%d\n", cp->val);    
        }
        //bumflag += currnode->flag[i];
    }

    for (i = 0; i < MAX_NODE; i++)
    {
        if (maxindx == i)
        {
            newnode_1->flag[maxindx] = 0;    
        }
        else
        {
            newnode_2->flag[maxindx] = 0;
        }
        newnode_2->val = maxval;
        newnode_1->val = currnode->val - maxval;

    }
    
    
    //__my_debug("%s\n", currnode->buf[i]);    
    __my_debug("%d\n", newnode_1->val);    
    __my_debug("%d\n", newnode_2->val);    

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
    assert(1 == bumflag);

    //__my_debug("%d\n", indx); 
    
    char temp[MAX_COL] = {0};
    strcpy(temp, x->buf[indx]);

    int len = strlen(x->buf[indx]);
    //__my_debug("%d\n", len);
    temp[len+1] = '\0';

    TRIE_NODE *cp;
    for (i = 0; i < MAX_NODE; i++)
    { 
        temp[len] = hs[i];
        x->flag[i] = 1;
        //__my_debug("%d\n", len);
        //__my_debug("%s\n", temp);
        strcpy(x->buf[i], temp);
        if (NO_MATCH == prefixMatchNode(root, temp, &cp))
        {
            x->flag[i] = 0;
        }    
    }
    return OK;
}

