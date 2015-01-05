/*
 * Filename: displayFileInfo.c
 * Author: Gurkirat Singh
 * Description: This file handles all of the cases for the flags and displays
 *              the output accordingly. It loops through each of the entries
 *              in the table and displays the information about each of the
 *              file if the L flag is set, for example, and if A flag is 
 *              set, it is going to print out all of the files, including
 *              the hidden files. 
 */

/* Standard C libraries */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mkdev.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>

/* Local header files */
#include "myls.h"
#include "strings.h"

/*
 * Function: displayFileInfo();
 * Function prototype: void displayFileInfo(sstruct fileInfo *const table,
 *                   const int entries, const int displayMode)
 * Description: Handle all things for different valid flags. Use qsort to sort
 *              the entries in the table; the default is ascending name sort.
 *              R flag is used to reverse the sorting order of files and L flag
 *              displays permission/owner's name/group's name of the file. This
 *              function cycles through all the entries in the table and 
 *              displays the information according to what each flag wants. 
 *              For example, A flag requires that hidden files must also be
 *              printed out and sorted. 
 * Parameters:
 *    arg 1: struct fileInfo *const table-- pointer to the first index of table
 *    arg 2: const int entries -- size of the table/number of files accounted
 *                                  for
 *    arg 3: const int displayMode -- mode that is returned by setDisplayMode
 *                                  which will tell us which flags were set
 * Side Effects: Realloc errors need to print out files processed. Spacing
 *                  between outputs is crucial for alignment
 * Error conditions: Need to check if directory could be opened successfully
 *                  and if there are any malloc/realloc errors. 
 * Return value: None; it's void.
 */

void displayFileInfo(struct fileInfo *const table, const int entries, const int
    displayMode)
{
    /* Local variables */
    int loopCounter = 0;
    char fileName[MAXNAMLEN];
    mode_t fileMode;
    struct stat stbuf;
    char *convertedStr, *leadingPtr, *trailingPtr;

    /* Size sort */
    if (SFLAG & displayMode){

        /* sort size ascending order */
        if (RFLAG & displayMode){
            qsort(table, entries, sizeof(struct fileInfo),sizeSortAscending);

        }else{
            /* descending order */
            qsort(table,entries, sizeof(struct fileInfo),sizeSortDescending);
        }
    }else{

        /*sort file names in descending order */
        if (RFLAG & displayMode){
            qsort(table, entries, sizeof(struct fileInfo), nameSortDescending);

        }else{
            /* ascending order */
            qsort(table,entries,sizeof(struct fileInfo), nameSortAscending);
        }

    }

    for (loopCounter = 0; loopCounter < entries; loopCounter++){

        (void)strncpy(fileName, (table[loopCounter]).name, MAXNAMLEN);

        /* If A flag is not set and file is a hidden file, skip this
         * iteration
         */
        if (!(AFLAG & displayMode)){
            /* Get the actual name of the file */
            char * baseName = basename(fileName);
            
            /* Check if there is a '.' in front of the file */
            if (baseName[0] == HIDDEN_FILE){
                continue;
            }
        }

        /* Don't display files with '~' at the file if B flag is set */
        if (BFLAG & displayMode){
            if(fileName[strlen(fileName)-1] == TILDA) continue;
        }

        if (LFLAG & displayMode){
            
            /* Store the entire struct info for that particular table index */
            stbuf = (table[loopCounter]).stbuf;
            fileMode = stbuf.st_mode;

            /* Print out the modes for each file; ex: d if it is directory,etc,
             * or the default '-' for a regular file
             */
            if (S_ISDIR(fileMode)) (void)printf(DIRECTORY);      //Directory
            else if (S_ISLNK(fileMode)) (void)printf(SYMLINK);   //Symbolic lnk
            else if (S_ISBLK(fileMode)) (void)printf(BLKDEVICE); //Block device
            else if (S_ISCHR(fileMode)) (void)printf(CHARDEVICE);//char device
            else (void)printf(REGFILE);                          //regular file

            /* Display the permission, owner's, and group's name of each file*/
            displayPermissions(fileMode);
            (void)printf(" ");
            (void)printf(STR_NLINK,stbuf.st_nlink);
            displayOwnerName(stbuf.st_uid);
            displayGroupName(stbuf.st_gid);

            /* We care about major and minor is char or block device is set */
            if (S_ISCHR(fileMode) || S_ISBLK(fileMode)){
                (void)printf(STR_MAJOR_MINOR, major(stbuf.st_rdev), \
                    minor(stbuf.st_rdev));
            }else{
                (void)printf(STR_SIZE,stbuf.st_size);
            }

            /* Sample time format: Wed Dec 31 16:00:00 1969 */
            convertedStr = ctime(&stbuf.st_mtime);
            leadingPtr = strchr(convertedStr, (int)SPACE);
      
            /* Modification time is greater than months, then the format is
             * Month Day Year, else, Month Day Hour:Min
             */
            if (((int)(stbuf.st_mtime)) < (time(NULL) - \
                SIXMONTHS_SECS))
            { 
                char cpyStr[MAXNAMLEN];
                /* Keep copy of the original time string */
                (void)strncpy(cpyStr,convertedStr, MAXNAMLEN);

                /* Set the pointer to the first colon found and subtract
                 * offset (3) to get to the whitespace
                 */
                char *colonOffset = strchr(convertedStr, (int)COLON);
                colonOffset = colonOffset - COLON_OFFSET;
                *colonOffset = '\0';

                /* Get rid of the Hour, min, seconds and set the last character
                 * to null
                 */
                trailingPtr = strrchr(cpyStr, (int)SPACE);
                char *newLine = strrchr(cpyStr, (int)NEWLINE);
                *newLine = '\0';

                /* Print the string we just created */
                (void)printf("%s %s ", leadingPtr + 1, trailingPtr + 1);

            }else{
                /* We don't need anything after the colon; get rid of it by 
                 * setting that pointer to null
                 */
                trailingPtr = strrchr(convertedStr, (int)COLON);
                *trailingPtr = '\0';
                (void)printf("%s ", leadingPtr+1);
            }
        }
        /* Regardless, always print out the name of the file */
        (void)printf("%s\n", fileName);

    }

}
