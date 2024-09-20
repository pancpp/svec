/**
 * @copyright Copyright (C) 2020 Leyuan Pan. All rights reserved.
 *
 * @file
 * @brief Circular buffer based on static memory.
 */

#ifndef SVEC_SCBUF_H_
#define SVEC_SCBUF_H_

#include <stddef.h>
#include <string.h>

#define svec_scbuf(type)     \
  struct {                   \
    type *p_start_;          \
    type *p_finish_;         \
    type *p_beg_of_storage_; \
    type *p_end_of_storage_; \
  }

#define svec_scbuf_init(sv, p_storage, sz_storage)                            \
  do {                                                                        \
    (sv).p_beg_of_storage_ =                                                  \
        (typeof((sv).p_beg_of_storage_))(((size_t)(p_storage) +               \
                                          sizeof(*((sv).p_beg_of_storage_)) - \
                                          1) /                                \
                                         sizeof(*((sv).p_beg_of_storage_)) *  \
                                         sizeof(*((sv).p_beg_of_storage_)));  \
    (sv).p_end_of_storage_ =                                                  \
        (typeof((sv).p_end_of_storage_))(((size_t)(p_storage) + sz_storage) / \
                                         sizeof(*((sv).p_end_of_storage_)) *  \
                                         sizeof(*((sv).p_end_of_storage_)));  \
    (sv).p_start_ = (sv).p_beg_of_storage_;                                   \
    (sv).p_finish_ = (sv).p_beg_of_storage_;                                  \
  } while (0)

#define svec_scbuf_reinit(sv, p_storage, sz_storage, preserve)

#define svec_scbuf_push_back(sv, a)                 \
  do {                                              \
    *(sv).p_finish_++ = a;                          \
    if ((sv).p_finish_ == (sv).p_end_of_storage_) { \
      (sv).p_finish_ = (sv).p_beg_of_storage_;      \
    }                                               \
  } while (0)

#define svec_scbuf_pop_back(sv)                      \
  do {                                               \
    if (--(sv).p_finish_ < (sv).p_beg_of_storage_) { \
      (sv).p_finish_ = (sv).p_end_of_storage_ - 1;   \
    }                                                \
  } while (0)

#define svec_scbuf_push_front(sv, a)                \
  do {                                              \
    if (--(sv).p_start_ < (sv).p_beg_of_storage_) { \
      (sv).p_start_ = (sv).p_end_of_storage_ - 1;   \
    }                                               \
    *(sv).p_start_ = a;                             \
  } while (0)

#define svec_scbuf_pop_front(sv)                     \
  do {                                               \
    if (++(sv).p_start_ == (sv).p_end_of_storage_) { \
      (sv).p_start_ = (sv).p_beg_of_storage_;        \
    }                                                \
  } while (0)

#define svec_scbuf_insert(sv, i, a) \
  do {                              \
  } while (0)

#define svec_scbuf_erase(sv, i) \
  do {                          \
  } while (0)

#define svec_scbuf_clear(sv) ((sv).p_finish_ = (sv).p_start_)

#define svec_scbuf_resize(sv, sz)                                           \
  do {                                                                      \
    (sv).p_finish_ = (sv).p_start_ + (sz);                                  \
    if ((sv).p_finish_ > (sv).p_end_of_storage_) {                          \
      (sv).p_finish_ =                                                      \
          (sv).p_finish_ - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_; \
    }                                                                       \
  } while (0)

#define svec_scbuf_front(sv) (*((sv).p_start_))

#define svec_scbuf_back(sv)                                                  \
  (*((sv).p_finish_ == (sv).p_beg_of_storage_ ? ((sv).p_end_of_storage_ - 1) \
                                              : ((sv).p_finish_ - 1)))

#define svec_scbuf_data(sv) ((sv).p_start_)

#define svec_scbuf_rdata(sv)                                               \
  ((sv).p_finish_ == (sv).p_beg_of_storage_ ? ((sv).p_end_of_storage_ - 1) \
                                            : ((sv).p_finish_ - 1))

#define svec_scbuf_at(sv, i)                                                   \
  (*((sv).p_start_ + i >= (sv).p_end_of_storage_                               \
         ? (sv).p_start_ + i - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_ \
         : (sv).p_start_ + i))

#define svec_scbuf_pat(sv, i)                                                  \
  ((sv).p_start_ + i >= (sv).p_end_of_storage_                                 \
       ? ((sv).p_start_ + i - (sv).p_end_of_storage_ + (sv).p_beg_of_storage_) \
       : ((sv).p_start_ + i))

#define svec_scbuf_size(sv)                           \
  ((sv).p_finish_ < (sv).p_start_                     \
       ? (((sv).p_finish_ - (sv).p_beg_of_storage_) + \
          ((sv).p_end_of_storage_ - (sv).p_start_))   \
       : ((sv).p_finish_ - (sv).p_start_))

#define svec_scbuf_capacity(sv) \
  ((sv).p_end_of_storage_ - (sv).p_beg_of_storage_ - 1)

#define svec_scbuf_empty(sv) ((sv).p_start_ == (sv).p_finish_)

#define svec_scbuf_full(sv)                      \
  (((sv).p_start_ == (sv).p_beg_of_storage_ &&   \
    (sv).p_finish_ == (sv).p_end_of_storage_) || \
   ((sv).p_start_ == (sv).p_finish_ + 1))

#define svec_scbuf_copy(src_sv, src_beg, src_end, dst_sv, dst_beg)

#define svec_scbuf_fill(sv, i_beg, i_end, a)

#endif  // SVEC_SCBUF_H_
