#include "stack_alloc.h"

// TODO Defrag!?

#ifdef DEBUG
#include <string.h>
#include <stdio.h>
#endif

Stack_Memory new_Stack_Memory(size_t size_Stack_Memory){
    Stack_Memory new_allocated_stack_memory = malloc(sizeof(struct sStackMemory));
    new_allocated_stack_memory->start_Stack_Memory = malloc(size_Stack_Memory);
    new_allocated_stack_memory->start_free_Stack_Memory = new_allocated_stack_memory->start_Stack_Memory;
    new_allocated_stack_memory->partition_Number = size_Stack_Memory;
    new_allocated_stack_memory->free_partitions = size_Stack_Memory;
    new_allocated_stack_memory->used_partitions = 0;
    new_allocated_stack_memory->chunk_Stack_Memory = malloc(sizeof(partition) * new_allocated_stack_memory->partition_Number);
    for (size_t i = 0; i < new_allocated_stack_memory->partition_Number; ++i) {
        new_allocated_stack_memory->chunk_Stack_Memory[i].start_partition = NULL;
        new_allocated_stack_memory->chunk_Stack_Memory[i].size_partition = 0;
    }
    new_allocated_stack_memory->size_Stack_Memory = size_Stack_Memory;
    new_allocated_stack_memory->size_free_Stack_Memory = size_Stack_Memory;
    return new_allocated_stack_memory;
}

void resize_Stack_Memory(Stack_Memory globale_Stack_Memory, size_t size_Stack_Memory){
    globale_Stack_Memory->start_Stack_Memory = realloc(globale_Stack_Memory->start_Stack_Memory, size_Stack_Memory);
    globale_Stack_Memory->chunk_Stack_Memory = realloc(globale_Stack_Memory->chunk_Stack_Memory, sizeof(partition) * (globale_Stack_Memory->partition_Number + size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory));
    for (size_t i = globale_Stack_Memory->partition_Number; i < globale_Stack_Memory->partition_Number + size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory; ++i) {
        globale_Stack_Memory->chunk_Stack_Memory[i].start_partition = NULL;
        globale_Stack_Memory->chunk_Stack_Memory[i].size_partition = 0;
    }
    globale_Stack_Memory->partition_Number += size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory;
    globale_Stack_Memory->free_partitions += size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory;
    globale_Stack_Memory->size_free_Stack_Memory += size_Stack_Memory - globale_Stack_Memory->size_Stack_Memory;
    globale_Stack_Memory->size_Stack_Memory = size_Stack_Memory;
}

void* Stack_Memory_Alloc(Stack_Memory globale_Stack_Memory, size_t size){
    size_t i = 0;
    if (size > globale_Stack_Memory->size_free_Stack_Memory) return NULL;
    while (globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) ++i;
    globale_Stack_Memory->chunk_Stack_Memory[i].start_partition = globale_Stack_Memory->start_free_Stack_Memory;
    globale_Stack_Memory->chunk_Stack_Memory[i].size_partition = size;
    globale_Stack_Memory->free_partitions -= size - 1;
    ++globale_Stack_Memory->used_partitions;
    globale_Stack_Memory->start_free_Stack_Memory = (char*)globale_Stack_Memory->start_free_Stack_Memory + size;
    globale_Stack_Memory->size_free_Stack_Memory -= size;
    return globale_Stack_Memory->chunk_Stack_Memory[i].start_partition;
}

void* Stack_Memory_Realloc(Stack_Memory globale_Stack_Memory, size_t size){
    size_t i = 0;
    while (i <= globale_Stack_Memory->partition_Number && globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) ++i;
    if(!i) return Stack_Memory_Alloc(globale_Stack_Memory, size);
    if(i > globale_Stack_Memory->partition_Number)
        resize_Stack_Memory(globale_Stack_Memory, globale_Stack_Memory->size_Stack_Memory + globale_Stack_Memory->size_Stack_Memory/2);
    globale_Stack_Memory->size_free_Stack_Memory += globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition - size;
    globale_Stack_Memory->free_partitions += globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition - size;
    globale_Stack_Memory->start_free_Stack_Memory = (char*)globale_Stack_Memory->start_free_Stack_Memory - globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition;
    globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition = size;
    return globale_Stack_Memory->chunk_Stack_Memory[i-1].start_partition;
}

