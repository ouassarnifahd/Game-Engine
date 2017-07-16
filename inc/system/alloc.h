#ifndef _ALLOC_
#define _ALLOC_

#include <stdlib.h>

#define Memory_1Ko 1ull << 10
#define Memory_1Mo 1ull << 20
#define Memory_1Go 1ull << 30

typedef struct {
    void* start_partition;
    size_t size_partition;
} partition;

typedef struct sStackMemory {
    void* start_Stack_Memory;
    void* start_free_Stack_Memory;
    partition *chunk_Stack_Memory;
    size_t partition_Number;
    size_t free_partitions;
    size_t used_partitions;
    size_t size_Stack_Memory;
    size_t size_free_Stack_Memory;
} *Stack_Memory;

Stack_Memory new_Stack_Memory(size_t size_Stack_Memory);

void resize_Stack_Memory(Stack_Memory globale_Stack_Memory, size_t size_Stack_Memory);

void* Stack_Memory_Alloc(Stack_Memory globale_Stack_Memory, size_t size);

void* Stack_Memory_Realloc(Stack_Memory globale_Stack_Memory, size_t size);

void Stack_Memory_Free(Stack_Memory globale_Stack_Memory);

void delete_Stack_Memory(Stack_Memory globale_Stack_Memory);

#endif /* end of include guard: _ALLOC_ */
