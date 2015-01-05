/*
 * Filename: displayGroupName.s
 * Author: Gurkirat Singh
 * Description: This file prints out the group name of the file, which is
 *              basically the group that owns the file, by converting the 
 *              gid to a string name.
 */

	.global displayGroupName	!declare global name so we can call
					!it from other files
	.section ".data"

GID:	.asciz "%-8ld "			!declare string formats to be used with
					!printf to print out the gid/group name
GNAME:	.asciz "%-8s "

	.section ".text"		!text section begins here

/*
 * Function: displayGroupName()
 * Function prototype: void displayGroupName(const gid_t gid);
 * Description: This functions calls getgrgid by passing in the numerical
 *              gid of the file that it belongs to and converts that number
 *              to a representative string name and prints it out if 
 *              conversion was successful; if not, then it just prints out
 *              the numerical gid of the file.
 * Parameters: 
 *    arg1: const gid_t gid: numerical ID of group that holds the file
 * Side Effects: The group name might return null
 * Error conditions: check if the group name of file is null or not
 * Return Value: None
 * Registers Used:
 *    %i0 -- arg 1 -- numerical gid of the file to which it belongs
 *    %l0 -- store the output of getgrgid, the group name
 *    %g0 -- check to see if the output of getgrgid was null or not
 */
displayGroupName:
	save	%sp, -96, %sp		!save caller's window

	mov	%i0, %o0		!call getgrgid to convert the 
					!numerical ID to a string name
	call	getgrgid		!of that group for the file
	nop

	mov	%o0, %l0
	cmp	%l0, %g0		!if getgrgid fails, then just print
	be	isNULL			!the numerical gid of the file
	nop

	ld	[%l0], %l0
	set	GNAME, %o0		!conversion to string name was
	mov	%l0, %o1		!successful, now print out the 
	call	printf			!name of the group for the file
	nop

	ba	Return			!we are done
	nop

isNULL:					!Failure occurred
	set	GID, %o0		!print numerical gid of file
	mov	%i0, %o1
	call	printf
	nop

Return:
	ret				!Restore caller's window
	restore
