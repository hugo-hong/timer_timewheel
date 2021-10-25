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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "x_utils.h"
#include "x_list.h"

/*******************************************************************************
 *                      Macros & Type Define
 *******************************************************************************/
#define TAG "X_LIST"



/*******************************************************************************
 *                      Structures
 *******************************************************************************/


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
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
                  struct list_head *prev,
                  struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head *prev, struct list_head *next)
{
   next->prev = prev;
   prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

/**
 * Replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void __list_replace(struct list_head *old, struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

static inline void __list_splice(const struct list_head *list,
				 struct list_head *prev,
				 struct list_head *next)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

static inline void __list_cut_position(struct list_head *list,
		struct list_head *head, struct list_head *entry)
{
	struct list_head *new_first = entry->next;
	list->next = head->next;
	list->next->prev = list;
	list->prev = entry;
	entry->next = list;
	head->next = new_first;
	new_first->prev = head;
}


void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

void list_replace_init(struct list_head *old, struct list_head *new)
{
    __list_replace(old, new);
    INIT_LIST_HEAD(old);
}

void list_del_entry(struct list_head *entry)
{
    __list_del_entry(entry);
}

void list_del_init(struct list_head *entry)
{
    __list_del_entry(entry);
    INIT_LIST_HEAD(entry);
}

void list_move(struct list_head *list, struct list_head *head)
{
    __list_del_entry(list);
    list_add(list, head);
}

void list_move_tail(struct list_head *list, struct list_head *head)
{
    __list_del_entry(list);
    list_add_tail(list, head);
}

void list_splice(const struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head, head->next);
}

void list_splice_tail(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head->prev, head);
}

void list_splice_init(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head, head->next);
		INIT_LIST_HEAD(list);
	}
}

void list_splice_tail_init(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head->prev, head);
		INIT_LIST_HEAD(list);
	}
}

void list_cut_position(struct list_head *list,
		struct list_head *head, struct list_head *entry)
{
	if (list_empty(head))
		return;
	if (list_is_singular(head) &&
		(head->next != entry && head != entry))
		return;
	if (entry == head)
		INIT_LIST_HEAD(list);
	else
		__list_cut_position(list, head, entry);
}

/*******************************************************************************
 *                      END OF FILE
 *******************************************************************************/