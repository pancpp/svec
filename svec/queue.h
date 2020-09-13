/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @file
 * @author Leyuan Pan
 * @date Sep 12, 2020
 *
 * @brief The first-in first-out (FIFO) queue.
 */
#ifndef SVEC_QUEUE_H_
#define SVEC_QUEUE_H_

#include <stddef.h>

typedef struct svec_queue* svec_queue;

// Constructor and destructor
svec_queue svec_queue_new(size_t data_size);
void svec_queue_delete(svec_queue self);

// Element access
void* svec_queue_front(svec_queue self);
void* svec_queue_back(svec_queue self);

// Capacity
bool svec_queue_empty(svec_queue self);
size_t svec_queue_size(svec_queue self);

// Modifiers
int svec_queue_push(svec_queue self, const void* data);
void svec_queue_pop(svec_queue self);
void svec_queue_clear(svec_queue self);

#endif  // SVEC_QUEUE_H_
