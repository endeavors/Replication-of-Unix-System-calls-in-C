/*
 * Filename: unitTest_setDisplayMode.c
 * Author: Gurkirat Singh
 */

#include "myls.h"
#include "test.h"
void testSetDisplayMode()
{
    optind = 1;
    optarg = NULL;
    int argc = 2;
    struct fileInfo fileinfo;
    char *argv[] = {"exe", "-rlS"    };
    unsigned int x = setDisplayMode(argc,argv);
    TEST(x == (RFLAG | LFLAG | SFLAG));

    optind = 1;
    optarg = NULL;
    argc = 2;
    struct fileInfo file;
    char * argg[] = {"e", "-Ba"};
    unsigned int y = setDisplayMode(argc,argg);
    TEST(y ==  (BFLAG | AFLAG));

}

int main()
{
    testSetDisplayMode();
    return 0;
}
