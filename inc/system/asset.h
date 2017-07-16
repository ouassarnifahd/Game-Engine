#ifndef _ASSET_
#define _ASSET_

#include "common.h"
#include "system/path.h"
#include "system/type.h"

typedef void Asset;

typedef struct {
    fpath path;
    Asset* ptr;
    uint32_t timestamp;
} Asset_handle;

Asset_handle asset_hndl_null(void);
Asset_handle asset_hndl_new(fpath path);
Asset_handle asset_hndl_new_load(fpath path);
Asset_handle asset_hndl_new_ptr(Asset* asset);

bool asset_hndl_isnull(Asset_handle* ah);
fpath asset_hndl_path(Asset_handle* ah);
Asset* asset_hndl_ptr(Asset_handle* ah);
bool asset_hndl_eq(Asset_handle* ah0, Asset_handle* ah1);

void asset_cache_flush(void);

/* Init and Finish operations */
void asset_init(void);
void asset_finish(void);

/* Map a variable such as '$CORANGE' to a path string */
void asset_add_path_variable(fpath variable, fpath mapping);

fpath asset_map_filename(fpath filename);
fpath asset_unmap_filename(fpath filename);

/* Create handler for asset type. Requires type, file extension, and load/unload functions. */
#define asset_handler(type, extension, loader, deleter) \
  asset_handler_cast(typeid(type), extension, \
  (Asset*(*)(const char*))loader , \
  (Asset(*)(void*))deleter)

void asset_handler_cast(type_id type, const char* extension,
                        Asset* asset_loader(const char* filename),
                        void asset_deleter(Asset* asset));

/* Load/Reload/Unload assets at path or folder */
void file_load(fpath filename);
void file_unload(fpath filename);
void file_reload(fpath filename);
bool file_isloaded(fpath path);
bool file_exists(fpath path);

void folder_load(fpath folder);
void folder_unload(fpath folder);
void folder_reload(fpath folder);
void folder_load_recursive(fpath folder);

Asset* asset_get_load(fpath path);
Asset* asset_get(fpath path);

#define asset_get_as(path, type) ((type*)asset_get_as_type(path, typeid(type)))
Asset* asset_get_as_type(fpath path, type_id type);

/* Reload all assets of a given type */
#define asset_reload_type(type) asset_reload_type_id(typeid(type))
void asset_reload_type_id(type_id type);
void asset_reload_all(void);

/* Get path or typename of asset at ptr */
char* asset_ptr_path(Asset* asset);
char* asset_ptr_typename(Asset* asset);

#endif /* end of include guard: _ASSET_ */
