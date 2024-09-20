/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @file
 * @brief Circular buffer.
 */

#ifndef SVEC_CBUF_H_
#define SVEC_CBUF_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct svec_cbuf* svec_cbuf;

// Constructor and destructor
svec_cbuf svec_cbuf_new(size_t data_size, size_t capacity);
void svec_cbuf_delete(svec_cbuf self);

// Element access
void* svec_cbuf_at(svec_cbuf self, size_t index);
void* svec_cbuf_front(svec_cbuf self);
void* svec_cbuf_back(svec_cbuf self);

// Capacity
bool svec_cbuf_empty(svec_cbuf self);
bool svec_cbuf_full(svec_cbuf self);
size_t svec_cbuf_size(svec_cbuf self);
size_t svec_cbuf_capacity(svec_cbuf self);
int svec_cbuf_reserve(svec_cbuf self, size_t new_cap);

// Modifiers
void svec_cbuf_clear(svec_cbuf self);

void svec_cbuf_erase(svec_cbuf self, size_t index);
void svec_cbuf_erase_range(svec_cbuf self, size_t beg, size_t end);
void svec_cbuf_erase_items(svec_cbuf self, size_t index, size_t num_items);

int svec_cbuf_insert(svec_cbuf self, size_t index, const void* data);
int svec_cbuf_insert_range(svec_cbuf self, size_t index, const void* data_beg,
                           const void* data_end);
int svec_cbuf_insert_items(svec_cbuf self, size_t index, const void* data,
                           size_t num_items);

int svec_cbuf_push_front(svec_cbuf self, const void* data);
int svec_cbuf_push_back(svec_cbuf self, const void* data);

void svec_cbuf_pop_front(svec_cbuf self);
void svec_cbuf_pop_back(svec_cbuf self);

int svec_vector_resize(svec_cbuf self, size_t new_size);
void svec_vector_set(svec_cbuf self, size_t index, const void* data);

#endif  // SVEC_CBUF_H_
