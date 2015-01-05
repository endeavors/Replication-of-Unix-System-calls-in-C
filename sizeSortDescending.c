/*
 * Filename: sizeSortDescending.c
 * Author: Gurkirat Singh
 * Description: This file serves as the comparsion method that qsort method
 *              will call and utilize in order to compare the sizes of 
 *              two different st_size fields of the struct. It will sort
 *              the structs in descending order.
 */

/* Local header file */
#include "myls.h"

/*
 * Function: sizeSortDescending()
 * Function prototype: int sizeSortDescending(const void* p1, const void *p2)
 * Description: This function takes in two void pointers to struct fileInfo
 *              and gets the st_size fields, which is the size of the structs
 *              and compares which size is greater by subtracting them from
 *              one another. Positive num means that p2 struct is greater than
 *              p1.
 * Parameters:
 *      arg1: const void * p1 -- void pointer that serves as our struct 
 *                              fileInfo pointer to that specific struct
 *      arg2: const void *p2 -- void pointer that is a struct fileInfo pointer
 *                              to the second struct we need to compare size of
 * Side Effects: none
 * Error conditions: none
 * Return value: Positive num indicating p2 is greater than p1
 *              Negative num indicating p1 is greater than pa2
 *              Zero if both sizes are equal
 */
int sizeSortDescending(const void* p1, const void *p2)
{
    /* Cast void pointer to struct fileInfo pointer and get the size of each
     * struct
     */
    long structOne = ((struct fileInfo *)p1)->stbuf.st_size;
    long structTwo = ((struct fileInfo *)p2)->stbuf.st_size;

    /* Subtract the two sizes from one another to sort in Descending order*/
    return (structTwo - structOne);
}
