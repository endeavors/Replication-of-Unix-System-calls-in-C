/*
 * Filename: buildFileInfoTable.c
 * Author: Gurkirat Singh
 * Description: This file creates an array of fileInfo struct which contain all
 *              the file information. In other words, each index of the array
 *              which is basically can be considered a directory contains all
 *              all information of the files inside that directory.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "strings.h"
#include "myls.h"

/*
 * Function: buildFileInfoTable()
 * Function prototype: int buildFileInfoTable(const char*filename, struct 
 *                        fileInfo **const tablePtr)
 * Description: This function checks if filename inputted is a directory or not
 *              and accordingly allocates space for the struct that will
 *              contain the file's info. If it's a directory, there will an 
 *              array of struct pointers, each of the index which will contain
 *              the name of the file, and other information such as permissions
 *              and modes, etc. Realloc is used to allocate space for each
 *              index inside the array.
 * Paramters:
 *    arg 1: const char* filename-- name of file that is passed in from command
 *                        line, which we then check is a directory of not
 *    arg 2: struct fileInfo** const tablPtr -- pointer to null "array"
 *                        which will store the info of each file.
 * Side Effects: Open directory, malloc/realloc errors can occur
 * Error conditions: check if with the filename provided, we can open the
 *                    directory. Make sure realloc doesn't return null
 * Return value: the size of the table, which is the number of entries
 */
int buildFileInfoTable(const char*filename,struct fileInfo **const tablePtr)
{
    /* local variables */
    struct stat buffer;
  	struct stat fileStat;
    struct fileInfo *fileStruct = NULL;
    struct fileInfo *secondPtr = NULL;
    struct dirent* dirStruct;
    int status, fileStatus;
    int tblSize = 0;
    DIR * directoryPtr;
    char fullPath[MAXNAMLEN];
    char fileHolder[MAXNAMLEN];

    /* get the info about the file */
    status = lstat(filename, &buffer);

    /*successful completion*/
    if (status == 0){
         
        /* filename entered is a directory */
        if(S_ISDIR(buffer.st_mode)){
            (void)printf("%s:\n", filename );
            directoryPtr = opendir(filename);
            char charPointer[BUFSIZ];
 
            /* Couldn't open the directory, return error */
            if (directoryPtr == NULL){
                (void)snprintf(charPointer,BUFSIZ,"%s%s",STR_OPENDIR_ERR,
                    filename);
                perror(charPointer);
                return 0;
            }

            /* Go through each file in the directory, and allocate space for
             * each file's info, which is stored in a struct
             */
            while((dirStruct = readdir(directoryPtr)) != NULL){
                
                /* Make a duplicate of filename  */
                (void)strncpy(fileHolder, filename, MAXNAMLEN);
                (void)snprintf(fullPath,MAXNAMLEN, "%s/%s" , fileHolder,
                    dirStruct->d_name);
                
                /* Get info about current file we are visiting */
				        fileStatus = lstat(fullPath, &fileStat);
				  
                /* successful */
                if (fileStatus == 0){

                    /* allocate one more space for one more struct fileInfo */
					          fileStruct = (struct fileInfo*)realloc(fileStruct,
                                (tblSize + 1) * sizeof(struct fileInfo));
					          
                    /* Realloc failed; close directory and print error */
                    if (fileStruct == NULL){
                        perror(STR_ALLOC_ERR);
						            (void)fprintf(stderr,STR_PARTIAL_INFO);
                        if (directoryPtr != NULL)
				                    (void)closedir(directoryPtr);
                        *tablePtr = secondPtr;
					            	return tblSize;
				          	}

                    /* Keep track of old table */
                    secondPtr = fileStruct;

                    /* Store info in the struct inside the space we just 
                     * allocated
                     */
					          (void)memset(fileStruct[tblSize].name,0,MAXNAMLEN);
					          (void)strncpy(fileStruct[tblSize].name,dirStruct->d_name,
                        MAXNAMLEN);
				           	fileStruct[tblSize].stbuf = fileStat;
				            
                    /* Keep track of the number of entries we have for our
                     * array
                     */
                    tblSize++;
				        }else{

                    /* Couldn't retrieve info about the file inputted */
					          (void)fprintf(stderr, STR_LSTAT_ERR);
					          perror(dirStruct->d_name);
					          return 0;
				        }
            }
             
            /* Close directory and set the pointer to the first element
             * of the array
             */
			      if (directoryPtr != NULL)
				        (void)closedir(directoryPtr);
            
			      *tablePtr = fileStruct;
        }else{

            /* File is just a file, not a directory; don't use realloc*/
            fileStruct = (struct fileInfo*)malloc(sizeof(struct fileInfo));
            if (fileStruct == NULL){
                (void)fprintf(stderr,STR_ALLOC_ERR);
                return 0; 
            }

            /* Just store the name and otehr info about the file in the
             * struct 
             */
            (void)memset(fileStruct->name,0,MAXNAMLEN);
            (void)strncpy(fileStruct->name,filename,MAXNAMLEN);
            fileStruct->name[MAXNAMLEN - 1] = NULL;
            fileStruct->stbuf = buffer;
            
            /* Set pointer to 1st element in the array */
            *tablePtr = fileStruct;
            ++tblSize;
        }
    }else{

        /* Couldn't retrieve information about the file; print error */
        (void)fprintf(stderr,STR_LSTAT_ERR);
        (void)perror(filename);
        return 0;
    }
    return tblSize;
}
