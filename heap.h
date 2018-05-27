#ifndef _HEAP_H_
#define _HEAP_H_

#include "gttypes.h"
#include <stdio.h>

int initHeap(HEAPSQ *HBT, int MS);

void clearHeap(HEAPSQ *HBT);

int emptyHeap(HEAPSQ *HBT);

int insertHeap(HEAPSQ *HBT, ElemType x);

int expantionHeap(HEAPSQ *HBT, TRIE_NODE *root);

int transNode(ElemType x, TRIE_NODE *root);

ElemType deleteHeap(HEAPSQ *HBT);

void printnode(ElemType x);

int myHeapClassification(int classnum, TRIE_NODE *root);


#endif
