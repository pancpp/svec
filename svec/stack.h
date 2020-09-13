/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @file
 * @author Leyuan Pan
 * @date Sep 12, 2020
 *
 * @brief The last-in first-out (LIFO) stack.
 */
#ifndef SVEC_STACK_H_
#define SVEC_STACK_H_

#include <stddef.h>

typedef struct svec_stack* svec_stack;

// Constructor and destructor
svec_stack svec_stack_new(size_t data_size);
void svec_stack_delete(svec_stack self);

// Element access
void* svec_stack_top(svec_stack self);

// Capacity
bool svec_stack_empty(svec_stack self);
size_t svec_stack_size(svec_stack self);

// Modifiers
int svec_stack_push(svec_stack self, const void* data);
void svec_stack_pop(svec_stack self);
void svec_stack_clear(svec_stack self);

#endif  // SVEC_STACK_H_
