/*
 * Filename: strings.h
 * Author: Gurkirat Singh
 * Description: Strings used in myls
 */

#ifndef MYLS_STRINGS_H
#define MYLS_STRINGS_H

#define STR_USAGE "Usage: %s [-alrSB] [file ...]\n"

#define STR_LSTAT_ERR "lstat --"

#define STR_OPENDIR_ERR "opendir --"

#define STR_PARTIAL_INFO "Only partial info will be displayed.\n"

#define STR_ALLOC_ERR "Attempted to allocate memory in buildFileInfoTable()"

#define STR_NLINK "%3lu "

#define STR_MAJOR_MINOR "%3ld %3ld "

#define STR_SIZE "%7ld "

#define STR_GNAME "%-8s "

#define STR_GID "%-8ld "

#define STR_PWNAME "%-8s "

#define STR_UID "%-8u "

#endif /* MYLS_STRINGS_H */
