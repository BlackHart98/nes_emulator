#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"



void utils_dyn_array_append(utils_dyn_array_t * dyn_array, uint8_t item){
    if ((dyn_array->count + 1) > dyn_array->capacity){
        // double the array size
        dyn_array->buffer = realloc(dyn_array->buffer, 2 * dyn_array->capacity + 1);
        if (dyn_array == NULL) return;
    } 
    dyn_array->buffer[dyn_array->count++] = item;
}


extern uint8_t utils_dyn_array_get_index(const utils_dyn_array_t * dyn_array, size_t index){
    assert((index < dyn_array->capacity)&&"Index to big");
    return dyn_array->buffer[index];
}

extern void utils_dyn_array_set_index(utils_dyn_array_t * dyn_array, size_t index, uint8_t item){
    assert((index < dyn_array->capacity)&&"Index to big");
    dyn_array->buffer[index] = item;
    if (index >= dyn_array->count) 
        dyn_array->count = index + 1;
}


void utils_dyn_array_destroy(utils_dyn_array_t * dyn_array){
    if (dyn_array->buffer != NULL){
        free(dyn_array->buffer);
        dyn_array->buffer = NULL;
        dyn_array->capacity = 0;
    }
}


int utils_dyn_array_init(utils_dyn_array_t * dyn_array, size_t init_size){
#if defined(DEBUG)
    assert((init_size != 0)&&"array initializatio size should be > 0!")
#endif
    uint8_t * buffer = (uint8_t *) malloc(init_size);
    if (buffer == NULL) return 0;
    memset(buffer, 0, init_size);

    dyn_array->buffer = buffer;
    dyn_array->count = 0;
    dyn_array->capacity = init_size;
    return 1;
}