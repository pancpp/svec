/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 */
#include "cbuf.h"
#include <string.h>
#include "svec.h"

struct svec_cbuf {
  void* data;
  size_t start;
  size_t size;
  size_t capacity;
  size_t data_size;
};

static inline bool is_legal_index(svec_cbuf self, size_t index) {
  return index < self->size;
}

// Constructor and destructor
svec_cbuf svec_cbuf_new(size_t data_size, size_t capacity) {
  struct svec_cbuf* cbuf =
      (struct svec_cbuf*)svec_malloc(sizeof(struct svec_cbuf));
  if (cbuf) {
    cbuf->data = svec_malloc(capacity * data_size);
    if (cbuf->data) {
      cbuf->start = 0;
      cbuf->size = 0;
      cbuf->capacity = capacity;
      cbuf->data_size = data_size;
    } else {
      svec_free(cbuf);
      cbuf = NULL;
    }
  }
  return cbuf;
}

void svec_cbuf_delete(svec_cbuf self) {
  if (self) {
    svec_cbuf_clear(self);
    svec_free(self);
  }
}

// Element access
void* svec_cbuf_at(svec_cbuf self, size_t index) {
  if (is_legal_index(self, index)) {
    return self->data +
           (self->start + index) % self->capacity * self->data_size;
  }
  return NULL;
}

void* svec_cbuf_front(svec_cbuf self) {
  return svec_cbuf_at(self, 0);
}

void* svec_cbuf_back(svec_cbuf self) {
  return svec_cbuf_at(self, self->size - 1);
}

// Capacity
bool svec_cbuf_empty(svec_cbuf self) {
  return self->size == 0;
}

bool svec_cbuf_full(svec_cbuf self) {
  return self->size == self->capacity;
}

size_t svec_cbuf_size(svec_cbuf self) {
  return self->size;
}

size_t svec_cbuf_capacity(svec_cbuf self) {
  return self->capacity;
}

int svec_cbuf_reserve(svec_cbuf self, size_t new_cap) {
}

// Modifiers
void svec_cbuf_clear(svec_cbuf self) {
  self->start = 0;
  self->size = 0;
}

void svec_cbuf_erase(svec_cbuf self, size_t index) {
  svec_cbuf_erase_items(self, index, 1);
}

void svec_cbuf_erase_range(svec_cbuf self, size_t beg, size_t end) {
  svec_cbuf_erase_items(self, beg, end - beg);
}

void svec_cbuf_erase_items(svec_cbuf self, size_t index, size_t num_items) {
}

int svec_cbuf_insert(svec_cbuf self, size_t index, const void* data) {
  return svec_cbuf_insert_items(self, index, data, 1);
}

int svec_cbuf_insert_range(svec_cbuf self, size_t index, const void* data_beg,
                           const void* data_end) {
  return svec_cbuf_insert_items(self, index, data_beg,
                                (data_end - data_beg) / self->data_size);
}

int svec_cbuf_insert_items(svec_cbuf self, size_t index, const void* data,
                           size_t num_items) {
}

int svec_cbuf_push_front(svec_cbuf self, const void* data) {
  return svec_cbuf_insert(self, 0, data, 1);
}

int svec_cbuf_push_back(svec_cbuf self, const void* data) {
  return svec_cbuf_insert(self, self->size, data, 1);
}

void svec_cbuf_pop_front(svec_cbuf self) {
  svec_cbuf_erase(self, 0);
}

void svec_cbuf_pop_back(svec_cbuf self) {
  svec_cbuf_erase(self, self->size - 1);
}

int svec_vector_resize(svec_cbuf self, size_t new_size) {
}

void svec_vector_set(svec_cbuf self, size_t index, const void* data) {
}
