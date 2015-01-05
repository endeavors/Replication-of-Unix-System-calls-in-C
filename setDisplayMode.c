/*
 * Filename: setDisplayMode.c
 * Author: Gurkirat Singh
 * Description: This file parsing the command line options and sets the flags
 *              by turning on the bits of that specific flag we have identified
 *              and it does it by using getopt. It loops through each of the
 *              flags and if the flag was not valid, the err flag is set.
 */

#include <unistd.h>
#include "myls.h"

/*
 * Function: setDisplayMode();
 * Function prototype: unsigned int setDisplayMode(int argc,char*argv[]);
 * Descritption: This function turns on the bits in the unsigned int
 *               with the number of bits we have identified in the myls.h
 *               file. The error flag is set if invalid flags were entered.
 *               All flags are accounted for, even if no flags were entered
 *               and then unsigned int to which all the flag bit were set
 *               is returned.
 * Parameters:
 *      arg1: int argc -- number of arguments passed in on command line
 *      arg2: char *argv[] -- all the arguments in char * (strings) format
 *                          inside an array
 * Side Effects: If no flags were found, the error flag bit is returned
 * Error Conditions: Default case for no flags handles error cases
 * Return value: Return the unsigned int to which all the flag bit were
 *              set.
 */

unsigned int setDisplayMode(int argc, char* argv[])
{
    /* Local variables */
    int c;
    unsigned int num = 0;

    /* Run through the command line arguments and see if the flags
     * match with what we consider valid flags. 
     */
    while((c = getopt(argc,argv,STR_GETOPT_OPTIONS)) != -1){
        switch(c){
            /*No input case was found*/
            case '?':
                num = num | ERR_FLAG;
                return num;
            case 'a':
                num = num | AFLAG;
                break;
            case 'l':
                num = num | LFLAG;
                break;
            case 'r':
                num = num | RFLAG;
                break;
            case 'S':
                num = num | SFLAG;
                break;
            case 'B':
                num = num | BFLAG;
                break;
                
        }
    }

    /* Return num that all the bits set to it if valid flags were found */
    return num;

}
