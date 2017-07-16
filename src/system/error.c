#include "system/error.h"

typedef void (*error_func_t)(const char*);
typedef void (*warn_func_t)(const char*);
typedef void (*debug_func_t)(const char*);

#define MAX_AT_FUNCS 32
static error_func_t error_funcs[MAX_AT_FUNCS];
static warn_func_t warn_funcs[MAX_AT_FUNCS];
static debug_func_t debug_funcs[MAX_AT_FUNCS];

static int num_error_funcs = 0;
static int num_warn_funcs = 0;
static int num_debug_funcs = 0;

void at_error(void(*func)(const char*)) {
    if (num_error_funcs == MAX_AT_FUNCS) {
        warning("Cannot register more than maximum of %i error functions", MAX_AT_FUNCS);
        return;
    }
    error_funcs[num_error_funcs] = (error_func_t)func;
    num_error_funcs++;
}

void at_warning(void(*func)(const char*)) {
    if (num_warn_funcs == MAX_AT_FUNCS) {
        warning("Cannot register more than maximum of %i warning functions", MAX_AT_FUNCS);
        return;
    }
    warn_funcs[num_warn_funcs] = (warn_func_t)func;
    num_warn_funcs++;
}

void at_debug(void(*func)(const char*)) {
    if (num_debug_funcs == MAX_AT_FUNCS) {
        warning("Cannot register more than maximum of %i debug functions", MAX_AT_FUNCS);
        return;
    }
    debug_funcs[num_debug_funcs] = (debug_func_t)func;
    num_debug_funcs++;
}

void error_(const char* str) {
    for (int i = 0; i < num_error_funcs; i++) {
        error_funcs[i](str);
    }
}

void warning_(const char* str) {
    for (int i = 0; i < num_warn_funcs; i++) {
        warn_funcs[i](str);
    }
}

void debug_(const char* str) {
    for (int i = 0; i < num_debug_funcs; i++) {
        debug_funcs[i](str);
    }
}
