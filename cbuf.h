/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @author Leyuan Pan
 * @date Sep 04, 2020
 */

#ifndef SVEC_H_
#define SVEC_H_

#include <stddef.h>
#include <string.h>

#define svec_t(type)                                                           \
  struct {                                                                     \
    type *p_start_;                                                            \
    type *p_finish_;                                                           \
    type *p_beg_of_storage_;                                                   \
    type *p_end_of_storage_;                                                   \
  }

#define svec_init(sv, p_storage, sz_storage)                                   \
  do {                                                                         \
    (sv).p_beg_of_storage_ = (typeof((sv).p_beg_of_storage_))(                 \
        ((size_t)(p_storage) + sizeof(*((sv).p_beg_of_storage_)) - 1) /        \
        sizeof(*((sv).p_beg_of_storage_)) *                                    \
        sizeof(*((sv).p_beg_of_storage_)));                                    \
    (sv).p_end_of_storage_ =                                                   \
        (typeof((sv).p_end_of_storage_))(((size_t)(p_storage) + sz_storage) /  \
                                         sizeof(*((sv).p_end_of_storage_)) *   \
                                         sizeof(*((sv).p_end_of_storage_)));   \
    (sv).p_start_ = (sv).p_beg_of_storage_;                                    \
    (sv).p_finish_ = (sv).p_beg_of_storage_;                                   \
  } while (0)

#define svec_reinit(sv, p_storage, sz_storage, preserve)

#define svec_push_back(sv, a)                                                  \
  do {                                                                         \
    *(sv).p_finish_++ = a;                                                     \
    if ((sv).p_finish_ == (sv).p_end_of_storage_) {                            \
      (sv).p_finish_ = (sv).p_beg_of_storage_;                                 \
    }                                                                          \
  } while (0)

#define svec_pop_back(sv)                                                      \
  do {                                                                         \
    if (--(sv).p_finish_ < (sv).p_beg_of_storage_) {                           \
      (sv).p_finish_ = (sv).p_end_of_storage_ - 1;                             \
    }                                                                          \
  } while (0)

#define svec_push_front(sv, a)                                                 \
  do {                                                                         \
    if (--(sv).p_start_ < (sv).p_beg_of_storage_) {                            \
      (sv).p_start_ = (sv).p_end_of_storage_ - 1;                              \
    }                                                                          \
    *(sv).p_start_ = a;                                                        \
  } while (0)

#define svec_pop_front(sv)                                                     \
  do {                                                                         \
    if (++(sv).p_start_ == (sv).p_end_of_storage_) {                           \
      (sv).p_start_ = (sv).p_beg_of_storage_;                                  \
    }                                                                          \
  } while (0)

#define svec_insert(sv, i, a)                                                  \
  do {                                                                         \
  } while (0)

#define svec_erase(sv, i)                                                      \
  do {                                                                         \
  } while (0)

#define svec_clear(sv) ((sv).p_finish_ = (sv).p_start_)

#define svec_resize(sv, sz)                                                    \
  do {                                                                         \
    (sv).p_finish_ = (sv).p_start_ + (sz);                                     \
    if ((sv).p_finish_ > (sv).p_end_of_storage_) {                             \
      (sv).p_finish_ =                                                         \
          (sv).p_finish_ - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_;    \
    }                                                                          \
  } while (0)

#define svec_front(sv) (*((sv).p_start_))

#define svec_back(sv)                                                          \
  (*((sv).p_finish_ == (sv).p_beg_of_storage_ ? ((sv).p_end_of_storage_ - 1)   \
                                              : ((sv).p_finish_ - 1)))

#define svec_data(sv) ((sv).p_start_)

#define svec_rdata(sv)                                                         \
  ((sv).p_finish_ == (sv).p_beg_of_storage_ ? ((sv).p_end_of_storage_ - 1)     \
                                            : ((sv).p_finish_ - 1))

#define svec_at(sv, i)                                                         \
  (*((sv).p_start_ + i >= (sv).p_end_of_storage_                               \
         ? (sv).p_start_ + i - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_ \
         : (sv).p_start_ + i))

#define svec_pat(sv, i)                                                        \
  ((sv).p_start_ + i >= (sv).p_end_of_storage_                                 \
       ? ((sv).p_start_ + i - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_) \
       : ((sv).p_start_ + i))

#define svec_size(sv)                                                          \
  ((sv).p_finish_ < (sv).p_start_                                              \
       ? (((sv).p_finish_ - (sv).p_beg_of_storage_) +                          \
          ((sv).p_end_of_storage_ - (sv).p_start_))                            \
       : ((sv).p_finish_ - (sv).p_start_))

#define svec_capacity(sv) ((sv).p_end_of_storage_ - (sv).p_beg_of_storage_ - 1)

#define svec_empty(sv) ((sv).p_start_ == (sv).p_finish_)

#define svec_full(sv)                                                          \
  (((sv).p_start_ == (sv).p_beg_of_storage_ &&                                 \
    (sv).p_finish_ == (sv).p_end_of_storage_) ||                               \
   ((sv).p_start_ == (sv).p_finish_ + 1))

#define __svec_swap__(a, b)                                                    \
  do {                                                                         \
    void *tmp = a;                                                             \
    a = b;                                                                     \
    b = tmp;                                                                   \
  } while (0)

#define svec_swap(sv_a, sv_b)                                                  \
  do {                                                                         \
    __svec_swap__(sv_a.p_start_, sv_b.p_start_);                               \
    __svec_swap__(sv_a.p_finish_, sv_b.p_finish_);                             \
    __svec_swap__(sv_a.p_beg_of_storage_, sv_b.p_beg_of_storage_);             \
    __svec_swap__(sv_a.p_end_of_storage_, sv_b.p_end_of_storage_);             \
  } while (0)

#define svec_copy(src_sv, src_beg, src_end, dst_sv, dst_beg)

#define svec_fill(sv, i_beg, i_end, a)

#endif // SVEC_H_
