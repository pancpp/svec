/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 *
 * @brief The first-in first-out (FIFO) queue.
 */
#include "svec/queue.h"
#include <errno.h>
#include <stdlib.h>
#include "svec/svec.h"

struct node {
  struct node* next;
  void* data;
};

struct svec_queue {
  struct node* front;
  struct node* back;
  size_t size;
  size_t data_size;
};

static struct node* new_node(const void* data, size_t size) {
  struct node* node = (struct node*)svec_malloc(sizeof(struct node));
  if (node) {
    node->data = svec_malloc(size);
    if (node->data) {
      memcpy(node->data, data, size);
      node->next = NULL;
    } else {
      svec_free(node);
      node = NULL;
    }
  }
  return node;
}

static void delete_node(struct node* node) {
  svec_free(node->data);
  svec_free(node);
}

svec_queue svec_queue_new(size_t data_size) {
  struct svec_queue* q = svec_malloc(sizeof(struct svec_queue));
  if (q) {
    q->front = q->back = NULL;
    q->size = 0;
    q->data_size = data_size;
  }
  return q;
}

void svec_queue_delete(svec_queue self) {
  if (self) {
    svec_queue_clear(self);
    svec_free(self);
  }
}

void* svec_queue_front(svec_queue self) {
  if (self->front) {
    return self->front->data;
  }
  return NULL;
}

void* svec_queue_back(svec_queue self) {
  if (self->back) {
    return self->back->data;
  }
  return NULL;
}

bool svec_queue_empty(svec_queue self) {
  return self->size == 0;
}

size_t svec_queue_size(svec_queue self) {
  return self->size;
}

int svec_queue_push(svec_queue self, const void* data) {
  struct node* nn = new_node(data, self->data_size);
  if (!nn) {
    return ENOMEM;
  }

  if (self->back) {
    self->back->next = nn;
    self->back = nn;
  } else {
    self->front = self->back = nn;
  }
  ++self->size;

  return 0;
}

void svec_queue_pop(svec_queue self) {
  if (self->front) {
    struct node* nn = self->front->next;
    delete_node(self->front);
    self->front = nn;
  }
}

void svec_queue_clear(svec_queue self) {
  struct node* next;
  struct node* curr = self->front;
  while (curr) {
    next = curr->next;
    delete_node(curr);
    curr = next;
  }

  self->front = self->back = NULL;
  self->size = 0;
}

#endif  // SVEC_QUEUE_H_
