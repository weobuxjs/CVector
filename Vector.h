/*
Original Author: WeoBuXCS
email: freenitro.inc@gmail.com
Dynamic array. It is a C version of C++ vector*/
#pragma once

typedef unsigned long long size_t;
typedef struct Vector Vector;
#ifdef TESTING
    #define ref(x) *(x*)
#endif
/*Implementation of struct Vector
struct Vector
{
    void* data;
    size_t length;
    unsigned int elementSize;
};
Dynamic array constructer. It takes the array's size and the element's size*/

Vector* init_vector(size_t, size_t);

//Utils
//Generical functions. No matter what the datatype of each element is!
/*Get the length of the dynamic array*/
size_t len(Vector*);
/*Check the dynamic array is empty or not. If yes, it returns true. Otherwise false*/
int is_empty(Vector*);
/*Check the index is in bound of Dynamic array or not*/
int check_valid_index(Vector*, size_t);
/*Get the size in bytes of each element*/
size_t elemsize(Vector*);
/*Destroy the array*/
int destroy(Vector*);
/*Empty the array*/
int empty(Vector*);
/*Append the src into dst*/
int append(Vector*, Vector*);
/*Remove an element in the dynamic array determinated with specific index*/
int delete(Vector*, size_t);
/*remove the last element */
int pop_back(Vector*);
/*Resize the array*/
int resize(Vector*, size_t);
/*Get the address of a element*/
void* get_addr(Vector*, size_t);

// These functions the users may have to implement a new datatype-driven version of it. Here is the default case
/*Add a nem element to the end of the dynamic array*/
int push_backi(Vector*, int);
/*Set the element's value at the specific index of the dynamic array to another value*/
int seti(Vector*, size_t, int);
/*Get the value of the dynamic array with specific index */
int ati(Vector*, size_t);
/*Insert an element in the array*/
int inserti(Vector*, size_t, int);

