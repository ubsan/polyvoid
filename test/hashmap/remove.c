#include <pv/hashmap.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.c"

void abort_on_call(void* ptr) {
  (void)ptr;
  abort();
}

int main(void) {
  PvHashmap hm = pv_hashmap_new(int_hash, int_equals);

  for (int i = 0; i < 100; ++i) {
    insert_unique(&hm, i, i + 1);
  }

  for (int i = 0; i < 100; ++i) {
    PvHashmapRemoveReturn rr = pv_hashmap_remove(&hm, &i);
    if (!rr.key) {
      return 1;
    }
    if (!rr.value) {
      return 2;
    }

    if (*(int*)rr.key != i) {
      return 3;
    }
    if (*(int*)rr.value != i + 1) {
      return 4;
    }

    free(rr.key);
    free(rr.value);
  }

  size_t size = pv_hashmap_size(&hm);
  if (size != 0) {
    fprintf(stderr, "pv_hashmap_size = %zu (should = 0)\n", size);
    return 5;
  }

  pv_hashmap_delete(&hm, abort_on_call, abort_on_call);
  return 0;
}
