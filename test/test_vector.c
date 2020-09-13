/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 12, 2020
 */

#include <stdbool.h>
#include <stdio.h>
#include "svec/svec.h"
#include "svec/vector.h"

struct data {
  int val;
};

static void test1() {
  int errc = 0;

  svec_vector vec = svec_vector_new(sizeof(int));

  ////////////////
  if (!svec_vector_empty(vec)) {
    errc = 1;
    goto fini;
  }
  ////////////////
  if (svec_vector_size(vec) != 0) {
    errc = 2;
    goto fini;
  }
  ////////////////
  // 5 2 3
  int a;
  a = 1;
  svec_vector_push_back(vec, &a);
  a = 2;
  svec_vector_push_back(vec, &a);
  a = 3;
  svec_vector_push_back(vec, &a);
  a = 4;
  svec_vector_push_back(vec, &a);

  svec_vector_pop_back(vec);
  svec_vector_erase(vec, 0);

  a = 5;
  svec_vector_insert(vec, 0, &a);
  a = 6;
  svec_vector_insert(vec, 0, &a);

  svec_vector_erase(vec, 0);

  if (svec_vector_empty(vec)) {
    errc = 3;
    goto fini;
  }
  if (svec_vector_size(vec) != 3) {
    errc = 4;
    goto fini;
  }

  int* data = (int*)svec_vector_data(vec);
  for (int i = 0; i < 3; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n");

  if (*(int*)svec_vector_at(vec, 0) != 5) {
    errc = 5;
    goto fini;
  }
  if (*(int*)svec_vector_at(vec, 1) != 2) {
    errc = 6;
    goto fini;
  }
  if (*(int*)svec_vector_at(vec, 2) != 3) {
    errc = 7;
    goto fini;
  }
  ////////////////
  svec_vector_clear(vec);
  if (!svec_vector_empty(vec)) {
    errc = 8;
    goto fini;
  }

  if (svec_vector_at(vec, 0)) {
    errc = 9;
    goto fini;
  }

  if (svec_vector_at(vec, 1)) {
    errc = 10;
    goto fini;
  }

fini:
  if (errc) {
    printf("Test fails: errc %d\n", errc);
  } else {
    printf("Test passed!\n");
  }
}

static void test2() {
  svec_vector vector1 = svec_vector_new(sizeof(struct data));
}

int main() {
  test1();
  test2();
  return 0;
}
