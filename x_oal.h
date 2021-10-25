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
#ifndef __X_OAL_H_
#define __X_OAL_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef __linux

//data type define
typedef signed char        s8_t;
typedef signed short       s16_t;
typedef signed int         s32_t;
typedef signed long long   s64_t;
typedef unsigned char      u8_t;
typedef unsigned short     u16_t;
typedef unsigned int       u32_t;
typedef unsigned long      ulong_t;
typedef unsigned long long u64_t;
typedef signed char        bool_t;
typedef void *             HANDLE;


#define MEM_SIZE_IN_BOUND(size) 	   ((size + 3) & 0xfffffffc)

#define MEM_INIT_ZERO(ptr_, size_)     memset((ptr_), 0, (size_))

#define LOG_DBG(tag, format, ...)	 printf("D [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)
#define LOG_WARN(tag, format, ...)	 printf("W [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)
#define LOG_ERR(tag, format, ...)	 printf("E [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)

#define X_ASSERT(tag, assertion) \
    do { \
        if (!(assertion)) { \
            LOG_ERR(tag, "assert fail %s on %d", __FILE__, __LINE__); \
            assert(0); \
        } \
    } while(0)


/* OS critical section entry/exit (unconditional interrupt disabling) */
#define X_CRITICAL_ENTRY()
#define X_CRITICAL_EXIT()

#define X_FOREVER                           0xFFFFFFFFU
#define X_NO_WAIT                           0

#define X_GET_TICK_COUNT()                  1000

#define X_MS_2_TICKS(ms_)                   (ms_)

#define X_TICKS_2_MS(t_)                    (t_)

#define X_EPOLL_WAIT(entry_bits_, exit_bits_, value_, ticks_to_wait_)

#define X_EVENT_SIGNAL(h_, v_, a_)

static __inline void *X_MALLOC(size_t size) {
    size_t real_size = MEM_SIZE_IN_BOUND(size);
    void *p = malloc(real_size);
    if (p) memset(p, 0, real_size);
    return p;
}

static __inline void X_FREE(void *p) {
    if (p != NULL) {
        free(p);
        p = NULL;
    }
}

#endif

#ifdef WINVER

#define LOG_DBG(tag, format, ...)	 printf("D [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)
#define LOG_WARN(tag, format, ...)	 printf("W [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)
#define LOG_ERR(tag, format, ...)	 printf("E [%s][%s]" format"\n", tag, __func__, ##__VA_ARGS__)

#endif



#endif //__X_OAL_H_
