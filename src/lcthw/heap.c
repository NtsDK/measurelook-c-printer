#include <lcthw/heap.h>
#include <assert.h>

Heap *Heap_create(DArray *array, Heap_comparator comparator){
	Heap *heap = malloc(sizeof(Heap));
	check_mem(heap);
	check(array != NULL, "Array can't be NULL.");
	check(comparator != NULL, "Comparator can't be NULL.");
	
	heap->array = array;
	heap->comparator = comparator;
	
	for(int i = DArray_count(heap->array) / 2; i>=0; --i){
		Heap_siftDown(heap, i);
	}
	
	return heap;

error:
	if(array) DArray_clear_destroy(array);
    if(heap) free(heap);
    return NULL;
}

void Heap_siftDown(Heap *heap, int i){
	int heapSize = DArray_count(heap->array);
	while (2 * i + 1 < heapSize){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
//        if( right < heapSize && DArray_get(heap->array, right) < DArray_get(heap->array, left)){
        if( right < heapSize && heap->comparator(DArray_get(heap->array, right),
        		 DArray_get(heap->array, left)) < 0){
            j = right;
        }
//        if (DArray_get(heap->array, i) <= DArray_get(heap->array, j)){
        if (heap->comparator(DArray_get(heap->array, i), DArray_get(heap->array, j)) <= 0){
	        break;
        }
        DArray_swap(heap->array, i,j);
        i = j;
	}    
}

void Heap_siftUp(Heap *heap, int i){
//	while( DArray_get(heap->array, i) < DArray_get(heap->array, (i - 1) / 2)){   // i == 0 — мы в корне
	while( heap->comparator(DArray_get(heap->array, i), DArray_get(heap->array, (i - 1) / 2)) < 0){   // i == 0 — мы в корне
		DArray_swap(heap->array, i,(i - 1) / 2);
	    i = (i - 1) / 2;
	}
}

void *Heap_extract(Heap *heap){
	void *min = DArray_get(heap->array, 0);
	DArray_set(heap->array, 0, DArray_pop(heap->array));
    Heap_siftDown(heap, 0);
    return min;
}

void Heap_insert(Heap *heap, void *el){
	DArray_push(heap->array, el);
	Heap_siftUp(heap, Heap_size(heap)-1);
}

void Heap_destroy(Heap *heap){
    if(heap) {
//        if(heap->array) DArray_clear_destroy(heap->array);
        if(heap->array) DArray_destroy(heap->array);
        free(heap);
    }
}
