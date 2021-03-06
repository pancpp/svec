/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 04, 2020
 */

#include "svec/svec.h"
#include <stdlib.h>

struct svec_mem g_svec_mem = {
    .malloc = malloc,
    .free = free,
#ifdef SVEC_REALLOC
    .realloc = realloc,
#endif
};

void svec_init(struct svec_mem* svm) {
  g_svec_mem.malloc = svm->malloc;
  g_svec_mem.free = svm->free;
#ifdef SVEC_REALLOC
  g_svec_mem.realloc = svm->realloc;
#endif
}

void* svec_malloc(size_t size) {
  return g_svec_mem.malloc(size);
}

void svec_free(void* ptr) {
  g_svec_mem.free(ptr);
}

#ifdef SVEC_REALLOC
void* svec_realloc(void* ptr, size_t new_size) {
  return g_svec_mem.realloc(ptr, new_size);
}
#endif
