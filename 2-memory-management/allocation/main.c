#include <stdio.h>
#include "_malloc.c"

int main()
{
    int *p = (int *)_malloc(100 * sizeof(int));
    char *q = (char *)_malloc(250 * sizeof(char));
    int *r = (int *)_malloc(1000 * sizeof(int));

    _free(p);

    char *w = (char *)_malloc(700);

    _free(r);

    int *k = (int *)_malloc(500 * sizeof(int));
    printf("Allocation and deallocation is done successfully! \n");
}
