#ifndef _MYFILE_H_ 
#define _MYFILE_H_

#include "gttypes.h"

/***********************************************************************
*FunctionName : readFile
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : reading file data to 2 dementional buffer.
*InputParam :   buffer - using for saving data in file
                  fileName - filename.
*OutputParam :  none
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int readFile(char buffer[MAX_LINE][MAX_COL], 
        const char *fileName);

/***********************************************************************
*FunctionName : writeFile
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 04:44:51 PM
*Descreption : write data to file
*InputParam :   buffer - data used to write to file in memory.
                fileName - value of map.
*OutputParam : none
*ReturnValue : none
*Relation : none
*OtherInfo : none
************************************************************************/
int writeFile(char buffer[MAX_LINE][MAX_COL], 
        const char *fileName);

int addFile(char buffer[MAX_LINE][MAX_COL],
         const char *fileName, int num);

//int clearFile(const char *filename)

#endif // MYFILE_H_
