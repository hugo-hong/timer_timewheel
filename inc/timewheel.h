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
#ifndef __TIMEWHEEL_H__
#define __TIMEWHEEL_H__
#include <pthread.h>
#include <sys/time.h>
#include "x_list.h"


/*******************************************************************************
 *                      Macros & Type Define
 *******************************************************************************/
// Level 5 timewheel range:0 ~ (2^8 * 2^6 * 2^6 * 2^6 *2^6)=2^32
#define TVR_BITS 		8
#define TVN_BITS 		6
#define TVR_SIZE 		(1 << TVR_BITS)
#define TVN_SIZE 		(1 << TVN_BITS)

#define TVR_MASK 		(TVR_SIZE - 1)
#define TVN_MASK 		(TVN_SIZE - 1)


typedef void (*timeouthandle)(unsigned long );

/*******************************************************************************
 *                      Structures
 *******************************************************************************/



/*******************************************************************************
 *                      Export Variable Declaration
 *******************************************************************************/

/*******************************************************************************
 *                      Function Declarations
 *******************************************************************************/
/**
 * @brief:
 * @param {*}
 * @return {*}
 */
void *ti_timewheel_create(void);

/**
 * @brief:
 * @param {void *} tw
 * @return {*}
 */
void ti_timewheel_release(void * tw);

/**
 * @brief:
 * @param {*}
 * @return {*}
 */
void* ti_add_timer(
    void *tw,
    unsigned long expires,
    timeouthandle te_handle,
    unsigned long arg
);

/**
 * @brief:
 * @param {void} *p
 * @return {*}
 */
void ti_del_timer(void *p);

/**
 * @brief:
 * @param {void} *t
 * @param {unsigned long} expires
 * @return {*}
 */
int ti_mod_timer(void *t, unsigned long expires);

#endif //__TIMEWHEEL_H__