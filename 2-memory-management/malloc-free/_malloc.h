#include <stdio.h>
#include <stddef.h>
#define MEM_SIZE 20000

char memory[MEM_SIZE];

struct block
{
    size_t size;
    int free;
    struct block *next;
};

struct block *freeList = (void *)memory;

void initialize();
void split(struct block *fitting_slot, size_t size);
void *_malloc(size_t noOfBytes);
void merge();
void _free(void *ptr);
