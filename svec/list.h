/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 11, 2020
 *
 * @brief The doubly-linked list.
 */

#ifndef SVEC_LIST_H_
#define SVEC_LIST_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct svec_list *svec_list;

// Constructor and destructor
svec_list svec_list_new(size_t data_size);
void svec_list_delete(svec_list self);

// Element access
void *svec_list_front(svec_list self);
void *svec_list_back(svec_list self);
void *svec_list_at(svec_list self, size_t index);

// Modifiers
void svec_list_clear(svec_list self);
void svec_list_erase(svec_list self, size_t index);

/// @return 0 on success.
int svec_list_insert(svec_list self, size_t index, void *data);

/// @return 0 on success.
int svec_list_push_back(svec_list self, void *data);

/// @return 0 on success.
int svec_list_push_front(svec_list self, void *data);

void svec_list_pop_back(svec_list self);
void svec_list_pop_front(svec_list self);

// Capacity
bool svec_list_empty(svec_list self);
size_t svec_list_size(svec_list self);

#endif  // SVEC_LIST_H_
