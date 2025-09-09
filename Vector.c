#include "Vector.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
struct Vector
{
    void* data;
    size_t length;
    size_t capacity;  
    size_t elemsize;  
};
Vector* v_init_vector(size_t size, size_t element_size)
{
    Vector* arr = (Vector*)malloc(sizeof(Vector));
    size_t calloc_size = (size <= INIT_CAPACITY ? INIT_CAPACITY : size * CAP_INCREASE);
    arr->data = calloc(calloc_size, element_size);
    arr->elemsize = element_size;
    arr->length = 0;
    arr->capacity = 0;
    if(arr->data)
    {
        arr->length = size;
        arr->capacity = calloc_size;
    }
    return arr;
}
// internal functions
// This function adjusts capacity depending on new length (or wanted length)
static int adjust_cap(Vector* arr, size_t new_length)
{
    if(new_length == arr->capacity)
    {
        return 1;
    }
    size_t nearest_cap;
    if(!new_length)
    {
        nearest_cap = 1;
    }
    else 
    {
        nearest_cap = (size_t) pow(2, ceill(log2(new_length)));
    }
    void* new_data = realloc(arr->data, nearest_cap * arr->elemsize);
    if(!new_data)
    {
        return 0;
    }
    arr->data = new_data;
    arr->capacity = nearest_cap;   
    return 1;
}
// if condition is FALSE, then it will output error_msg and terminate the program
static void v_assert(int condition, const char* error_msg)
{
    if(condition <= 0)
    {
        puts(error_msg);
        exit(EXIT_FAILURE);  
    }
}
//Utils
size_t v_len(Vector* arr)
{
    return arr->length;
}
int v_is_empty(Vector* arr)
{
    if(arr->length == 0)
    {
        return 1;
    }
    return 0;
}
int v_check_valid_index(Vector* arr, size_t index)
{
    if(index >= arr->length)
    {
        return 0;
    }
    return 1;
}
size_t v_elemsize(Vector* arr)
{
    return arr->elemsize;
}
int v_destroy(Vector* arr)
{
   free(arr->data);
   free((void*)arr);
   return 1;
}
int v_clear(Vector* arr)
{
    arr->length = 0;
    // free(arr->data);
    return 1;
}
int v_append(Vector* arr1, Vector* arr2)
{
    if(arr1->elemsize != arr2->elemsize)
    {
        return 0;
    }
    size_t old_len = arr1->length;        
    if(!v_resize(arr1, arr1->length + arr2->length))
    {
        return 0;
    }
    void* dst = (char*)arr1->data + arr1->elemsize * old_len;
    void* src = arr2->data;
    size_t bytes_to_move = arr2->elemsize * arr2->length;
    memmove(dst, src, bytes_to_move);
    return 1; // honestly i don't know the status of the function memove;
}
int v_delete(Vector* arr, size_t index)
{
    if(v_is_empty(arr) || !v_check_valid_index(arr, index))
    {
        return 0;
    }
    if(index < arr->length - 1)
    {
        void* dst = (char*)arr->data + index * arr->elemsize;
        void* src = (char*)arr->data + (index + 1) * arr->elemsize;
        size_t bytes_to_move = (arr->length  - 1 - index) * arr->elemsize;
        memmove(dst, src, bytes_to_move);
    }
    v_pop_back(arr);
    return 1;
}
int v_pop_back(Vector* arr)
{
    if(arr->length == 0)
    {
        return 0;
    }
    arr->length--;
    return 1;
}
int v_resize(Vector* arr, size_t nums_ele)
{
    if(nums_ele > arr->capacity)
    {
        if(!adjust_cap(arr, nums_ele))
        {
            return 0;
        }
    }
    arr->length = nums_ele;
    return 1;
}
void* v_get_addr(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return NULL;
    }
    return (char*)arr->data + index * arr->elemsize;
}
void* v_data(Vector* arr)
{
    return arr->data;
}
// Non-generical functions.
#ifndef POINTER_GENERIC
//char
char v_atc(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    char* data = (char*)arr->data;
    return data[index]; 
}
int v_setc(Vector* arr, size_t index, char value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }
    void* dst = (char*)arr->data + index * arr->elemsize;
    memcpy(dst, &value, arr->elemsize);
    return 1;
}
int v_push_backc(Vector* arr, char value)
{
    if(arr->length == arr->capacity)
    {
        if(!adjust_cap(arr, arr->length + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_setc(arr, arr->length - 1, value);
    return 1;  
}
int v_insertc(Vector* arr, size_t index, char value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == arr->length)
    {
        v_push_backc(arr, value);
        return 1;
    }  
    if(!v_resize(arr, arr->length + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (arr->length - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_seti(arr, index, value);
    return 1;
}
//short
short v_ats(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    short* data = (short*)arr->data;
    return data[index];
}
int v_sets(Vector* arr, size_t index, short value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }
    void* dst = (char*)arr->data + index * arr->elemsize;
    memcpy(dst, &value, arr->elemsize);
    return 1;
}
int v_push_backs(Vector* arr, short value)
{
    if(arr->length == arr->capacity)
    {
        if(!adjust_cap(arr, arr->length + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_sets(arr, arr->length - 1, value);
    return 1;   
}
int v_inserts(Vector* arr, size_t index, short value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == arr->length)
    {
        v_push_backs(arr, value);
        return 1;
    }  
    if(!v_resize(arr, arr->length + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (arr->length - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_sets(arr, index, value);
    return 1;
}
//int
int v_ati(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    int* data = (int*)arr->data;
    return data[index];
}
int v_seti(Vector* arr, size_t index, int value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }
    void* dst = (char*)arr->data + index * arr->elemsize;
    memcpy(dst, &value, arr->elemsize);
    return 1;
}
int v_push_backi(Vector* arr, int value)
{
    if(arr->length == arr->capacity)
    {
        if(!adjust_cap(arr, arr->length + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_seti(arr, arr->length - 1, value);
    return 1;
}
int v_inserti(Vector* arr, size_t index, int value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == arr->length)
    {
        v_push_backi(arr, value);
        return 1;
    }  
    if(!v_resize(arr, arr->length + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (arr->length - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_seti(arr, index, value);
    return 1;
}
//float
float v_atf(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    float* data = (float*)arr->data;
    return data[index];
}
int v_setf(Vector* arr, size_t index, float value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }
    void* dst = (char*)arr->data + index * arr->elemsize;
    memcpy(dst, &value, arr->elemsize);
    return 1;
}
int v_push_backf(Vector* arr, float value)
{
    if(arr->length == arr->capacity)
    {
        if(!adjust_cap(arr, arr->length + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_setf(arr, arr->length - 1, value);
    return 1;
}
int v_insertf(Vector* arr, size_t index, float value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == arr->length)
    {
        v_push_backf(arr, value);
        return 1;
    }  
    if(!v_resize(arr, arr->length + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (arr->length - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_setf(arr, index, value);
    return 1;
}
// long long
long long v_atll(Vector* arr, size_t index)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    long long* data = (long long*)arr->data;
    return data[index];
}
#else
int v_at(Vector* arr, size_t index, void* ret_ptr)
{
    if(!v_check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    ret_ptr = (char*)arr->data + arr->elemsize * index; 
    return 1;
}
int v_set(Vector* arr, size_t index, void* value_ptr)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }
    void* dst = (char*)arr->data + index * arr->elemsize;
    memcpy(dst, value_ptr, arr->elemsize);
    return 1;
}
int v_push_back(Vector* arr, void* value_ptr)
{
    if(arr->length == arr->capacity)
    {
        if(!adjust_cap(arr, arr->length + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_set(arr, arr->length - 1, value_ptr);
    return 1;
}
int v_insert(Vector* arr, size_t index, void* value_ptr)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == arr->length)
    {
        v_push_back(arr, value_ptr);
        return 1;
    }  
    if(!v_resize(arr, arr->length + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (arr->length - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_set(arr, index, value_ptr);
    return 1;
}
#endif