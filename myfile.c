/*************************************************************************
*File Name : myfile.c
*Author : Zheng Qinwen
*CreateDate : Sun 13 May 2018 10:40:16 PM
*Reversion : v1.1
*Description : file operation in project
*Copyright : Fiberhome
*OtherInfo : None
*ModifyLog : None
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "myfile.h"

/*
 *  read file into buffer
 * */
int readFile(char buffer[MAX_LINE][MAX_COL], const char *fileName)
{
    /*initialize input stream*/
	FILE *fpRead = fopen(fileName, "r");
	if (NULL == fpRead)
	{
		//exit(0);
        __my_debug("can not open file");
	    return ERROR;
    }

    int currow = 0;
	while(!feof(fpRead))/*read input stream into buffer*/
	{
		if (NULL == fgets(buffer[currow], MAX_COL, fpRead))
		{
			break;
		}
		currow++;
	}

	fclose(fpRead);/*close input stream*/
	return OK;
}

/*
 *  write data into file
 * */
int writeFile(char buf[MAX_LINE][MAX_COL], const char *fileName)
{
    /*initalize output stream*/
    FILE *fp = fopen(fileName, "w");
    if (NULL == fp)
    {
        __my_debug("can not open file");
        return ERROR;
    }

    for (int i = 0; i < MAX_LINE; i++)/*write data into output stream*/
    {
        fprintf(fp, "%s\n", buf[i]);
    } 
    fclose(fp);/*close stram*/
    return OK;
}

int addFile(char buf[MAX_LINE][MAX_COL], const char *fileName, int num)
{

    FILE *fp = fopen(fileName, "a");
    if (NULL == fp)
    {
        __my_debug("can not open file");
        return ERROR;
    }

    fprintf(fp, "%d\n", num);
    for (int i = 0; i < num; i++)/*write data into output stream*/
    {
        fprintf(fp, "%s\n", buf[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);/*close stram*/
    return OK;
}
