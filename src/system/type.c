#include "system/type.h"

#define MAX_TYPE_LEN 512
#define MAX_NUM_TYPES 1024

typedef char type_string[MAX_TYPE_LEN];
typedef size_t type_size;

static type_string type_names[MAX_NUM_TYPES];
static type_size type_sizes[MAX_NUM_TYPES];

static int type_index = 0;

int type_find(char* type, size_t size) {
    /* Ensure can enter type */
    if (type_index >= MAX_NUM_TYPES) {
        error("Too many types in type table already. Cannot add %s.", type);
    }
    if (strlen(type) >= MAX_TYPE_LEN) {
        error("Type name %s is too long to index into type table.", type);
    }
    /* Search Table for previous entry */
    for (int i = 0; i < type_index; i++) {
        if (strcmp(type, type_names[i]) == 0) {
            return i;
        }
    }
    /* Enter into Table */
    strcpy(type_names[type_index], type);
    type_sizes[type_index] = size;
    type_index++;
    return type_index-1;
}

char* type_id_name(int id) {
    return type_names[id];
}
