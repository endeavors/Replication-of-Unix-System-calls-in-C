/*
 * Filename: myls.h
 * Author: Gurkirat Singh
 * Description: This file is the header file for all the prototypes
 *              of the C and assembly functions/subroutines, constants,
 *              structs, any anything that is needed by other files
 *              to run.
 */

#ifndef _MYLS_H
#define _MYLS_H

/* Bit masks for each of the flags we use in this program */
#define AFLAG 0x1
#define LFLAG 0x2
#define RFLAG 0x4
#define SFLAG 0x8
#define BFLAG 0x10
#define ERR_FLAG 0x80000000

#define STR_GETOPT_OPTIONS "larBS"
#define CURRENT_DIRECTORY "."

/* struct stat mode for each file */
#define DIRECTORY "d"
#define SYMLINK "l"
#define BLKDEVICE "b"
#define CHARDEVICE "c"
#define REGFILE "-"

/* seconds in 6 months */
#define SIXMONTHS_SECS 15724800

/* Char constants to use when printing time or checking if file is hidden
 * file or not 
 */
#define HIDDEN_FILE '.'
#define TILDA '~'
#define SPACE ' '
#define COLON ':'
#define NEWLINE '\n'
#define COLON_OFFSET 3

#include <dirent.h>     /* To pick up MAXNAMLEN - maximum filename length */
#include <sys/stat.h>   /* For struct stat definition */

struct fileInfo {
  char name[MAXNAMLEN];
  struct stat stbuf;
};

unsigned int setDisplayMode( int argc, char * argv[]);

int buildFileInfoTable( const char *filename, struct fileInfo ** const tablePtr );

void displayFileInfo( struct fileInfo * const table, const int entries,
    const int displayMode );

int sizeSortAscending( const void *p1, const void *p2 );
int sizeSortDescending( const void *p1, const void *p2 );
int nameSortAscending( const void *p1, const void *p2 );
int nameSortDescending( const void *p1, const void *p2 );
void displayPermissions( const mode_t mode );
void displayOwnerName( const uid_t uid );
void displayGroupName( const gid_t gid );

#endif /* _MYLS_H */
