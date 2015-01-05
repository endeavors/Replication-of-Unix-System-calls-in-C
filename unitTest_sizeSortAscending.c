/*
 * Filename: unitTest_sizeSortAscending.c
 * Author: Gurkirat Singh
 */

#include "myls.h"
#include "test.h"
#include "globals.c"
void testSizeSortAscending()
{
    struct fileInfo struct1;
    struct fileInfo struct2;

    struct1.stbuf.st_size = 3;
    struct2.stbuf.st_size = 8;

    int x = sizeSortAscending(&struct1,&struct2);
    TEST(x == -5);
    
    struct fileInfo str;
    struct fileInfo str2;

    str.stbuf.st_size = 10;
    str2.stbuf.st_size = 8;

    int y = sizeSortAscending(&str, &str2);
    TEST(y == 2);

    struct fileInfo st;
    struct fileInfo st2;

    st.stbuf.st_size = 20;
    st2.stbuf.st_size = 20;

    int w = sizeSortAscending(&st, &st2);
    TEST(w == 0);
    
}

int main()
{
    testSizeSortAscending();
    return 0;
}
