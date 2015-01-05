/*
 * Filename: globals.c
 * Author: Gurkirat Singh
 * Description: This file contains the global variables that the assembly
 *              files may need.  
 */
#include <stddef.h>
#include "myls.h"

/* Calculate the offset size of each file struct we use */
int offsetSize = offsetof(struct fileInfo, stbuf.st_size);
