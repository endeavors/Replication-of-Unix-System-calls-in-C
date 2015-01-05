/*
 * Filename: unitTest_nameSortDescending.c
 * Author: Gurkirat Singh
 */
#include "myls.h"
#include "test.h"
#include "string.h"
#include "dirent.h"

void testNameSortDescending()
{
    struct fileInfo struct1;
    struct fileInfo struct2;
    char dst[MAXNAMLEN] = "boy";
    char dst1[MAXNAMLEN] = "girl";
    strcpy(struct1.name, dst);
    strcpy(struct2.name, dst1);

    int x = nameSortDescending(&struct1, &struct2);
    TEST(x > 0);

    struct fileInfo st1;
    struct fileInfo st2;
    char s[MAXNAMLEN] = "Helloooo";
    char s1[MAXNAMLEN] = "Hellooo";
    strcpy(st1.name, s);
    strcpy(st2.name, s1);

    int y = nameSortDescending(&st1, &st2);
    TEST(y < 0);
}

int main()
{
    testNameSortDescending();
    return 0;
}
