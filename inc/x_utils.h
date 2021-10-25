/*********************************************************************************
   Copyright (C)
   Written 2020 by hugo（yongguang hong） <hugo.08@163.com>
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*********************************************************************************/

#ifndef __X_UTILS_H_
#define __X_UTILS_H_
#include "x_oal.h"

#ifndef UNUSED_ATTR
#define UNUSED_ATTR __attribute__((unused))
#endif
#ifndef UNUSED
#define UNUSED(x_) (void)x_
#endif
#ifndef XSTR
#define XSTR(x_) #x_
#endif
#ifndef CONCAT
#define CONCAT(a_, b_) a_##b_
#endif
#ifndef MAX
#define MAX(x_, y_) (((x_) > (y_)) ? (x_) : (y_))
#endif
#ifndef MIN
#define MIN(x_, y_) (((x_) < (y_)) ? (x_) : (y_))
#endif
#ifndef DIM
#define DIM(a_)		(sizeof(a_) / sizeof((a_)[0]))
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a_)		(sizeof(a_) / sizeof((a_)[0]))
#endif
#ifndef BIT
#define BIT(n_)      (1 << (n_))
#endif
#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

//Macro sets or clears bit depending on boolean value
#define WRITE_BIT(var_, bit_, set_) \
	((var_) = (set_) ? ((var_) | BIT(bit_)) : ((var_) & ~BIT(bit_)))

#define BIT_MASK(n_) (BIT(n_) - 1)

/* number of nsec per usec */
#define NSEC_PER_USEC 1000U

/* number of microseconds per millisecond */
#define USEC_PER_MSEC 1000U

/* number of milliseconds per second */
#define MSEC_PER_SEC 1000U

/* number of microseconds per second */
#define USEC_PER_SEC ((USEC_PER_MSEC) * (MSEC_PER_SEC))

/* number of nanoseconds per second */
#define NSEC_PER_SEC ((NSEC_PER_USEC) * (USEC_PER_MSEC) * (MSEC_PER_SEC))


//retrieves the offset of a member from the beginning of structure
#ifndef OFFSETOF
#define OFFSETOF(type, member) ((size_t)(&((type*)0)->member))
#endif
//retrieves structure ptr from the member ptr
#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)    ((type *)( (char *)ptr - OFFSETOF(type, member) ))
#endif

/*! access element at index @p i_ from the base pointer @p base_ */
#define PTR_AT(base_, i_)   ((base_)[(i_)])


/**
* @description
* This macro is specifically and exclusively used for checking the range
* of a block pointer returned to the pool
*/
#define IS_IN_RANGE(x_, min_, max_)  (((min_) <= (x_)) && ((x_) <= (max_)))


// link for list
typedef struct _x_link {
    struct _x_link * next;
} x_link_t;

/********************************************************************************
** Macros to get and put bytes to and from a stream (Little Endian format).
*/
#define UINT32_TO_STREAM(p, u32) {*(p)++ = (u8_t)(u32); *(p)++ = (u8_t)((u32) >> 8); *(p)++ = (u8_t)((u32) >> 16); *(p)++ = (u8_t)((u32) >> 24);}
#define UINT24_TO_STREAM(p, u24) {*(p)++ = (u8_t)(u24); *(p)++ = (u8_t)((u24) >> 8); *(p)++ = (u8_t)((u24) >> 16);}
#define UINT16_TO_STREAM(p, u16) {*(p)++ = (u8_t)(u16); *(p)++ = (u8_t)((u16) >> 8);}
#define UINT8_TO_STREAM(p, u8)   {*(p)++ = (u8_t)(u8);}
#define INT8_TO_STREAM(p, u8)    {*(p)++ = (s8_t)(u8);}
#define ARRAY32_TO_STREAM(p, a)  {register int i_; for (i_ = 0; i_ < 32;           i_++) *(p)++ = (u8_t) a[31 - i_];}
#define ARRAY16_TO_STREAM(p, a)  {register int i_; for (i_ = 0; i_ < 16;           i_++) *(p)++ = (u8_t) a[15 - i_];}
#define ARRAY8_TO_STREAM(p, a)   {register int i_; for (i_ = 0; i_ < 8;            i_++) *(p)++ = (u8_t) a[7 - i_];}
#define BDADDR_TO_STREAM(p, a)   {register int i_; for (i_ = 0; i_ < 6;  i_++) *(p)++ = (u8_t) a[6 - 1 - i_];}
#define LAP_TO_STREAM(p, a)      {register int i_; for (i_ = 0; i_ < 3;      i_++) *(p)++ = (u8_t) a[3 - 1 - i_];}
#define DEVCLASS_TO_STREAM(p, a) {register int i_; for (i_ = 0; i_ < 3;i_++) *(p)++ = (u8_t) a[3 - 1 - i_];}
#define ARRAY_TO_STREAM(p, a, len) {register int i_; for (i_ = 0; i_ < len;        i_++) *(p)++ = (u8_t) a[i_];}
#define REVERSE_ARRAY_TO_STREAM(p, a, len)  {register int i_; for (i_ = 0; i_ < len; i_++) *(p)++ = (u8_t) a[len - 1 - i_];}
#define UINT64_tO_STREAM(p, u64) {*(p)++ = (u8_t)(u64); *(p)++ = (u8_t)((u64) >> 8); *(p)++ = (u8_t)((u64) >> 16); *(p)++ = (u8_t)((u64) >> 24); \
								*(p)++ = (u8_t)((u64) >> 32); *(p)++ = (u8_t)((u64) >> 40); *(p)++ = (u8_t)((u64) >> 48); *(p)++ = (u8_t)((u64) >> 56);}

