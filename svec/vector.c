/**
 * @copyright Copyright (C) 2020-2024 Leyuan Pan. All rights reserved.
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

static inline bool is_legal_index(svec_vector_t v, size_t index) {
  return index < v->size;
}

svec_vector_t svec_vector_new(size_t data_size) {
  svec_vector_t vec = svec_malloc(sizeof(svec_vector_t));
  if (vec) {
    vec->data = NULL;
    vec->size = vec->capacity = 0;
    vec->data_size = data_size;
  }
  return vec;
}

void svec_vector_delete(svec_vector_t v) {
  if (v) {
    svec_vector_clear(v);
    svec_free(v);
  }
}

void* svec_vector_at(svec_vector_t v, size_t index) {
  if (!is_legal_index(v, index)) {
    return NULL;
  }

  return v->data + index * v->data_size;
}

void* svec_vector_front(svec_vector_t v) {
  return v->data;
}

void* svec_vector_back(svec_vector_t v) {
  if (v->size) {
    return v->data + (v->size - 1) * v->data_size;
  }
  return NULL;
}

void* svec_vector_data(svec_vector_t v) {
  return v->data;
}

bool svec_vector_empty(svec_vector_t v) {
  return v->size == 0;
}

size_t svec_vector_size(svec_vector_t v) {
  return v->size;
}

size_t svec_vector_capacity(svec_vector_t v) {
  return v->capacity;
}

int svec_vector_reserve(svec_vector_t v, size_t new_cap) {
  if (new_cap > v->capacity) {
#ifdef SVEC_REALLOC
    void* new_data = svec_realloc(v->data, new_cap * v->data_size);
    if (new_data) {
      v->data = new_data;
      v->capacity = new_cap;
    } else {
      return ENOMEM;
    }
#else
    void* new_data = svec_malloc(new_cap * v->data_size);
    if (new_data) {
      memcpy(new_data, v->data, v->size * v->data_size);
      svec_free(v->data);
      v->data = new_data;
      v->capacity = new_cap;
    } else {
      return ENOMEM;
    }
#endif
  }

  return 0;
}

void svec_vector_shrink_to_fit(svec_vector_t v) {
  if (v->size == 0) {
    svec_free(v->data);
    v->data = NULL;
    v->capacity = 0;
  } else if (v->capacity > v->size) {
    void* new_data = svec_malloc(v->size * v->data_size);
    if (new_data) {
      memcpy(new_data, v->data, v->size * v->data_size);
      v->data = new_data;
      v->capacity = v->size;
    }
  }
}

void svec_vector_clear(svec_vector_t v) {
  v->size = v->capacity = 0;
  svec_free(v->data);
}

void svec_vector_erase(svec_vector_t v, size_t index) {
  if (is_legal_index(v, index)) {
    memmove(v->data + index * v->data_size,
            v->data + (index + 1) * v->data_size,
            (v->size - (index + 1)) * v->data_size);
    --v->size;
  }
}

void svec_vector_erase_range(svec_vector_t v, size_t beg, size_t end) {
  if (end > beg && is_legal_index(v, beg) && is_legal_index(v, end - 1)) {
    memmove(v->data + beg * v->data_size, v->data + end * v->data_size,
            (v->size - end) * v->data_size);
    v->size -= end - beg;
  }
}

int svec_vector_insert(svec_vector_t v, size_t index, const void* data) {
  return svec_vector_insert_items(v, index, data, 1);
}

int svec_vector_insert_range(svec_vector_t v, size_t index,
                             const void* data_beg, const void* data_end) {
  return svec_vector_insert_items(v, index, data_beg,
                                  (data_end - data_beg) / v->data_size);
}

int svec_vector_insert_items(svec_vector_t v, size_t index, const void* data,
                             size_t num_items) {
  if (index > v->size) {
    return EINVAL;
  }

  if (!v->data) {
    v->data = svec_malloc(num_items * v->data_size);
    if (!v->data) {
      return ENOMEM;
    }
    v->size = v->capacity = num_items;
    memcpy(v->data, data, num_items * v->data_size);
  } else {
    if (v->size + num_items > v->capacity) {
      int rc = svec_vector_reserve(v, v->size + num_items + 1);
      if (rc) {
        return rc;
      }
    }
    memmove(v->data + (index + num_items) * v->data_size,
            v->data + index * v->data_size, (v->size - index) * v->data_size);
    memcpy(v->data + index * v->data_size, data, num_items * v->data_size);

    v->size += num_items;
  }

  return 0;
}

int svec_vector_push_back(svec_vector_t v, const void* data) {
  if (!v->data) {
    v->data = svec_malloc(v->data_size);
    if (!v->data) {
      return ENOMEM;
    }
    v->size = v->capacity = 1;
    memcpy(v->data, data, v->data_size);
  } else {
    if (v->size == v->capacity) {
      int rc = svec_vector_reserve(v, v->capacity * 2);
      if (rc) {
        return rc;
      }
    }
    memcpy(v->data + v->size * v->data_size, data, v->data_size);
    ++v->size;
  }

  return 0;
}

void svec_vector_pop_back(svec_vector_t v) {
  if (v->size > 0) {
    --v->size;
  }
}

int svec_vector_resize(svec_vector_t v, size_t new_size) {
  if (new_size > v->capacity) {
    int rc = svec_vector_reserve(v, new_size + 1);
    if (rc) {
      return rc;
    }
  }
  v->size = new_size;
  return 0;
}
