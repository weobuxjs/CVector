#include "Vector.h"
#include <stdlib.h>
#include <string.h>
struct Vector
{
    void* data;
    size_t length;  
    size_t elemsize;  
};
Vector* init_vector(size_t size, size_t element_size)
{
    Vector* arr = (Vector*)malloc(sizeof(Vector));
    arr->data = calloc(size, element_size);
    arr->elemsize = element_size;
    arr->length = 0;
    if(arr->data)
    {
        arr->length = size;
    }
    return arr;
}
size_t len(Vector* arr)
{
	if(!arr)
	{
		return 0;
	}
    return arr->length;
}
int is_empty(Vector* arr)
{
    if(arr && len(arr) == 0)
    {
        return 1;
    }
    return 0;
}
int check_valid_index(Vector* arr, size_t index)
{
	if(!arr)
	{
		return 0;	
	}
    if(index < 0 || index >= len(arr))
    {
        return 0;
    }
    return 1;
}
size_t elemsize(Vector* arr)
{
	if(!arr)
	{
		return 0;
	}
    return arr->elemsize;
}
int destroy(Vector* arr)
{
   if(!arr)
   {
		return 0;
   }
   free(arr->data);
   free((void*)arr);
   return 1;
}
int empty(Vector* arr)
{
	if(!arr)
	{
		return 0;
	}
    arr->length = 0;
    free(arr->data);
    return 1;
}
int append(Vector* arr1, Vector* arr2)
{
	if(!arr1 || !arr2)
	{
		return 0;
	}
    if(arr1->elemsize != arr2->elemsize)
    {
        return 0;
    }
    if(!resize(arr1, len(arr1) + len(arr2)))
    {
        return 0;
    }
    memmove(arr1->data + arr1->elemsize * len(arr1), arr2->data, len(arr2) * arr2->elemsize);
    return 1; // honestly i don't know the status of the function memove;
}
int delete(Vector* arr, size_t index)
{
    if(is_empty(arr) || !check_valid_index(arr, index))
    {
        return 0;
    }
    if(index < len(arr) - 1)
    {
        void* dst = arr->data + index * arr->elemsize;
        void* src = arr->data + (index + 1) * arr->elemsize;
        size_t bytes_to_move = (len(arr)  - 1 - index) * arr->elemsize;
        memmove(dst, src, bytes_to_move);
    }
    pop_back(arr);
    return 1;
}
int pop_back(Vector* arr)
{
    if(!arr)
    {
        return 0;
    }
    void* errChecking = realloc(arr->data, arr->elemsize * (len(arr) - 1));
    if(!errChecking)
    {
        return 0;
    }
    arr->data = errChecking;
    arr->length--;
    return 1;
}
int resize(Vector* arr, size_t nums_ele)
{
    if(!arr)
    {
        return 0;
    }
    void* errCheck = realloc(arr->data, arr->elemsize *  nums_ele);
    if(!errCheck)
    {
        return 0;
    }
    arr->length = nums_ele;
    arr->data = errCheck;
    return 1;
}
void* get_addr(Vector* arr, size_t index)
{
    if(!arr || !check_valid_index(arr, index))
    {
        return NULL;
    }
    return arr->data + index * arr->elemsize;
}
// Non-generical functions. Default implement.
int ati(Vector* arr, size_t index)
{
    if(!check_valid_index(arr, index))
    {
        return -1;  //place holder
    }
    int* data = (int*)arr->data;
    return data[index];
}
int seti(Vector* arr, size_t index, int value)
{
    if(!check_valid_index(arr, index))
    {
        return 0;
    }
    memcpy(arr->data + index * arr->elemsize, &value, sizeof(value));
    return 1;
}
int push_backi(Vector* arr, int value)
{
	if(!arr)
	{
		return 0;
	}
    void* errChecking = realloc(arr->data,  arr->elemsize * (len(arr) + 1));
    if(!errChecking)
    {
        return 0;
    }
    arr->data = errChecking;    
    arr->length++;
    seti(arr, arr->length - 1, value);
    return 1;
}
int inserti(Vector* arr, size_t index, int value)
{
    if(!arr || !check_valid_index(arr, index))
    {
        return 0;
    }
    if(!resize(arr, len(arr) + 1))
    {
        return 0;
    } 
    void* dst = arr->data + (index + 1) * arr->elemsize;
    void* src = arr->data + index * arr->elemsize;
    size_t bytes_to_move = (len(arr) - index) * arr->elemsize;     
    memmove(dst, src, bytes_to_move);
    seti(arr, index, value);
    return 1;
}
