/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 */

#include <stdbool.h>
#include <stdio.h>
#include "svec/list.h"
#include "svec/svec.h"

struct data {
  int val;
};

static void test1() {
  int errc = 0;

  svec_list list = svec_list_new(sizeof(int));

  ////////////////
  if (!svec_list_empty(list)) {
    errc = 1;
    goto fini;
  }
  ////////////////
  if (svec_list_size(list) != 0) {
    errc = 2;
    goto fini;
  }
  ////////////////
  // 5 2 3
  int a;
  a = 1;
  svec_list_push_back(list, &a);
  a = 2;
  svec_list_push_back(list, &a);
  a = 3;
  svec_list_push_back(list, &a);
  a = 4;
  svec_list_push_back(list, &a);
  svec_list_pop_back(list);
  svec_list_pop_front(list);
  a = 5;
  svec_list_push_front(list, &a);
  a = 6;
  svec_list_push_front(list, &a);
  svec_list_pop_front(list);

  if (svec_list_empty(list)) {
    errc = 3;
    goto fini;
  }
  if (svec_list_size(list) != 3) {
    errc = 4;
    goto fini;
  }
  if (*(int*)svec_list_at(list, 0) != 5) {
    errc = 5;
    goto fini;
  }
  if (*(int*)svec_list_at(list, 1) != 2) {
    errc = 5;
    goto fini;
  }
  if (*(int*)svec_list_at(list, 2) != 3) {
    errc = 5;
    goto fini;
  }
  ////////////////
  svec_list_clear(list);
  if (!svec_list_empty(list)) {
    errc = 6;
    goto fini;
  }

  if (svec_list_at(list, 0)) {
    errc = 7;
    goto fini;
  }

  if (svec_list_at(list, 1)) {
    errc = 7;
    goto fini;
  }

fini:
  if (errc) {
    printf("Test fails: errc %d", errc);
  } else {
    printf("Test passed!\n");
  }
}

static void test2() {
  svec_list list1 = svec_list_new(sizeof(struct data));
}

int main() {
  test1();
  test2();
  return 0;
}
