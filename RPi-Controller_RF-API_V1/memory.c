/*
 * memory.c
 *
 *  Created on: 15 Nov 2016
 *      Author: André Gomes
 */

#include "memory.h"


/* Memory file pointer */
FILE *fp;
char memFile[]="memory.txt";


/* Variables to manage the memory file */
int ch;   		//temporary place to store character of the memory file (one at a time)
uint8_t nLine=0;  	//count number lines in memory file.


/* Function to open memory file */
uint8_t Memory_Open(void)
{
    /* Opens the memory file to update both reading and writing. The file must exist. */
    fp = fopen(memFile,"r+");;

    if(fp == NULL)
    {
        printf("\nError...cannot open/create files");
        return 1;
    }

    return 0;
}


/* Function to read one position of the memory file - one line per position */
void Memory_ReadPos(unsigned int pos, unsigned int *data)
{
	Memory_Open();

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')  //counts number of lines
            nLine++;;

        if(nLine == pos)
        {
            fscanf(fp, "%u", data);
            break;
        }
    }

    /* set the file pointer to the start of the file and clear line count */
    nLine = 0;
    rewind(fp);

    Memory_Close();
}


/* Function to write one position on the memory file - one line per position */
void Memory_WritePos(unsigned int pos, unsigned int *data)
{
	Memory_Open();

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')  //counts number of lines
            nLine++;

        if(nLine == pos)
            fprintf(fp, "%5u", *data);
    }

    /* set the file pointer to the start of the file and clear line count */
    nLine = 0;
    rewind(fp);

    Memory_Close();
}


/* Function to close the memory file */
void Memory_Close(void)
{
    fclose(fp);
}