#define STREAM_TO_UINT8(u8, p)   {u8 = (u8_t)(*(p)); (p) += 1;}
#define STREAM_TO_UINT16(u16, p) {u16 = ((u16_t)(*(p)) + (((u16_t)(*((p) + 1))) << 8)); (p) += 2;}
#define STREAM_TO_UINT24(u32, p) {u32 = (((u32_t)(*(p))) + ((((u32_t)(*((p) + 1)))) << 8) + ((((u32_t)(*((p) + 2)))) << 16) ); (p) += 3;}
#define STREAM_TO_UINT32(u32, p) {u32 = (((u32_t)(*(p))) + ((((u32_t)(*((p) + 1)))) << 8) + ((((u32_t)(*((p) + 2)))) << 16) + ((((u32_t)(*((p) + 3)))) << 24)); (p) += 4;}
#define STREAM_TO_BDADDR(a, p)   {register int i_; register u8_t *pbda = (u8_t *)a + 6 - 1; for (i_ = 0; i_ < 6; i_++) *pbda-- = *p++;}
#define STREAM_TO_ARRAY32(a, p)  {register int i_; register u8_t *_pa = (u8_t *)a + 31; for (i_ = 0; i_ < 32; i_++) *_pa-- = *p++;}
#define STREAM_TO_ARRAY16(a, p)  {register int i_; register u8_t *_pa = (u8_t *)a + 15; for (i_ = 0; i_ < 16; i_++) *_pa-- = *p++;}
#define STREAM_TO_ARRAY8(a, p)   {register int i_; register u8_t *_pa = (u8_t *)a + 7; for (i_ = 0; i_ < 8; i_++) *_pa-- = *p++;}
#define STREAM_TO_DEVCLASS(a, p) {register int i_; register u8_t *_pa = (u8_t *)a + 3 - 1; for (i_ = 0; i_ < 3; i_++) *_pa-- = *p++;}
#define STREAM_TO_LAP(a, p)      {register int i_; register u8_t *plap = (u8_t *)a + 3 - 1; for (i_ = 0; i_ < 3; i_++) *plap-- = *p++;}
#define STREAM_TO_ARRAY(a, p, len) {register int i_; for (i_ = 0; i_ < len; i_++) ((u8_t *) a)[i_] = *p++;}
#define REVERSE_STREAM_TO_ARRAY(a, p, len) {register int i_; register u8_t *_pa = (u8_t *)a + len - 1; for (i_ = 0; i_ < len; i_++) *_pa-- = *p++;}

/********************************************************************************
** Macros to get and put bytes to and from a field (Little Endian format).
** These are the same as to stream, except the pointer is not incremented.
*/
#define UINT32_TO_FIELD(p, u32) {*(u8_t *)(p) = (u8_t)(u32); *((u8_t *)(p)+1) = (u8_t)((u32) >> 8); *((u8_t *)(p)+2) = (u8_t)((u32) >> 16); *((u8_t *)(p)+3) = (u8_t)((u32) >> 24);}
#define UINT24_TO_FIELD(p, u24) {*(u8_t *)(p) = (u8_t)(u24); *((u8_t *)(p)+1) = (u8_t)((u24) >> 8); *((u8_t *)(p)+2) = (u8_t)((u24) >> 16);}
#define UINT16_TO_FIELD(p, u16) {*(u8_t *)(p) = (u8_t)(u16); *((u8_t *)(p)+1) = (u8_t)((u16) >> 8);}
#define UINT8_TO_FIELD(p, u8)   {*(u8_t *)(p) = (u8_t)(u8);}


/********************************************************************************
** Macros to get and put bytes to and from a stream (Big Endian format)
*/
#define UINT32_TO_BE_STREAM(p, u32) {*(p)++ = (u8_t)((u32) >> 24);  *(p)++ = (u8_t)((u32) >> 16); *(p)++ = (u8_t)((u32) >> 8); *(p)++ = (u8_t)(u32); }
#define UINT24_TO_BE_STREAM(p, u24) {*(p)++ = (u8_t)((u24) >> 16); *(p)++ = (u8_t)((u24) >> 8); *(p)++ = (u8_t)(u24);}
#define UINT16_TO_BE_STREAM(p, u16) {*(p)++ = (u8_t)((u16) >> 8); *(p)++ = (u8_t)(u16);}
#define UINT8_TO_BE_STREAM(p, u8)   {*(p)++ = (u8_t)(u8);}
#define ARRAY_TO_BE_STREAM(p, a, len) {register int i_; for (i_ = 0; i_ < len; i_++) *(p)++ = (u8_t) a[i_];}

