/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 04, 2020
 */

#include "svec.h"
#include <stdio.h>

int main()
{
  char buff_a[1024];
  char buff_b[2048];

  svec_t(int) sv_a;
  svec_t(int) sv_b;

  svec_init(sv_a, buff_a, sizeof(buff_a));
  svec_init(sv_b, buff_b + 5, sizeof(buff_b) - 5);

  printf("sv_a.empty = %d\n", svec_empty(sv_a));
  printf("sv_b.empty = %d\n", svec_empty(sv_b));

  svec_push_back(sv_a, 10);
  svec_push_back(sv_a, 20);
  svec_push_front(sv_a, 30);
  svec_push_front(sv_a, 40);

  printf("---------------\n");
  for (size_t i = 0; i < svec_size(sv_a); ++i)
  {
    printf("sv_a[%lu] = %d\n", i, svec_at(sv_a, i));
  }
  printf("---------------\n");

  printf("sv_a.size = %ld\n", svec_size(sv_a));
  printf("sv_b.size = %ld\n", svec_size(sv_b));
  printf("sv_a.capacity = %ld\n", svec_capacity(sv_a));
  printf("sv_b.capacity = %ld\n", svec_capacity(sv_b));

  svec_swap(sv_a, sv_b);

  printf("sv_a.size = %ld\n", svec_size(sv_a));
  printf("sv_b.size = %ld\n", svec_size(sv_b));
  printf("sv_a.capacity = %ld\n", svec_capacity(sv_a));
  printf("sv_b.capacity = %ld\n", svec_capacity(sv_b));

  svec_clear(sv_a);
  // svec_pop_back(sv_b);
  // svec_pop_front(sv_b);

  printf("sv_b.size = %ld\n", svec_size(sv_b));
  printf("sv_b[0] = %d\n", svec_at(sv_b, 0));

  return 0;
}
