#include "stack_alloc.h"

// TODO MemFree, MemRealloc memfrag!!

#ifdef DEBUG
#include <string.h>
#include <stdio.h>
#endif

Stack_Memory new_Stack_Memory(size_t size_Stack_Memory, size_t partition_Number){
    Stack_Memory new_allocated_stack_memory = malloc(sizeof(struct sStackMemory));
    new_allocated_stack_memory->start_Stack_Memory = malloc(size_Stack_Memory);
    new_allocated_stack_memory->partition_Number = partition_Number;
    new_allocated_stack_memory->chunk_Stack_Memory = malloc(sizeof(partition) * partition_Number);
    for (size_t i = 0; i < partition_Number; ++i) {
        new_allocated_stack_memory->chunk_Stack_Memory[i].start_partition = NULL;
        new_allocated_stack_memory->chunk_Stack_Memory[i].size_partition = 0;
    }
    new_allocated_stack_memory->chunk_Stack_Memory[0].start_partition = new_allocated_stack_memory->start_Stack_Memory;
    new_allocated_stack_memory->size_Stack_Memory = size_Stack_Memory;
    new_allocated_stack_memory->size_free_Stack_Memory = size_Stack_Memory;
    return new_allocated_stack_memory;
}

void resize_Stack_Memory(Stack_Memory globale_Stack_Memory, size_t size_Stack_Memory, size_t partition_Number){
    globale_Stack_Memory->start_Stack_Memory = realloc(globale_Stack_Memory->start_Stack_Memory, size_Stack_Memory);
    globale_Stack_Memory->chunk_Stack_Memory = realloc(globale_Stack_Memory->chunk_Stack_Memory, sizeof(partition) * partition_Number);
    if (partition_Number > globale_Stack_Memory->partition_Number) {
        for (size_t i = globale_Stack_Memory->partition_Number; i < partition_Number; ++i) {
            globale_Stack_Memory->chunk_Stack_Memory[i].start_partition = NULL;
            globale_Stack_Memory->chunk_Stack_Memory[i].size_partition = 0;
        }
    }
    globale_Stack_Memory->partition_Number = partition_Number;
    globale_Stack_Memory->size_free_Stack_Memory += size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory;
    globale_Stack_Memory->size_Stack_Memory = size_Stack_Memory;

}

void* Stack_Memory_Alloc(Stack_Memory globale_Stack_Memory, size_t size){
    size_t i = 0;
    if (size > globale_Stack_Memory->size_free_Stack_Memory) return NULL;
    void* memory = NULL;
    while (globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) ++i;
    memory = globale_Stack_Memory->chunk_Stack_Memory[i-1].start_partition;
    globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition = size;
    while (globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) ++i;
    globale_Stack_Memory->chunk_Stack_Memory[i].start_partition = (char*)memory + size;
    globale_Stack_Memory->size_free_Stack_Memory -= size;
    return memory;
}

void* Stack_Memory_Realloc(Stack_Memory globale_Stack_Memory, size_t size){
    size_t i = 0;
    while (globale_Stack_Memory->chunk_Stack_Memory[i].size_partition) ++i;
    if(i) {
        globale_Stack_Memory->size_free_Stack_Memory += globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition - size;
        globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition = size;
        return globale_Stack_Memory->chunk_Stack_Memory[i-1].start_partition;
    } else {
        globale_Stack_Memory->size_free_Stack_Memory += globale_Stack_Memory->chunk_Stack_Memory[i].size_partition - size;
        globale_Stack_Memory->chunk_Stack_Memory[i].size_partition = size;
        return globale_Stack_Memory->chunk_Stack_Memory[i].start_partition;
    }
}

void Stack_Memory_Free(Stack_Memory globale_Stack_Memory){
    Stack_Memory_Realloc(globale_Stack_Memory,0);
}

void delete_Stack_Memory(Stack_Memory globale_Stack_Memory){
    free(globale_Stack_Memory->chunk_Stack_Memory);
    free(globale_Stack_Memory->start_Stack_Memory);
    free(globale_Stack_Memory);
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {
    int choix, index = 0;
    Stack_Memory work_space = new_Stack_Memory(100, 10); // 100 octets, 10 partitions
    while (1) {
        printf("Free_Memory_Size %zu\n\n", work_space->size_free_Stack_Memory);
        printf("\t1: Alloc int\n");
        printf("\t2: Alloc string\n");
        printf("\t3: Alloc real\n");
        printf("\t4: free\n");
        printf("\n\tChoix: ");
        scanf("%d\n",&choix);
        switch (choix) {
            case 1:
                int* number = Stack_Memory_Alloc(work_space, sizeof(int));
                *number = 8;
                printf("int = %d at %X size partition %zu\n", *number, number, work_space->chunk_Stack_Memory[index].size_partition);
                ++index;
                break;
            case 2:
                char* str = Stack_Memory_Alloc(work_space, strlen("Hello world!"));
                strcpy(str,"Hello world!");
                printf("str = %s at %X size partition %zu\n", str, str, work_space->chunk_Stack_Memory[index].size_partition);
                ++index;
                break;
            case 3:
                float* real = Stack_Memory_Realloc(work_space, sizeof(float));
                *real = 2.3;
                printf("real = %f at %X size partition %zu\n", *real, real, work_space->chunk_Stack_Memory[index].size_partition);
                ++index;
                break;
            case 4:
                Stack_Memory_Free(work_space);
                --index;
                break;
            case 0:
                delete_Stack_Memory(work_space);
                return 0;
            default:
                printf("invalid!\n");
        }

    }
    // float* real1 = Stack_Memory_Realloc(work_space, sizeof(float));
    // *real1 = 2.97;
    // printf("real = %f at %zu size partition %zu\n", *real1, (size_t)real1, work_space->chunk_Stack_Memory[2].size_partition);
    // printf("free Memory size %zu\n", work_space->size_free_Stack_Memory);
    return 0;
}
#endif
