/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 04, 2020
 */

#ifndef SVEC_SVEC_H_
#define SVEC_SVEC_H_

#include <stddef.h>

/// @brief Memory management routines.
struct svec_mem {
  void* (*malloc)(size_t size);
  void (*free)(void* ptr);
#ifdef SVEC_REALLOC
  void* (*realloc)(void* ptr, size_t new_size);
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

void svec_init(struct svec_mem* m);

void* svec_malloc(size_t size);
void svec_free(void* ptr);
#ifdef SVEC_REALLOC
void* svec_realloc(void* ptr, size_t new_size);
#endif

#ifdef __cplusplus
}
#endif

#endif  // SVEC_SVEC_H_
