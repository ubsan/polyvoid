#ifndef PV_HASHMAP_H
#define PV_HASHMAP_H

#include "_macros.h"
#include "common.h"
#include "linked_list.h"

PV_BEGIN_HEADER

struct PV_HashmapNode;

PV_DEFINE_STRUCT(PvHashmap) {
  PvHasher* PV_hasher;
  PvEquals* PV_equals;
  size_t PV_elements_until_reallocation;
  /*
    log2(array_length)
    for example, length = 32 => array_length_log2 = 5
    if length = 0, array_length_log2 = SIZE_MAX
  */
  size_t PV_array_length_log2;
  struct PvHashmapNode** PV_array;
};

PV_EXPORT
PvHashmap pv_hashmap_new(PvHasher* PV_hasher, PvEquals* PV_equals);

/**
  Either inserts the key, value pair into the map, if the key is not currently
  in the map; or it sets the value mapped to by key to value.

  NOTE:
    This function does not replace key.
    If you want to free the new key, you'll have to get it from wherever you
    passed it in.

  ```cpp
  void add_0_1_to_hm(PvHashmap* hm) {
    int* key = malloc(sizeof *key);
    int* value = malloc(sizeof *value);
    if (!key || !value) {
      abort();
    }
    *key = 0;
    *value = 1;

    int* old_value;
    if ((old_value = pv_hashmap_insert(key, value))) {
      free(old_value);
    }
  }
  ```

  returns:
    - NULL if the key is not currently in the map
    - the value replaced if the key _is_ in the map
*/
PV_EXPORT
void* pv_hashmap_insert(PvHashmap* PV_self, void* key, void* value);

PV_EXPORT
void* pv_hashmap_get(PvHashmap* PV_self, void const* key);

PV_DEFINE_STRUCT(PvHashmapRemoveReturn) {
  void* key;
  void* value;
};

PV_EXPORT
PvHashmapRemoveReturn pv_hashmap_remove(PvHashmap* PV_self, void const* key);

PV_EXPORT
size_t pv_hashmap_size(PvHashmap const* PV_self);

PV_EXPORT
void pv_hashmap_delete(
    PvHashmap* PV_self, PvDeleter* PV_key_del, PvDeleter* PV_value_del);

PV_END_HEADER

#endif /* PV_HASHMAP_H */