void Stack_Memory_Free(Stack_Memory globale_Stack_Memory){
    size_t i = 0;
    while (i <= globale_Stack_Memory->partition_Number && globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) ++i;
    if(!i) return;
    globale_Stack_Memory->size_free_Stack_Memory += globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition;
    globale_Stack_Memory->free_partitions += globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition - 1;
    --globale_Stack_Memory->used_partitions;
    globale_Stack_Memory->start_free_Stack_Memory = (char*)globale_Stack_Memory->start_free_Stack_Memory - globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition;
    globale_Stack_Memory->chunk_Stack_Memory[i-1].size_partition = 0;
    globale_Stack_Memory->chunk_Stack_Memory[i-1].start_partition = NULL;
}

void delete_Stack_Memory(Stack_Memory globale_Stack_Memory){
    free(globale_Stack_Memory->chunk_Stack_Memory);
    free(globale_Stack_Memory->start_Stack_Memory);
    free(globale_Stack_Memory);
}

#ifdef DEBUG

void displayMemory(Stack_Memory globale_Stack_Memory){
    for (size_t i = 0; i < globale_Stack_Memory->partition_Number; i++) {
        if (globale_Stack_Memory->chunk_Stack_Memory[i].start_partition) {
            printf("%2X | ", (char *)globale_Stack_Memory->chunk_Stack_Memory[i].start_partition);
            for (size_t j = 0; j < globale_Stack_Memory->chunk_Stack_Memory[i].size_partition; j++) {
                printf("%2X ", *((char *)globale_Stack_Memory->chunk_Stack_Memory[i].start_partition + j));
            }
            printf("| %zu\n", globale_Stack_Memory->chunk_Stack_Memory[i].size_partition);
        }
    }
    printf("Free_Memory_Size %zu partition_Number %zu (free %zu/used %zu)\n", globale_Stack_Memory->size_free_Stack_Memory, globale_Stack_Memory->partition_Number, globale_Stack_Memory->free_partitions, globale_Stack_Memory->used_partitions);
}

int main(int argc, char const *argv[]) {
    int choix, index = 0, *number = NULL, cste_int = 1;
    long *big_number = NULL;
    float *real = NULL, cste_real = 0.1;
    char *str = NULL;
    Stack_Memory work_space = new_Stack_Memory(2 * Memory_1Ko); // 2048 octets
    while (1) {
        printf("Free_Memory_Size %zu\n\n", work_space->size_free_Stack_Memory);
        displayMemory(work_space);
        printf("\t1: Alloc int\n");
        printf("\t2: Alloc string\n");
        printf("\t3: Alloc real\n");
        printf("\t4: Realloc to long\n");
        printf("\t5: free\n");
        printf("\n\tChoix: ");
        scanf("%d",&choix);
        fgetc(stdin);
        switch (choix) {
            case 1:
                number = Stack_Memory_Alloc(work_space, sizeof(int));
                *number = cste_int;
                printf("int = %d at %X\n", *number, number);
                ++cste_int;
                ++index;
                break;
            case 2:
                str = Stack_Memory_Alloc(work_space, strlen("Hello world!"));
                strcpy(str,"Hello world!");
                printf("str = %s at %X\n", str, str);
                ++index;
                break;
            case 3:
                real = Stack_Memory_Alloc(work_space, sizeof(float));
                *real = cste_real;
                printf("real = %f at %X\n", *real, real);
                cste_real = cste_real * (cste_real + cste_int) + cste_int;
                ++index;
                break;
            case 4:
                big_number = Stack_Memory_Realloc(work_space, sizeof(long));
                *big_number = cste_int * 1234;
                printf("long = %ld at %X\n", *big_number, big_number);
                ++cste_int;
                break;
            case 5:
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
}
#endif
