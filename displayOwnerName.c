/*
 * Filename: displayOwnerName.c
 * Author: Gurkirat Singh
 * Description: This file gets the name of the owner of the file from the
 *              struct that contains that name by converting the numerical
 *              uid of the file to a string name. The string name is the
 *              name of the owner of the file.
 */

/* Local header files */
#include "pwd.h"
#include "strings.h"
#include "myls.h"

/*
 * Function: displayOwnerName()
 * Function prototype: void displayOwnername(const uid_t uid);
 * Description: This function calls getpwuid by inputting the numerical
 *              uid of the file in order to convert that number into a 
 *              string name of the owner of the file. If the conversion
 *              is not successful, then just print out the numerical id,
 *              otherwise, print out the string name.
 * Parameters:
 *    arg1 -- const uid_t uid -- numerical id for the owner of the file
 * Side Effects: Owner name might return null
 * Error conditions: Check if null is returned when we try to get the 
 *                      owner's name for the file
 * Return value: None; it's void
 */
void displayOwnerName(const uid_t uid)
{
    struct passwd * ownerName;  /* getpwuid returns struct passwd pointer*/
    
    ownerName = getpwuid(uid);  /* convert numerica uid to string name */

    /* getpwuid failed, just print the numerical uid */
    if (ownerName == NULL)
        (void)printf(STR_UID, uid);
    else
        (void)printf(STR_PWNAME, ownerName->pw_name);
}
