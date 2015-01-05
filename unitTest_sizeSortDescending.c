/*
 * Filename: unitTest_sizeSortDescending.c
 * Author: Gurkirat Singh
 */

#include "myls.h"
#include "test.h"

void testSizeSortDescending()
{
     struct fileInfo struct1;
     struct fileInfo struct2;

     struct1.stbuf.st_size = 7;
     struct2.stbuf.st_size = 13;

     int x = sizeSortDescending(&struct1,&struct2);
     TEST(x > 0);

     struct fileInfo st1;
     struct fileInfo st2;

     st1.stbuf.st_size = 1;
     st2.stbuf.st_size = 0;

     int y = sizeSortDescending(&st1, &st2);
     TEST(y < 0);
}

int main()
{
    testSizeSortDescending();
    return 0;
}
