#include "Vector.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
static int adjust_cap(Vector* arr, size_t elemsize)
{
    if(elemsize == arr->capacity)
    {
        return 1;
    }
    size_t nearest_cap;
    if(!elemsize)
    {
        nearest_cap = 1;
    }
    else 
    {
        nearest_cap = (size_t) pow(2, ceill(log2(elemsize)));
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
//Utils
size_t v_len(Vector* arr)
{
    return arr->length;
}
int v_is_empty(Vector* arr)
{
    if(v_len(arr) == 0)
    {
        return 1;
    }
    return 0;
}
int v_check_valid_index(Vector* arr, size_t index)
{
    if(index >= v_len(arr))
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
    size_t old_len = v_len(arr1);        
    if(!v_resize(arr1, v_len(arr1) + v_len(arr2)))
    {
        return 0;
    }
    void* dst = (char*)arr1->data + arr1->elemsize * old_len;
    void* src = arr2->data;
    size_t bytes_to_move = arr2->elemsize * v_len(arr2);
    memmove(dst, src, bytes_to_move);
    return 1; // honestly i don't know the status of the function memove;
}
int v_delete(Vector* arr, size_t index)
{
    if(v_is_empty(arr) || !v_check_valid_index(arr, index))
    {
        return 0;
    }
    if(index < v_len(arr) - 1)
    {
        void* dst = (char*)arr->data + index * arr->elemsize;
        void* src = (char*)arr->data + (index + 1) * arr->elemsize;
        size_t bytes_to_move = (v_len(arr)  - 1 - index) * arr->elemsize;
        memmove(dst, src, bytes_to_move);
    }
    v_pop_back(arr);
    return 1;
}
int v_pop_back(Vector* arr)
{
    if(v_len(arr) == 0)
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
// Non-generical functions. Default implement.
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
    memcpy(dst, &value, sizeof(value));
    return 1;
}
int v_push_backi(Vector* arr, int value)
{
    if(v_len(arr) == arr->capacity)
    {
        if(!adjust_cap(arr, v_len(arr) + 1))
        {
            return 0;
        }
    }
    arr->length++;
    v_seti(arr, v_len(arr) - 1, value);
    return 1;
}
int v_inserti(Vector* arr, size_t index, int value)
{
    if(!v_check_valid_index(arr, index))
    {
        return 0;
    }    
    if(index == v_len(arr))
    {
        v_push_backi(arr, value);
        return 1;
    }  
    if(!v_resize(arr, v_len(arr) + 1))
    {
        return 0;
    } 
    void* dst = (char*)arr->data + (index + 1) * arr->elemsize;
    void* src = (char*)arr->data + index * arr->elemsize;
    size_t bytes_to_move = (v_len(arr) - 1 - index) * arr->elemsize;       
    memmove(dst, src, bytes_to_move);
    v_seti(arr, index, value);
    return 1;
}
