#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdlib.h>

// You can almost never having constraints 
// implement a dynamic linear array with slice function
typedef struct _utils_dyn_array_t{
    size_t capacity;
    size_t count;
    uint8_t * buffer;
} utils_dyn_array_t;


typedef struct _utils_array_view_t{
    uint8_t * view;
    size_t capacity;
} utils_array_view_t;

extern utils_dyn_array_t utils_dyn_array_init(size_t init_size);
extern void utils_dyn_array_append(utils_dyn_array_t * dyn_array, uint8_t item);
extern uint8_t utils_dyn_array_get_index(const utils_dyn_array_t * dyn_array, size_t index);
extern void utils_dyn_array_set_index(utils_dyn_array_t * dyn_array, size_t index, uint8_t item);
extern void utils_dyn_array_pop(utils_dyn_array_t * dyn_array);
extern void utils_dyn_array_destroy(utils_dyn_array_t * dyn_array);




#endif /* _UTILS_H */