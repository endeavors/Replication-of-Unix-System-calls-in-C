/*
 * Filename: nameSortDescending.c
 * Author: Gurkirat Singh
 * Description: This file compares two strings, which are called from the 
 *              two void pointers passed in to us, and then calls strcmp
 *              to see whether or not the strings were greater than, less than,
 *              or equal to each other. The purpose is to sort the files
 *              in name descending manner.
 */

#include <string.h>
#include "myls.h"

/*
 * Function: nameSortDescending()
 * Function prototype: int nameSortDescending(const void *p1,const void *p2)
 * Description: This function casts the void pointers to struct fileInfo
 *              pointers and then gets the names of the two files, then 
 *              which we compare using strcmp to see which of the two 
 *              strings is greater than alphabetically. We need to sort
 *              the file names in descending order. 
 * Parameters:
 *      arg1: const void *p1 -- void pointer to struct 1
 *      arg2: const void *p2 -- void pointer to struct 2 that contains the
 *                              name of the file
 * Side Effects: None
 * Error conditions: None
 * Return value: Positive num to show p2 is greater than p1
 *              Negative num to show p1 is greater than p2
 *              Zero to show that p1 is equal to p2
 */
int nameSortDescending(const void *p1, const void *p2)
{
    /* Cast void pointer to struct fileInfo pointer so that we can get the
     * name of the files
     */
    char *structOne = ((struct fileInfo *)p1)->name;
    char *structTwo = ((struct fileInfo *)p2)->name;

    /* Call strcmp to see which string is bigger/smaller */
    return strcmp(structTwo,structOne);
}
