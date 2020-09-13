/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 *
 * @brief The last-in first-out (LIFO) stack.
 */
#include "svec/stack.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "svec/svec.h"

struct node {
  struct node* next;
  void* data;
};

struct svec_stack {
  struct node* top;
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

svec_stack svec_stack_new(size_t data_size) {
  struct svec_stack* st = svec_malloc(sizeof(struct svec_stack));
  if (st) {
    st->top = NULL;
    st->size = 0;
    st->data_size = data_size;
  }
  return st;
}

void svec_stack_delete(svec_stack self) {
  if (self) {
    svec_stack_clear(self);
    svec_free(self);
  }
}

void* svec_stack_top(svec_stack self) {
  if (self->top) {
    return self->top->data;
  }
  return NULL;
}

bool svec_stack_empty(svec_stack self) {
  return self->size == 0;
}

size_t svec_stack_size(svec_stack self) {
  return self->size;
}

int svec_stack_push(svec_stack self, const void* data) {
  struct node* nn = new_node(data, self->data_size);
  if (!nn) {
    return ENOMEM;
  }

  nn->next = self->top;
  self->top = nn;
  ++self->size;

  return 0;
}

void svec_stack_pop(svec_stack self) {
  if (self->top) {
    struct node* top = self->top;
    self->top = top->next;
    delete_node(top);
    --self->size;
  }
}

void svec_stack_clear(svec_stack self) {
  struct node* next;
  struct node* curr = self->top;
  while (curr) {
    next = curr->next;
    delete_node(curr);
    curr = next;
  }

  self->top = NULL;
  self->size = 0;
}
