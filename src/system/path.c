#include "system/path.h"

fpath P(const char* path) {
    fpath p = {};
    if (unlikely(strlen(path) >= PATH_MAX)) {
        error("Path too long '%s'", path);
    } else {
        strcpy(p.ptr, path);
    }
    return p;
}

fpath fpath_full(fpath path) {
    fpath ret;
    SDL_PathFullName(ret.ptr, path.ptr);
    return ret;
}

fpath fpath_file(fpath path) {
    fpath ret;
    SDL_PathFileName(ret.ptr, path.ptr);
    return ret;
}

fpath fpath_file_location(fpath path) {
    fpath ret;
    SDL_PathFileLocation(ret.ptr, path.ptr);
    return ret;
}

fpath fpath_file_extension(fpath path) {
    fpath ret;
    SDL_PathFileExtension(ret.ptr, path.ptr);
    return ret;
}
