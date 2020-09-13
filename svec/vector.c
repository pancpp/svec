/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 */
#include "svec/vector.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "svec/svec.h"

struct svec_vector {
  void* data;
  size_t size;
  size_t capacity;
  size_t data_size;
};

static inline bool is_legal_index(svec_vector self, size_t index) {
  return index < self->size;
}

svec_vector svec_vector_new(size_t data_size) {
  struct svec_vector* vec = svec_malloc(sizeof(struct svec_vector));
  if (vec) {
    vec->data = NULL;
    vec->size = vec->capacity = 0;
    vec->data_size = data_size;
  }
  return vec;
}

void svec_vector_delete(svec_vector self) {
  if (self) {
    svec_vector_clear(self);
    svec_free(self);
  }
}

void* svec_vector_at(svec_vector self, size_t index) {
  if (!is_legal_index(self, index)) {
    return NULL;
  }

  return self->data + index * self->data_size;
}

void* svec_vector_front(svec_vector self) {
  return self->data;
}

void* svec_vector_back(svec_vector self) {
  if (self->size) {
    return self->data + (self->size - 1) * self->data_size;
  }
  return NULL;
}

void* svec_vector_data(svec_vector self) {
  return self->data;
}

bool svec_vector_empty(svec_vector self) {
  return self->size == 0;
}

size_t svec_vector_size(svec_vector self) {
  return self->size;
}

size_t svec_vector_capacity(svec_vector self) {
  return self->capacity;
}

size_t svec_vector_reserve(svec_vector self, size_t new_cap) {
  if (new_cap > self->capacity) {
#ifdef SVEC_REALLOC
    void* new_data = svec_realloc(self->data, new_cap * self->data_size);
    if (new_data) {
      self->data = new_data;
      self->capacity = new_cap;
    }
#else
    void* new_data = svec_malloc(new_cap * self->data_size);
    if (new_data) {
      memcpy(new_data, self->data, self->size * self->data_size);
      svec_free(self->data);
      self->data = new_data;
      self->capacity = new_cap;
    }
#endif
  }
}

void svec_vector_shrink_to_fit(svec_vector self) {
  if (self->size == 0) {
    svec_free(self->data);
    self->data = NULL;
    self->capacity = 0;
  } else if (self->capacity > self->size) {
    void* new_data = svec_malloc(self->size * self->data_size);
    if (new_data) {
      memcpy(new_data, self->data, self->size * self->data_size);
      self->data = new_data;
      self->capacity = self->size;
    }
  }
}

void svec_vector_clear(svec_vector self) {
  self->size = 0;
}

void svec_vector_erase(svec_vector self, size_t index) {
  if (is_legal_index(self, index)) {
    memmove(self->data + index * self->data_size,
            self->data + (index + 1) * self->data_size,
            self->size - (index + 1));
    --self->size;
  }
}

void svec_vector_erase_range(svec_vector self, size_t beg, size_t end) {
  if (end > beg && is_legal_index(self, beg) && is_legal_index(self, end - 1)) {
    memmove(self->data + beg * self->data_size,
            self->data + end * self->data_size,
            (self->size - end) * self->data_size);
    self->size -= end - beg;
  }
}

int svec_vector_insert(svec_vector self, size_t index, const void* data) {
  return svec_vector_insert_items(self, index, data, 1);
}

int svec_vector_insert_range(svec_vector self, size_t index,
                             const void* data_beg, const void* data_end) {
  return svec_vector_insert_items(self, index, data_beg,
                                  (data_end - data_beg) / self->data_size);
}

int svec_vector_insert_items(svec_vector self, size_t index, const void* data,
                             size_t num_items) {
  if (index > self->size) {
    return EINVAL;
  }

  if (!self->data) {
    self->data = svec_malloc(num_items * self->data_size);
    if (!self->data) {
      return ENOMEM;
    }
    self->size = self->capacity = num_items;
    memcpy(self->data, data, num_items * self->data_size);
  } else {
    if (self->size + num_items > self->capacity) {
      int rc = svec_vector_reserve(self, self->size + num_items + 1);
      if (rc) {
        return rc;
      }
    }
    memmove(self->data + (index + num_items) * self->data_size,
            self->data + index * self->data_size, num_items * self->data_size);
    memcpy(self->data + index * self->data_size, data,
           num_items * self->data_size);

    self->size += num_items;
  }

  return 0;
}

int svec_vector_push_back(svec_vector self, void* data) {
  if (!self->data) {
    self->data = svec_malloc(self->data_size);
    if (!self->data) {
      return ENOMEM;
    }
    self->size = self->capacity = 1;
    memcpy(self->data, data, self->data_size);
  } else {
    if (self->size == self->capacity) {
      int rc = svec_vector_reserve(self, self->capacity * 2);
      if (rc) {
        return rc;
      }
    }
    memcpy(self->data + self->size * self->data_size, data, self->data_size);
    ++self->size;
  }

  return 0;
}

void svec_vector_pop_back(svec_vector self) {
  if (self->size > 0) {
    --self->size;
  }
}

int svec_vector_resize(svec_vector self, size_t new_size) {
  self->size = self->new_size;
}