/*
 * Filename: sizeSortAscending.s
 * Author: Gurkirat Singh
 * Description: This file is a leaf subroutine that compares two struct
 *              pointers and then sorts them in ascending order. It utilizes
 *              the offset of the size of the struct fileInfo to get the
 *              struct's size. The offset helps get the size of the struct.
 */

	.global sizeSortAscending	!declare global name so we can call it
					!from outside this file

	.section ".text"		!text section begins here

/*
 * Function: sizeSortAscending()
 * Function prototype: int sizeSortAscending(const void *p1, const void *p2)
 * Description: This function is a leaf subroutine, which means that there
 *              is no save statement in the beginning and no input or local
 *              registers. We use offset to get the size fields of each of the
 *              structs and subtract the second struct from the first one
 *              since we need to sort it in ascending order. Qsort calls
 *              this function to compare two structs at a time. 
 * Parameters: 
 *      arg1: const void *p1 -- void pointer that we cast it to struct fileInfo
 *                          pointer to get the size of the struct of p1
 *      arg2: const void *p2 -- second struct fileInfo pointer that we need to
 *                          compare to the first one to see which one is 
 *                          greater or smaller.
 * Side Effects: None
 * Error Conditions: None
 * Return value: Positive num indicating p1 is greater than p2
 *              Negative num indicating p2 is greater than p1
 *              Zero to indicate that both sizes are equal to each other
 * Register used:
 *      %o0 -- arg 1 -- void pointer to struct 1
 *      %o1 -- arg 2 -- void pointer to struct 2
 *      %o3 -- contains the offset size of the struct size
 *      %o4 -- contains the actual size of struct 1
 *      %o5 -- contains the actual size of struct 2
 */
sizeSortAscending:
	set	offsetSize, %o3		!set the offset to get to struct size
					!inside a temp variable
	ld	[%o3], %o3

	ld	[%o0 + %o3], %o4	!load the size of struct 1
	ld	[%o1 + %o3], %o5	!load the size of struct 2

	sub	%o4, %o5, %o2		!subtract size 2 from size 1
					!to sort in ascendin order
	mov	%o2, %o0		!return the result

	retl				!retl for return in leaf subroutine
	nop


