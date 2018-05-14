#ifndef TRIE_H
#define TRIE_H

#include "gttypes.h"

/***********************************************************************
*FunctionName : hstrie
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : Used to mapping character infomation to next node index
                in trie tree.
*InputParam :   in - key of map.
*OutputParam :  int - value of map.
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int hstrie(char in);

/***********************************************************************
*FunctionName : trie_create
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : create trie tree.
*InputParam :   none
*OutputParam : TRIE_NODE* - the root node of trie tree.
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
TRIE_NODE* trie_create();

/***********************************************************************
*FunctionName : trie_insert
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : insert words to trie tree.
*InputParam :   word - the string that insert to trie tree.
                root - root node of Trie tree.
*OutputParam : None
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int trie_insert(char *word, TRIE_NODE *root);

/***********************************************************************
*FunctionName : trie_travers
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : travers the trie tree, and save data in 2 dementional 
                buffer.
*InputParam : hd_buf - 2 dementional buffer for saving data.
                buf - temp parameters for recursion.
                node - begin node for travers.
                indx - temp parameters for recursion, first value is
                        0.
                row - temp parameters for recursion, first value is 0.
*OutputParam : None
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int trie_travers(char hd_buf[MAX_LINE][MAX_COL], char buf[MAX_COL], 
        TRIE_NODE *node, int indx, int *row);

/***********************************************************************
*FunctionName : trie_destroy
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : destroy the trie tree.
*InputParam : root - root node of Trie tree.
				indx - variable parameters for recursion, if recur frome
                    root node, the value is 0.
*OutputParam : None
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int trie_destroy(TRIE_NODE *root, int indx);

/***********************************************************************
*FunctionName : createBinaryTree
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : construct a Trie tree from data in the buffer and return
				the root node
*InputParam : buffer - buffer to save file data
*OutputParam : TNode* - root if Trie tree
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
TRIE_NODE* createBinaryTree(char buffer[MAX_LINE][MAX_COL]);

/***********************************************************************
*FunctionName : sortAndWriteFile
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : Traverse the Trie tree , sort, and write the data into a file
*InputParam : root - root node of Trie tree
				fileName - file that need to be write
*OutputParam : None
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int sortAndWriteFile(TRIE_NODE* root, const char* fileName);

/***********************************************************************
*FunctionName : prefixMatch
*Author : Zheng Qinwen
*CreateDate : Thu 13 May 2018 04:44:51 PM
*Descreption : Enter the string, and match the maximum string
*InputParam : root - begin node of Trie tree for serching
*OutputParam : None
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int prefixMatch(TRIE_NODE* root);


#endif //TRIE_H
