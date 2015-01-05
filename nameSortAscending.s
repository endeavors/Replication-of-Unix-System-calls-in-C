/*
 * Filename: nameSortAscending.s
 * Author: Gurkirat Singh
 * Description: This program servers as a comparison method to qsort that sorts
 *              the names of the files in ascending order. It calls strcmp to
 *              compare the two strings and then return a positive, negative,
 *              or zero value to show whether the string was greater/less than
 *              the one it was being compared to.
 */

	.global nameSortAscending	!declare global variable we can call it
					!from another file

	.section ".text"		!text segment begins here

/*
 * Function: nameSortAscending()
 * Function prototype: int nameSortAscending(const void *p1, const void* p2);
 * Description: This function directly calls strcmp by taking in the name of
 *              the files from the two structs and then compares which string
 *              was bigger or smaller so that it can be sorted in an
 *              ascending manner.
 * Parameters: 
 *      arg1: const void *p1 -- void pointer to the struct fileInfo 1
 *      arg2: const void *p2 -- void pointer to the struct fileInfo 2 of which
 *                              we will get the name of the file
 * Side Effects: None
 * Error Conditions: none
 * Return value: Positive to show that p1 is greater than pa2
 *              Negative to show that p2 is greater than p1
 *              Zero to show that both p1 and p2 are equal
 * Registers used:
 *      %i0 -- arg1 -- void pointer struct 1
 *      %i1 -- arg2 -- void pointer struct 2
 */
nameSortAscending:
	save	%sp, -96, %sp		!save caller's window

	mov	%i0, %o0		!store void pointer as a parameter
	mov	%i1, %o1		!so we can compare to two strings

	call	strcmp			!compare two strings
	nop

	mov	%o0, %i0		!return the result by storing it in
					!%i0

	ret				!Restore caller's window
	restore
