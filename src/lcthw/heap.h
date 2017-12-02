#ifndef _Heap_h
#define _Heap_h
#include <stdlib.h>
#include <assert.h>
#include <dbg.h>
#include <lcthw/darray.h>

typedef int (*Heap_comparator)(void *el1, void *el2);

typedef struct Heap {
    //int end;
    //int max;
    //size_t element_size;
    //size_t expand_rate;
    //void **contents;
    Heap_comparator comparator;
    DArray *array;
} Heap;

Heap *Heap_create(DArray *array, Heap_comparator comparator); // heapify

void Heap_siftDown(Heap *heap, int i);

void Heap_siftUp(Heap *heap, int i);

void *Heap_extract(Heap *heap);

void Heap_insert(Heap *heap, void *el);

void Heap_destroy(Heap *heap);

#define Heap_size(A) DArray_count(A->array)
#define Heap_free(E) DArray_free((E))

static inline void *Heap_new(Heap *heap)
{
    //check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
    void *el = DArray_new(heap->array);
    check(el != NULL, "Error on new element creation");

    return el;

error:
    return NULL;
}

/*
static inline void *DArray_new(DArray *array)
{
    check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");

    return calloc(1, array->element_size);

error:
    return NULL;
}*/

//void Heap_clear(Heap *heap);
/*
int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);*/

//void Heap_clear_destroy(Heap *heap);

#endif
