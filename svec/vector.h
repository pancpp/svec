/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 *
 * @file
 * @brief The dynamic size vector.
 */
#ifndef SVEC_VECTOR_H_
#define SVEC_VECTOR_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct svec_vector* svec_vector;

// Constructor and destructor
svec_vector svec_vector_new(size_t data_size);
void svec_vector_delete(svec_vector self);

// Element access
void* svec_vector_at(svec_vector self, size_t index);
void* svec_vector_front(svec_vector self);
void* svec_vector_back(svec_vector self);
void* svec_vector_data(svec_vector self);

// Capacity
bool svec_vector_empty(svec_vector self);
size_t svec_vector_size(svec_vector self);
size_t svec_vector_capacity(svec_vector self);

/// @brief Reserves storage.
/// @details This function is only effective when `new_cap` is greater than the
/// current list capacity and the memory allocation is successful.
int svec_vector_reserve(svec_vector self, size_t new_cap);

/// @brief Reduces memory usage by freeing unused memory.
/// @details This function is only effective on success which means that it does
/// not change the status of the list if the new memory allocation fails.
void svec_vector_shrink_to_fit(svec_vector self);

// Modifiers
void svec_vector_clear(svec_vector self);

void svec_vector_erase(svec_vector self, size_t index);

/// @brief Erase items between the range [`beg`, `end`) where `end` is
/// exclusive.
void svec_vector_erase_range(svec_vector self, size_t beg, size_t end);

/// @brief Insert `data` at position `index`.
int svec_vector_insert(svec_vector self, size_t index, const void* data);

/// @brief Insert [`data_beg`, `data_end`) at position `index` where `data_end`
/// is exclusive.
int svec_vector_insert_range(svec_vector self, size_t index,
                             const void* data_beg, const void* data_end);

int svec_vector_insert_items(svec_vector self, size_t index, const void* data,
                             size_t num_items);

int svec_vector_push_back(svec_vector self, const void* data);
void svec_vector_pop_back(svec_vector self);

int svec_vector_resize(svec_vector self, size_t new_size);

#endif  // SVEC_VECTOR_H_
