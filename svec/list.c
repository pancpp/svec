/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 11, 2020
 */
#include "svec/list.h"
#include <errno.h>
#include <string.h>
#include "svec/svec.h"

struct node {
  struct node *prev;
  struct node *next;
  void *data;
};

struct svec_list {
  size_t data_size;
  size_t count;
  struct node *front;
  struct node *back;
};

static bool is_legal_index(svec_list self, size_t index) {
  return index < self->count;
}

static struct node *new_node(const void *data, size_t size) {
  struct node *node = (struct node *)svec_malloc(sizeof(struct node));
  if (node) {
    node->data = svec_malloc(size);
    if (node->data) {
      memcpy(node->data, data, size);
      node->prev = node->next = NULL;
    } else {
      svec_free(node);
      node = NULL;
    }
  }

  return node;
}

static void delete_node(struct node *node) {
  svec_free(node->data);
  svec_free(node);
}

static struct node *get_node_from_front(svec_list self, size_t index) {
  struct node *curr = self->front;
  while (index--) {
    curr = curr->next;
  }
  return curr;
}

static struct node *get_node_from_back(svec_list self, size_t index) {
  struct node *curr = self->back;
  index = self->count - 1 - index;
  while (index--) {
    curr = curr->prev;
  }
  return curr;
}

static struct node *get_node_at(svec_list self, size_t index) {
  return index < self->count / 2 ? get_node_from_front(self, index)
                                 : get_node_from_back(self, index);
}

svec_list svec_list_new(size_t data_size) {
  struct svec_list *list = svec_malloc(sizeof(struct svec_list));
  if (list) {
    list->data_size = data_size;
    list->count = 0;
    list->front = list->back = NULL;
  }
  return list;
}

void svec_list_delete(svec_list self) {
  if (self) {
    svec_list_clear(self);
    svec_free(self);
  }
}

void *svec_list_front(svec_list self) {
  return self->front;
}

void *svec_list_back(svec_list self) {
  return self->back;
}

void *svec_list_at(svec_list self, size_t index) {
  if (!is_legal_index(self, index)) {
    return NULL;
  }

  return get_node_at(self, index)->data;
}

void svec_list_clear(svec_list self) {
  struct node *next;
  struct node *curr = self->front;
  while (curr) {
    next = curr->next;
    delete_node(curr);
    curr = next;
  }

  self->front = self->back = NULL;
  self->count = 0;
}

void svec_list_erase(svec_list self, size_t index) {
  if (!is_legal_index(self, index)) {
    return;
  }

  struct node *node_to_erase = get_node_at(self, index);
  if (node_to_erase->prev) {
    node_to_erase->prev->next = node_to_erase->next;
  } else {
    self->front = node_to_erase->next;
  }

  if (node_to_erase->next) {
    node_to_erase->next->prev = node_to_erase->prev;
  } else {
    self->back = node_to_erase->prev;
  }

  delete_node(node_to_erase);
  --self->count;
}

int svec_list_insert(svec_list self, size_t index, void *data) {
  struct node *nn;
  if (index == 0) {
    nn = new_node(data, self->data_size);
    if (!nn) {
      return ENOMEM;
    }

    if (self->front) {
      nn->next = self->front;
      self->front->prev = nn;
      self->front = nn;
    } else {
      self->front = self->back = nn;
    }
  } else if (index == self->count) {
    nn = new_node(data, self->data_size);
    if (!nn) {
      return ENOMEM;
    }

    if (self->back) {
      self->back->next = nn;
      nn->prev = self->back;
      self->back = nn;
    } else {
      self->front = self->back = nn;
    }
  } else {
    if (!is_legal_index(self, index)) {
      return EINVAL;
    }

    nn = new_node(data, self->data_size);
    if (!nn) {
      return ENOMEM;
    }

    struct node *cn = get_node_at(self, index);
    cn->prev->next = nn;
    nn->prev = cn->prev;
    nn->next = cn;
    cn->prev = nn;
  }

  ++self->count;

  return 0;
}

int svec_list_push_back(svec_list self, void *data) {
  return svec_list_insert(self, self->count, data);
}

int svec_list_push_front(svec_list self, void *data) {
  return svec_list_insert(self, 0, data);
}

void svec_list_pop_back(svec_list self) {
  svec_list_erase(self, self->count - 1);
}

void svec_list_pop_front(svec_list self) {
  svec_list_erase(self, 0);
}

bool svec_list_empty(svec_list self) {
  return self->count == 0;
}

size_t svec_list_size(svec_list self) {
  return self->count;
}
