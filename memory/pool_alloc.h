#ifndef _POOL_ALLOC_
#define _POOL_ALLOC_

#include <stdlib.h>

typedef struct Cell {
    void* memory;
    struct Cell *next;
    struct Cell *prev;
} Memory_Cell;

typedef struct sPoolMemory {
    void* start_Pool_Memory;
    size_t size_Pool_Memory;
    size_t number_free_Cells;
    size_t cell_Size;
    size_t cell_Number;
    Memory_Cell *first;
    Memory_Cell *current;
    Memory_Cell *last;
} *Pool_Memory;

Pool_Memory new_Pool_Memory(size_t cell_Number, size_t cell_Size);

void resize_Pool_Memory(Pool_Memory globale_Pool_Memory, size_t size_Pool_Memory, size_t partition_Number);

void* Pool_Memory_Alloc(Pool_Memory globale_Pool_Memory, size_t size);

void* Pool_Memory_Realloc(Pool_Memory globale_Pool_Memory, size_t size);

void Pool_Memory_Free(Pool_Memory globale_Pool_Memory);

void delete_Pool_Memory(Pool_Memory globale_Pool_Memory);

#endif /* end of include guard: _POOL_ALLOC_ */
