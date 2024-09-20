/**
 * @copyright Copyright (C) 2020-2024 Leyuan Pan. All rights reserved.
 */
#ifndef SVEC_SVEC_H_
#define SVEC_SVEC_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Memory management routines.
typedef struct svec_mem {
  void* (*malloc)(size_t size);
  void (*free)(void* ptr);
  void* (*realloc)(void* ptr, size_t new_size);
} svec_mem_t;

void svec_init(svec_mem_t* m);
void* svec_malloc(size_t size);
void svec_free(void* ptr);

#ifdef SVEC_REALLOC
void* svec_realloc(void* ptr, size_t new_size);
#endif

#ifdef __cplusplus
}
#endif

#endif  // SVEC_SVEC_H_
