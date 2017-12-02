#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);

typedef struct Hashmap {
    DArray *buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode *node);
typedef int (*Hashmap_extended_traverse_cb)(HashmapNode *node, void *data);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap *map, void *key, void *data);
void *Hashmap_get(Hashmap *map, void *key);

int Hashmap_containsKey(Hashmap *map, void *key);

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

int Hashmap_extended_traverse(Hashmap *map, Hashmap_extended_traverse_cb traverse_cb, void *data);

void *Hashmap_delete(Hashmap *map, void *key);

static int int_compare(void *a, void *b)
{
    int *tmp1 = a;
    int *tmp2 = b;
    return *tmp1 - *tmp2;
}

static uint32_t int_hash(void *a)
{
    uint32_t *tmp = a;
    return *tmp;
}

#endif
