/*
 * Filename: displayPermissions.c
 * Author: Gurkirat Singh
 * Description: This file displays the permissions "rwx" according to each
 *              file and if the permission bit is not set, "-" is the 
 *              default.
 */
#include <stdio.h>
#include <sys/stat.h>
#include "myls.h"

/*
 * Function: displayPermissions()
 * Function prototype: void displayPermissions(const mode_t mode)
 * Description: This function checks each mode (group owner, read, write,
 *              execute of owner's files, or other users) and according
 *              to that displays the permission of the files using "rwx",
 *              the default being "-" which means that no permission bit
 *              was set. 
 * Parameters:
 *    arg1: const mode_t mode -- symbolic constants for file mode bits
 * Side Effects: None
 * Error Conditions: None.
 * Return value: None; it's void
 */

void displayPermissions(const mode_t mode)
{
    /* "-" is the default permission */
    /* Read, write, execute or search permission bit for owner of file */
    (void)printf((S_IRUSR & mode)? "r": "-");
    (void)printf((S_IWUSR & mode)? "w": "-");
    (void)printf((S_IXUSR & mode)? "x": "-");
    
    /* Group owner of the file */
    (void)printf((S_IRGRP & mode)? "r": "-");
    (void)printf((S_IWGRP & mode)? "w": "-");
    (void)printf((S_IXGRP & mode)? "x": "-");

    /* other users */
    (void)printf((S_IROTH & mode)? "r": "-");
    (void)printf((S_IWOTH & mode)? "w": "-");
    (void)printf((S_IXOTH & mode)? "x": "-");

}