#define BE_STREAM_TO_UINT8(u8, p)   {u8 = (u8_t)(*(p)); (p) += 1;}
#define BE_STREAM_TO_UINT16(u16, p) {u16 = (u16_t)(((u16_t)(*(p)) << 8) + (u16_t)(*((p) + 1))); (p) += 2;}
#define BE_STREAM_TO_UINT24(u32, p) {u32 = (((u32_t)(*((p) + 2))) + ((u32_t)(*((p) + 1)) << 8) + ((u32_t)(*(p)) << 16)); (p) += 3;}
#define BE_STREAM_TO_UINT32(u32, p) {u32 = ((u32_t)(*((p) + 3)) + ((u32_t)(*((p) + 2)) << 8) + ((u32_t)(*((p) + 1)) << 16) + ((u32_t)(*(p)) << 24)); (p) += 4;}
#define BE_STREAM_TO_ARRAY(p, a, len) {register int i_; for (i_ = 0; i_ < len; i_++) ((u8_t *) a)[i_] = *p++;}


/********************************************************************************
** Macros to get and put bytes to and from a field (Big Endian format).
** These are the same as to stream, except the pointer is not incremented.
*/
#define UINT32_TO_BE_FIELD(p, u32) {*(u8_t *)(p) = (u8_t)((u32) >> 24);  *((u8_t *)(p)+1) = (u8_t)((u32) >> 16); *((u8_t *)(p)+2) = (u8_t)((u32) >> 8); *((u8_t *)(p)+3) = (u8_t)(u32); }
#define UINT24_TO_BE_FIELD(p, u24) {*(u8_t *)(p) = (u8_t)((u24) >> 16); *((u8_t *)(p)+1) = (u8_t)((u24) >> 8); *((u8_t *)(p)+2) = (u8_t)(u24);}
#define UINT16_TO_BE_FIELD(p, u16) {*(u8_t *)(p) = (u8_t)((u16) >> 8); *((u8_t *)(p)+1) = (u8_t)(u16);}
#define UINT8_TO_BE_FIELD(p, u8)   {*(u8_t *)(p) = (u8_t)(u8);}


/* Internal helpers only used by the sys_* APIs further below */
#define bswap_16_(x) ((u16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

#define bswap_32_(x) ((u32_t) ((((x) >> 24) & 0xff) | \
				   (((x) >> 8) & 0xff00) | \
				   (((x) & 0xff00) << 8) | \
				   (((x) & 0xff) << 24)))
#define bswap_64_(x) ((u64_t) ((((x) >> 56) & 0xff) | \
				   (((x) >> 40) & 0xff00) | \
				   (((x) >> 24) & 0xff0000) | \
				   (((x) >> 8) & 0xff000000) | \
				   (((x) & 0xff000000) << 8) | \
				   (((x) & 0xff0000) << 24) | \
				   (((x) & 0xff00) << 40) | \
				   (((x) & 0xff) << 56)))

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define sys_le16_to_cpu(val) (val)
#define sys_cpu_to_le16(val) (val)
#define sys_be16_to_cpu(val) bswap_16_(val)
#define sys_cpu_to_be16(val) bswap_16_(val)
#define sys_le32_to_cpu(val) (val)
#define sys_cpu_to_le32(val) (val)
#define sys_le64_to_cpu(val) (val)
#define sys_cpu_to_le64(val) (val)
#define sys_be32_to_cpu(val) bswap_32_(val)
#define sys_cpu_to_be32(val) bswap_32_(val)
#define sys_be64_to_cpu(val) bswap_64_(val)
#define sys_cpu_to_be64(val) bswap_64_(val)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define sys_le16_to_cpu(val) bswap_16_(val)
#define sys_cpu_to_le16(val) bswap_16_(val)
#define sys_be16_to_cpu(val) (val)
#define sys_cpu_to_be16(val) (val)
#define sys_le32_to_cpu(val) bswap_32_(val)
#define sys_cpu_to_le32(val) bswap_32_(val)
#define sys_le64_to_cpu(val) bswap_64_(val)
#define sys_cpu_to_le64(val) bswap_64_(val)
#define sys_be32_to_cpu(val) (val)
#define sys_cpu_to_be32(val) (val)
#define sys_be64_to_cpu(val) (val)
#define sys_cpu_to_be64(val) (val)
#else
#error "Unknown byte order"
#endif

#endif //__X_UTILS_H_
