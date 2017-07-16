#ifndef _TYPE_
#define _TYPE_

#include "common.h"

typedef int type_id;

#define typeid(TYPE) type_find(#TYPE, sizeof(TYPE))
type_id type_find(char* type, size_t size);
char* type_id_name(int id);

#endif /* end of include guard: _TYPE_ */
