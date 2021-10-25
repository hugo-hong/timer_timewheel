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
#include "x_errno.h"
#include "x_utils.h"
#include "timewheel.h"


/*******************************************************************************
 *                      Macros & Type Define
 *******************************************************************************/
#define TAG    "TIMEWHEEL"

/* native TIMER operations */
#define TW_INDEX_(tw_, N_) \
    (((tw_)->current_index >> (TVR_BITS + (N_) * TVN_BITS)) & TVN_MASK)

/*******************************************************************************
 *                      Structures
 *******************************************************************************/
struct tvec_n {
    struct list_head vec[TVN_SIZE];
};

struct tvec_root{
    struct list_head vec[TVR_SIZE];
};

struct tvec_base
{
    unsigned long 		current_index; /* current number of ms */
    pthread_t  			threadID;
    struct tvec_root 	tv1;	/*1 wheel*/
    struct tvec_n      	tv2;	/*2 wheel*/
    struct tvec_n      	tv3;	/*3 wheel*/
    struct tvec_n      	tv4;	/*4 wheel*/
    struct tvec_n      	tv5;	/*5 wheel*/
};

struct timer_list{
    struct list_head entry;          //timer list
    unsigned long expires;           //timeout value
    void (*function)(unsigned long); //timer handler
    unsigned long data;              //timer handler paramter
    struct tvec_base *base;          //timerwheel
};

/*******************************************************************************
 *                      Internal Function Declarations
 *******************************************************************************/

/*******************************************************************************
 *                      External Function Declarations
 *******************************************************************************/

/*******************************************************************************
 *                      Variable Definitions
 *******************************************************************************/

/*******************************************************************************
 *                      External Variable Declaration
 *******************************************************************************/

/*******************************************************************************
 *                      Function Definitions
 *******************************************************************************/

static void __add_timer(struct tvec_base *base, struct timer_list *timer)
{
    struct list_head *vec;
    unsigned long expires = timer->expires;
    unsigned long idx = expires - base->current_index;

    if ( (signed long)idx < 0 ) /* expires or out of limit?*/
    {
        /* put to first timewheel current slot */
        vec = base->tv1.vec + (base->current_index & TVR_MASK);
    }
    else if ( idx < TVR_SIZE )
    {
        /* put to NO 1 timewheel slot */
        int i = expires & TVR_MASK;
        vec = base->tv1.vec + i;
    }
    else if ( idx < 1 << (TVR_BITS + TVN_BITS) )
    {
        /* put to NO 2 timewheel slot */
        int i = (expires >> TVR_BITS) & TVN_MASK;
        vec = base->tv2.vec + i;
    }
    else if ( idx < 1 << (TVR_BITS + 2 * TVN_BITS) )
    {
        /* put to NO 3 timewheel slot */
        int i = (expires >> (TVR_BITS + TVN_BITS)) & TVN_MASK;
        vec = base->tv3.vec + i;
    }
    else if( idx < 1 << (TVR_BITS + 3 * TVN_BITS) )
    {
        /* put to NO 4 timewheel slot */
        int i = (expires >> (TVR_BITS + 2 * TVN_BITS)) & TVN_MASK;
        vec = base->tv4.vec + i;
    }
    else
    {
        /* put to NO 5 timewheel slot */
        int i;
        if (idx > 0xffffffffUL)
        {
            idx = 0xffffffffUL;
            expires = idx + base->current_index;
        }
        i = (expires >> (TVR_BITS + 3 * TVN_BITS)) & TVN_MASK;
        vec = base->tv5.vec + i;
    }

    list_add_tail(&timer->entry, vec);
}

static inline void __detach_timer(struct timer_list *timer)
{
    struct list_head *entry = &timer->entry;
    list_del_entry(entry);
    INIT_ENTRY(entry);
}

static int __mod_timer(struct timer_list *timer, unsigned long expires)
{
    if(NULL != timer->entry.next)
        __detach_timer(timer);

    __add_timer(timer->base, timer);

    return 0;
}

static void __init_tvr(struct tvec_root * tvr)
{
    int i;

    for( i = 0; i < TVR_SIZE; i++ )
        INIT_LIST_HEAD(&tvr->vec[i]);
}

static void __init_tvn(struct tvec_n * tvn)
{
    int i;

    for(int i = 0; i < TVN_SIZE; i++ )
        INIT_LIST_HEAD(&tvn->vec[i]);
}

static void __deinit_tvr(struct tvec_root *pvr)
{
    int i;
    struct list_head *pos,*tmp;
    struct timer_list *te;

    for (i = 0; i < TVR_SIZE; i++)
    {
        list_for_each_safe(pos, tmp, &pvr->vec[i])
        {
            te = LIST_ENTRY(pos, struct timer_list, entry);
            list_del_entry(pos);
            X_FREE(te);
        }
    }
}

static void __deinit_tvn(struct tvec_n *pvn)
{
    int i;
    struct list_head *pos,*tmp;
    struct timer_list *te;

    for (i = 0; i < TVN_SIZE; i++)
    {
        list_for_each_safe(pos,tmp,&pvn->vec[i])
        {
            te = LIST_ENTRY(pos, struct timer_list, entry);
            list_del_entry(pos);
            X_FREE(te);
        }
    }
}

