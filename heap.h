#ifndef _HEAP_H_
#define _HEAP_H_

#include "gttypes.h"
#include <stdio.h>

/***********************************************************************
*FunctionName : initHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : initial heap struct, aplly memory for heap
*InputParam :   HEAPSQ - heap struct.
                int - size of struct
*OutputParam :  int - determine if aplly success.
*ReturnValue : OK - apply success.
                ERROR - aplly failed
*Relation : none
*OtherInfo : none
************************************************************************/
int initHeap(HEAPSQ *HBT, int MS);

/***********************************************************************
*FunctionName : clearHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : clear heap and free memory
*InputParam :   HEAPSQ - heap struct.
*OutputParam :  none
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
void clearHeap(HEAPSQ *HBT);

/***********************************************************************
*FunctionName : emptyHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : idetermine the heap is empty
*InputParam :   HEAPSQ - heap struct.
*OutputParam :  int - jujement result.
*ReturnValue : YES - the heap is empty.
                ERROR -the heap is not empty.
*Relation : none
*OtherInfo : none
************************************************************************/
int emptyHeap(HEAPSQ *HBT);

/***********************************************************************
*FunctionName : insertHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : insert element to heap
*InputParam :   HEAPSQ - heap struct.
                ElemType - element to insert
*OutputParam :  int - determine if insert success.
*ReturnValue : OK - insert success.
                ERROR - insert failed
*Relation : none
*OtherInfo : none
************************************************************************/
int insertHeap(HEAPSQ *HBT, ElemType x);

/***********************************************************************
*FunctionName : expantionHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : increase size of heap. +1
*InputParam :   HEAPSQ - heap struct.
                TRIE_NODE - the root of trie
*OutputParam :  int - determine if expand success.
*ReturnValue : OK - expand success.
                ERROR - expand failed
*Relation : none
*OtherInfo : none
************************************************************************/
int expantionHeap(HEAPSQ *HBT, TRIE_NODE *root);

/***********************************************************************
*FunctionName : transNode
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : split a node 1 prefix into a node 3 prefix
*InputParam :   ElemType - node.
                TRIE_NODE - the root of trie
*OutputParam :  int - determine if transe success.
*ReturnValue : OK - transe success.
                ERROR - transe failed
*Relation : none
*OtherInfo : none
************************************************************************/
int transNode(ElemType x, TRIE_NODE *root);

/***********************************************************************
*FunctionName : deleteHeap
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : delete and return the top element
*InputParam :   HEAPSQ - heap struct.
*OutputParam :  EleType - the pointer point into top element
*ReturnValue : 
*Relation : none
*OtherInfo : none
************************************************************************/
ElemType deleteHeap(HEAPSQ *HBT);

/***********************************************************************
*FunctionName : printnode
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : initial heap struct, aplly memory for heap
*InputParam :   ElemType - node to be print.
*OutputParam :  void
*ReturnValue : node
*Relation : none
*OtherInfo : none
************************************************************************/
void printnode(ElemType x);

/***********************************************************************
*FunctionName : myHeapClassification
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : sort the prefix and save it in a file
*InputParam :   TRIE_NODE - root of treil.
                int - num of class
*OutputParam :  int - determine if classify success.
*ReturnValue : OK - classify success.
                ERROR - classify failed
*Relation : none
*OtherInfo : none
************************************************************************/
int myHeapClassification(int classnum, TRIE_NODE *root);


#endif
