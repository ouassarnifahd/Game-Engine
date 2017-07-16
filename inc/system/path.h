#ifndef _PATH_
#define _PATH_

#include "common.h"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

typedef struct {
  char ptr[MAX_PATH];
} fpath;

fpath P(const char* path);

fpath fpath_full(fpath path);
fpath fpath_file(fpath path);
fpath fpath_file_location(fpath path);
fpath fpath_file_extension(fpath path);

#endif /* end of include guard: _PATH_ */