static void __ti_add_timer(struct timer_list *timer)
{
    if ( NULL != timer->entry.next)
    {
        LOG_ERR(TAG, "timer is already exist\n");
        return;
    }

    ti_mod_timer(timer, timer->expires);
}


/*Time wheel cascade*/
static int __tw_cascade(struct tvec_base *base, struct tvec_n *tv, int index)
{
    struct list_head *pos,*tmp;
    struct timer_list *timer;
    struct list_head tv_list;

    /* re calc timewheel all task */
    list_replace_init(tv->vec + index, &tv_list);

    list_for_each_safe(pos, tmp, &tv_list)
    {
        timer = LIST_ENTRY(pos, struct timer_list, entry);
        __add_timer(base, timer);
    }

    return index;
}

static void *__timewheel_run(void *base)
{
    int ret;
    struct timeval tv;
    struct timer_list *timer;
    struct tvec_base *ba = (struct tvec_base *)base;

    for (;;)
    {
        gettimeofday(&tv, NULL);
        while ( ba->current_index <= (tv.tv_sec*1000 + tv.tv_usec/1000) )
        {
            /* some timer expire */
           struct list_head work_list;
           struct list_head *head = &work_list;
           int index = ba->current_index & TVR_MASK;/* first wheel pos*/

           /* update the timewheel when pointer to the first time slot */
           if (!index &&
              (!__tw_cascade(ba, &ba->tv2, TW_INDEX_(ba, 0))) &&
              ( !__tw_cascade(ba, &ba->tv3, TW_INDEX_(ba, 1))) &&
              (!__tw_cascade(ba, &ba->tv4, TW_INDEX_(ba, 2))) )
               __tw_cascade(ba, &ba->tv5, TW_INDEX_(ba, 3));

            ba->current_index ++;
            list_replace_init(ba->tv1.vec + index, &work_list);
            while(!list_empty(head))
            {
                void (*fn)(unsigned long);
                unsigned long data;
                timer = list_first_entry(head, struct timer_list, entry);
                fn = timer->function;
                data = timer->data;
                __detach_timer(timer);
                LOG_DBG(TAG, "TS %lu TIMEROUT", ba->current_index);
                (*fn)(data);
            }
        }
    }
}

/**
 * @brief:
 * @param {void} *t
 * @param {unsigned long} expires
 * @return {*}
 */
int ti_mod_timer(void *t, unsigned long expires)
{
    struct timer_list *te  = (struct timer_list *)t;
    struct tvec_base *base;

    base = te->base;
    if (NULL == base)
        return -X_EINVAL;

    expires = expires + base->current_index;
    if (te->entry.next != NULL && te->expires == expires)
        return 0;

    if ( NULL == te->function )
    {
        LOG_ERR(TAG, "timer's timeout function is null\n");
        return -X_EINVAL;
    }

    te->expires = expires;
    return __mod_timer(te, expires);
}

/**
 * @brief:
 * @param {void} *tw
 * @param {unsigned long} expires
 * @param {timeouthandle} handler
 * @param {unsigned long} arg
 * @return {*}
 */
void* ti_add_timer(
    void *tw,
    unsigned long expires,
    timeouthandle handler,
    unsigned long arg
)
{
    struct timer_list  *te;

    te = (struct timer_list *)X_MALLOC(sizeof(struct timer_list) );
    if (NULL == te)
        return NULL;

    te->entry.next = NULL;
    te->base = (struct tvec_base *)tw;
    te->expires = expires;
    te->function  = handler;
    te->data = arg;

    __ti_add_timer(te);

    return (void *)te;
}

/**
 * @brief:
 * @param {void} *p
 * @return {*}
 */
void ti_del_timer(void *p)
{
    struct timer_list *te = (struct timer_list*)p;

    if(NULL == te)
        return;

    if(NULL != te->entry.next)
        __detach_timer(te);

    X_FREE(te);
}


/**
 * @brief:
 * @param {*}
 * @return {*}
 */
void *ti_timewheel_create(void)
{
   int ret = 0;
   struct timeval tv;
   struct tvec_base *base;

   base = (struct tvec_base *) X_MALLOC( sizeof(struct tvec_base) );
   if( NULL == base )
      return NULL;

   __init_tvr(&base->tv1);
   __init_tvn(&base->tv2);
   __init_tvn(&base->tv3);
   __init_tvn(&base->tv4);
   __init_tvn(&base->tv5);

   gettimeofday(&tv, NULL);
   base->current_index = tv.tv_sec*1000 + tv.tv_usec/1000;

   if ( 0 != pthread_create(&base->threadID, NULL, __timewheel_run, base))
   {
      X_FREE(base);
      return NULL;
   }

   return base;
}

/**
 * @brief:
 * @param {void *} tw
 * @return {*}
 */
void ti_timewheel_release(void * tw)
{
    struct tvec_base *base = (struct tvec_base *)tw;

    if (NULL == base)
        return;

    __deinit_tvr(&base->tv1);
    __deinit_tvn(&base->tv2);
    __deinit_tvn(&base->tv3);
    __deinit_tvn(&base->tv4);
    __deinit_tvn(&base->tv5);

    // exit timewheel thread

    X_FREE(tw);
}
