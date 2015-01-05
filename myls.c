/*
 * Filename: myls.c
 * Author: Gurkirat Singh
 * Description: This file is the main function of the program and handles all
 *              command line arguments and calls other functions to display
 *              file information according to which flags were set. The error
 *              checking of bad flags is done in setDisplayMode and the usage
 *              is printing if an error was found. We cycle through the 
 *              command line arguments to build our fileInfo table.
 */

#include <stdlib.h>
#include <stdio.h>
#include "myls.h"
#include "strings.h"

/*
 * Function: main()
 * Function prototype: int main(int argc, char* argv[])
 * Description: This function allocates memory of the initial table that
 *              will contain all of the file's information. If error bit
 *              is set, then we print the usage error and return out of the
 *              function. We cycle through the command line arguments, get the
 *              size of the table and for each entry in the table, print out
 *              every file's info/name according to what flag was set.
 * Parameters:
 *      arg1: int argc -- number of arguments
 *      arg2: char* argv[] -- actual arguments entered on the command line
 * Side Effects: Check if error flag was set or not and incrementing optind
 *                  when displaying file's info in a loop
 * Error Conditions: None.
 * Return Value: 0 indicating successful completion
 */

int main(int argc, char* argv[])
{
    struct fileInfo ** const tblPtr=(struct fileInfo **const)malloc(
        sizeof(struct fileInfo));
    unsigned int displayModeStatus;
    const char *fileName;
    int tblSize = 0;

    displayModeStatus = setDisplayMode(argc, argv);

    /* some error occurred */
    if (displayModeStatus & ERR_FLAG){
        (void)fprintf(stderr, STR_USAGE, argv[0]);
        return 0;
    }
    
    /* no other arguments found */
    if (argv[optind] == NULL){
        /* First get the size of the table */
        tblSize = buildFileInfoTable(CURRENT_DIRECTORY,tblPtr);
        /* Display file's info for each entry in the table*/
        displayFileInfo(*tblPtr, tblSize, displayModeStatus);

    }else{
        /* Go through each argument until the end */
        while (optind < argc){
            fileName = argv[optind];
            /* Get the entries in the table */
            tblSize = buildFileInfoTable(fileName, tblPtr);
            /* Show each file's info according to which flag was set */
            displayFileInfo(*tblPtr, tblSize,displayModeStatus);
            optind++;
        }

    }
    /*We are done with the table, so free the memory that it has allocated */
    free(*tblPtr);
    
    return 0;
}
