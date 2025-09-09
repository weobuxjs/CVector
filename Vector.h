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
Vector's constructer. It takes the array's size and the element's size and return the pointer of 
the object Vector*/

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

//non-generic utils for primitive data type
#ifndef POINTER_GENERIC
//fast declaring macro
#define CONCAT(A, B) A ## B
#define PROTOTYPE(type, suffix) \
int CONCAT(v_push_back, suffix)(Vector*, type); \
int CONCAT(v_set, suffix)(Vector*, size_t, type); \
type CONCAT(v_at, suffix)(Vector*, size_t); \
int CONCAT(v_insert, suffix)(Vector*, size_t, type);


char v_atc(Vector*, size_t); 
int v_setc(Vector*, size_t, char); 
int v_push_backc(Vector*, char); 
int v_insertc(Vector*, size_t, char);

short v_ats(Vector*, size_t); 
int v_sets(Vector*, size_t, short); 
int v_push_backs(Vector*, short); 
int v_inserts(Vector*, size_t, short);

int v_ati(Vector*, size_t); 
int v_seti(Vector*, size_t, int); 
int v_push_backi(Vector*, int); 
int v_inserti(Vector*, size_t, int);

long long v_atll(Vector*, size_t); 
int v_setll(Vector*, size_t, long long); 
int v_push_backll(Vector*, long long); 
int v_insertll(Vector*, size_t, long long);

float v_atf(Vector*, size_t); 
int v_setf(Vector*, size_t, float); 
int v_push_backf(Vector*, float); 
int v_insertf(Vector*, size_t, float);

double v_atd(Vector*, size_t); 
int v_setd(Vector*, size_t, double); 
int v_push_backd(Vector*, double); 
int v_insertd(Vector*, size_t, double);


long double v_atld(Vector*, size_t); 
int v_setld(Vector*, size_t, long double); 
int v_push_backld(Vector*, long double); 
int v_insertld(Vector*, size_t, long double);

unsigned int v_atui(Vector*, size_t);
int v_setui(Vector*, size_t, unsigned int); 
int v_push_backui(Vector*, unsigned int);  
int v_insertui(Vector*, size_t, unsigned int);

unsigned long long v_atull(Vector*, size_t); 
int v_setull(Vector*, size_t, unsigned long long); 
int v_push_backull(Vector*, unsigned long long); 
int v_insertull(Vector*, size_t, unsigned long long);

unsigned char v_atuc(Vector*, size_t); 
int v_push_backuc(Vector*, unsigned char); 
int v_setuc(Vector*, size_t, unsigned char); 
int v_insertuc(Vector*, size_t, unsigned char);

#else
int v_at(Vector*, size_t, void*);
int v_set(Vector*, size_t, void*);
int v_push_back(Vector*, void*);
int v_insert(Vector*, size_t, void*);
#endif