/*
Original Author: WeoBuXCS
email: freenitro.inc@gmail.com
Dynamic array. It is a C version of C++ vector*/
#pragma once
#include <stddef.h>
typedef struct Vector Vector;
#ifdef TESTING
    #define ref(x) *(x*)
#endif
#define INIT_CAPACITY 1
#define CAP_INCREASE 2
/*Implementation of struct Vector
struct Vector
{
    void* data;
    size_t length;
    size_t elemsize
};
Dynamic array constructer. It takes the array's size and the element's size*/

Vector* v_init_vector(size_t, size_t);

//Utils
//Generical functions. No matter what the datatype of each element is!
size_t v_len(Vector*);
int v_is_empty(Vector*);
int v_check_valid_index(Vector*, size_t);
size_t v_elemsize(Vector*);
int v_destroy(Vector*);
int v_clear(Vector*);
int v_append(Vector*, Vector*);
int v_delete(Vector*, size_t);
int v_pop_back(Vector*);
int v_resize(Vector*, size_t);
void* v_get_addr(Vector*, size_t);
void* v_data(Vector*);

//non-generic utils, default declare						
int v_push_backi(Vector*, int);
int v_seti(Vector*, size_t, int);
int v_ati(Vector*, size_t);
int v_inserti(Vector*, size_t, int);

